#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include <array>
#include <iterator>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <pthread.h>
#include <semaphore.h>
#include "progtest_solver.h"
#include "sample_tester.h"

using namespace std;
#endif /* __PROGTEST__ */

//todo CHANGE TEST -> NON TEST
class ShipBuffer {
    deque<AShip> buffer;
    mutex bufferMtx;
    int shipCount = 0;
    condition_variable empty;           // protects from removing items from an empty buffer

public:
    ShipBuffer() = default;

    virtual void newShip(AShip ship) {
        unique_lock ul(bufferMtx);
        buffer.push_back(ship);
        empty.notify_one();
    }

    virtual void ending(int activeS, AShip bumper) {
        unique_lock ul(bufferMtx);
        for (int i = 0; i < activeS; ++i) {
            buffer.push_back(bumper);
        }
        empty.notify_all();
    }

    virtual AShip processShip() {
        AShip tmp;
        unique_lock ul(bufferMtx);
        empty.wait(ul, [this]() { return !buffer.empty(); });
        tmp = buffer.front();
        if (tmp.get() != nullptr) {
            buffer.pop_front();
        }
        return tmp;
    }
};

class ItemBuffer {
    deque<pair<AShip, vector<CCargo>>> buffer;
    mutex mtx;
    condition_variable empty;   // protects from removing items from an empty buffer

public:
    ItemBuffer() = default;

    virtual void addItem(pair<AShip, vector<CCargo>> item) {
        unique_lock ul(mtx);
        buffer.push_back(item);
        empty.notify_one();
    }

    virtual void ending(int activeW, pair<AShip, vector<CCargo>> bumper) {
        unique_lock ul(mtx);
        for (int i = 0; i < activeW; ++i) {
            buffer.push_back(bumper);
        }
        empty.notify_all();
    }

    virtual pair<AShip, vector<CCargo>> processItem() {
        pair<AShip, vector<CCargo>> tmp;
        unique_lock ul(mtx);
        empty.wait(ul, [this]() { return !buffer.empty(); });
        tmp = buffer.front();
        buffer.pop_front();
        return tmp;
    }
};

class CCargoPlanner {
public:
    CCargoPlanner() {
        salesNum = 0;
        workersNum = 0;
        bumperShip = AShip();
        bumper = pair<AShip, vector<CCargo>>(bumperShip, vector<CCargo>());
    };


    static int SeqSolver(const vector<CCargo> &cargo, int maxWeight, int maxVolume, vector<CCargo> &load);

    void Start(int sales, int workers);

    void Stop();

    void Customer(ACustomer customer);

    void Ship(AShip ship);

private:
    int salesNum, workersNum;
    mutex salesMtx;
    vector<ACustomer> customers;
    vector<thread> salesVec;
    vector<thread> workersVec;
    ShipBuffer shipBuffer;
    ItemBuffer itemBuffer;
    pair<AShip, vector<CCargo>> bumper;
    AShip bumperShip;


    void Salesman(mutex &mtx, int &active, int workers);

    void Worker();

};

int CCargoPlanner::SeqSolver(const vector<CCargo> &cargo, int maxWeight, int maxVolume, vector<CCargo> &load) {
    return ProgtestSolver(cargo, maxWeight, maxVolume, load);
}

void CCargoPlanner::Start(int sales, int workers) {
    salesNum = sales;
    workersNum = workers;
    for (int i = 0; i < sales; ++i) {
        salesVec.push_back(thread(&CCargoPlanner::Salesman, this, ref(salesMtx), ref(salesNum), workersNum));
    }
    for (int i = 0; i < workers; ++i) {
        workersVec.push_back(thread(&CCargoPlanner::Worker, this));
    }
}

void CCargoPlanner::Stop() {
    shipBuffer.ending(salesNum, bumperShip);
    for (auto &it : salesVec)
        it.join();
    for (auto &it : workersVec)
        it.join();
}

void CCargoPlanner::Customer(ACustomer customer) {
    customers.emplace_back(customer);
}

void CCargoPlanner::Ship(AShip ship) {
    shipBuffer.newShip(std::move(ship));
}

void CCargoPlanner::Salesman(mutex &mtx, int &active, int workers) {
    vector<CCargo> tmpCargo;
    vector<CCargo> allCargo;
    int var;
    while (true) {
        AShip tmp = shipBuffer.processShip();
//        string dest = tmp.get()->Destination();
        if (tmp.get() == nullptr) {
            unique_lock ul(mtx);
            active--;
            var = active;
            ul.unlock();
            if (var == 0)
                itemBuffer.ending(workers, bumper);
            break;
        }
        for (auto &customer : customers) {
            customer->Quote(tmp.get()->Destination(), tmpCargo);
            allCargo.insert(allCargo.end(), tmpCargo.begin(), tmpCargo.end());
        }
        itemBuffer.addItem(pair<AShip, vector<CCargo>>(tmp, allCargo));
        tmpCargo.clear();
        allCargo.clear();
    }
}

void CCargoPlanner::Worker() {
    pair<AShip, vector<CCargo>> item;
    vector<CCargo> load;
    while (true) {
        item = itemBuffer.processItem();
        if (item.first.get() == nullptr) {
            break;
        }
        SeqSolver(item.second, item.first->MaxWeight(), item.first->MaxVolume(), load);
        item.first->Load(load);
        load.clear();
    }
}

//-------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__

int main() {
    CCargoPlanner test;
    vector<AShipTest> ships;
    vector<ACustomerTest> customers{make_shared<CCustomerTest>(), make_shared<CCustomerTest>()};

    ships.push_back(g_TestExtra[0].PrepareTest("New York", customers));
    ships.push_back(g_TestExtra[1].PrepareTest("Barcelona", customers));
    ships.push_back(g_TestExtra[2].PrepareTest("Kobe", customers));
    ships.push_back(g_TestExtra[8].PrepareTest("Perth", customers));
    // add more buffer here

    for (auto x : customers)
        test.Customer(x);

//    test.Start(1, 1);
    test.Start(15, 12);

    for (auto x : ships)
        test.Ship(x);

    test.Stop();

    for (auto x : ships)
        cout << x->Destination() << ": " << (x->Validate() ? "ok" : "fail") << endl;
    return 0;
}

#endif /* __PROGTEST__ */
