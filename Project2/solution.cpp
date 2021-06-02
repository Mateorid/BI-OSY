#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include "common.h"

using namespace std;
#endif /* __PROGTEST__ */
uint32_t threadCount = 0;
pthread_cond_t condVar;
pthread_mutex_t threadMtx;
pthread_attr_t attr;

class MyStack {
    pthread_mutex_t stackMtx{};
    uint32_t index = -1, max;
    uint32_t *buffer;
public:
    explicit MyStack(uint32_t totalPages) {
        pthread_mutex_init(&stackMtx, nullptr);
        max = totalPages;
        buffer = new uint32_t[totalPages];
    }

    virtual ~MyStack() {
        delete[] buffer;
    }

    void push(uint32_t in) {
        pthread_mutex_lock(&stackMtx);
        if (index + 1 >= max) {
            pthread_mutex_unlock(&stackMtx);
            return;
        }
        index++;
        buffer[index] = in;
        pthread_mutex_unlock(&stackMtx);
    }

    bool pop(uint32_t pagesToPop, uint32_t *arr) {
        pthread_mutex_lock(&stackMtx);
        if (pagesToPop > index + 1) {
            pthread_mutex_unlock(&stackMtx);
            return false;
        }
        for (uint32_t i = 0; i < pagesToPop; ++i) {
            arr[i] = buffer[index - i];
        }
        if (pagesToPop == index) {
            index = 0;
        } else {
            index -= pagesToPop;
        }
        pthread_mutex_unlock(&stackMtx);
        return true;
    }
};

MyStack *myStack = nullptr;

class NewProcessWrapper {
public:
    CCPU *cpu;

    virtual ~NewProcessWrapper() {
        delete cpu;
    }

    void *args;

    void (*fnc)(CCPU *, void *);

    NewProcessWrapper(CCPU *cpu, void *args, void (*fnc)(CCPU *, void *)) : cpu(cpu), args(args), fnc(fnc) {}
};

void *NewProcessFnc(void *wrapper) {
    auto *tmp = (NewProcessWrapper *) wrapper;
    tmp->fnc(tmp->cpu, tmp->args);
    delete tmp;
    return nullptr;
}

class CPUwU : public CCPU {
    uint32_t memLimit = 0, lvl2Count = 0, lastTable = 0, lastPos = 0;
    uint32_t newPage[1]{0};
    uint32_t *level1 = nullptr, *level2 = nullptr;
public:
    CPUwU(uint8_t *memStart, uint32_t pageTableRoot) : CCPU(memStart, pageTableRoot) {
        //Setting the L1 table to 0s
        level1 = (uint32_t *) (m_MemStart + (m_PageTableRoot & ADDR_MASK));
        memset(level1, 0, 4096);
        pthread_mutex_lock(&threadMtx);
        threadCount++;
        pthread_mutex_unlock(&threadMtx);
    }

    ~CPUwU() override {
        SetMemLimit(0);
        myStack->push(m_PageTableRoot >> 12);
        pthread_mutex_lock(&threadMtx);
        threadCount--;
        pthread_mutex_unlock(&threadMtx);
        pthread_cond_broadcast(&condVar);
    }

    [[nodiscard]] uint32_t GetMemLimit() const override {
        return memLimit;
    }

    bool SetMemLimit(uint32_t pages) override {
        if (pages == memLimit)
            return true;
        else if (memLimit < pages) {
            return AddPages(pages);
        } else {
            return RemovePages(pages);
        }
    }

    bool NewProcess(void *processArg, void (*entryPoint)(CCPU *, void *), bool copyMem) override {
        uint32_t tmp[1];
        if (!myStack->pop(1, tmp)) {
            return false;
        }
        auto *cpu = new CPUwU(this->m_MemStart, (*tmp << 12) + 7);
        if (copyMem) {
            if (!cpu->SetMemLimit(memLimit)) {
                delete cpu;
                return false;
            }
            for (uint32_t i = 0; i < memLimit; ++i) {
                memcpy(cpu->virtual2Physical(i << 12, true), virtual2Physical(i << 12, true), 4096);
            }
        }
        auto *temp = new NewProcessWrapper(cpu, processArg, entryPoint);
        pthread_t thread;
        pthread_create(&thread, &attr, NewProcessFnc, (void *) temp);
        return true;
    }

protected:
    bool AddPages(uint32_t pages) {
        //Creating new L2 tables for the pages
        if (!AddLvl2(pages))
            return false;
        //Getting new pages from stack
        uint32_t toPop = pages - memLimit;
        auto *tmp = new uint32_t[toPop];
        if (!myStack->pop(toPop, tmp)) {
            delete[] tmp;
            return false;
        }
        while (toPop != 0) {
            level1 = (uint32_t *) (m_MemStart + (m_PageTableRoot & ADDR_MASK)) + lastTable;
            level2 = (uint32_t *) (m_MemStart + (*level1 & ADDR_MASK)) + lastPos;
            *level2 = (tmp[toPop - 1] << 12) + 7;
            toPop--;
            lastPos++;
            if (lastPos >= 1024) {
                lastTable++;
                lastPos = 0;
            }
            memLimit++;
        }
        delete[] tmp;
        return true;
    }

    bool AddLvl2(uint32_t pages) {
        while (lvl2Count * 1024 < pages) {
            level1 = (uint32_t *) (m_MemStart + (m_PageTableRoot & ADDR_MASK)) + lvl2Count;
            if (!myStack->pop(1, newPage))
                return false;
            *level1 = (newPage[0] << 12) + 7;
            lvl2Count++;
            //Setting the new L2 to 0s
            level2 = (uint32_t *) (m_MemStart + (*level1 & ADDR_MASK));
            memset(level2, 0, 4096);
        }
        return true;
    }

    bool RemovePages(uint32_t pages) {
        uint32_t toRemove = memLimit - pages;
        uint32_t pageNum;
        lastPos--;
        while (toRemove != 0) {
            level1 = (uint32_t *) (m_MemStart + (m_PageTableRoot & ADDR_MASK)) + lastTable;
            level2 = (uint32_t *) (m_MemStart + (*level1 & ADDR_MASK)) + lastPos;
            pageNum = *level2 >> 12;
            *level2 = 0;
            myStack->push(pageNum);
            if (lastPos == 0) {
                *level1 = 0;
                lastPos = 1023;
                if (lastTable != 0)
                    lastTable--;
            } else {
                lastPos--;
            }
            toRemove--;
            memLimit--;
        }
        return true;
    }
};

void MemMgr(void *mem, uint32_t totalPages, void *processArg, void (*mainProcess)(CCPU *, void *)) {
    myStack = new MyStack(totalPages);
    for (uint32_t i = 0; i < totalPages; ++i) {
        myStack->push(i);
    }
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_mutex_init(&threadMtx, nullptr);
    pthread_cond_init(&condVar, nullptr);
    uint32_t tmp[1];
    if (!myStack->pop(1, tmp)) {
        return;
    }
    {
        CPUwU cpu((uint8_t *) mem, (*tmp << 12) + 7);
        mainProcess(&cpu, processArg);
    }
    while (threadCount > 0) {
        pthread_cond_wait(&condVar, &threadMtx);
    }
    pthread_attr_destroy(&attr);
    pthread_cond_destroy(&condVar);
    pthread_mutex_destroy(&threadMtx);
    delete myStack;
}