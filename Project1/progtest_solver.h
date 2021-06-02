#ifndef PROGTEST_SOLVER_H_9128736516823541234
#define PROGTEST_SOLVER_H_9128736516823541234

#include <cstdint>
#include <vector>
#include "common.h"

//-------------------------------------------------------------------------------------------------
/**
 * A simple solver of the core problem. The function chooses the cargo from the input list such that:
 *  - the sum of weight does not exceed the limit,
 *  - the sum of volume does not exceed the limit, and
 *  - the sum of fees is as high as possible.
 * The function is available in the progtest environment, moreover, the implementation is supplied in 
 * the attached library (see the nested dirs).
 *
 * @param[in] cargoAvailable    the list of cargo to choose from
 * @param[in] maxWeight         the upper limit on the sum of cargo weight
 * @param[in] maxVolume         the upper limit on the sum of cargo volume
 * @param[out] cargoLoad        the cargo chosen from cargoAvailable
 * @return the sum of fees in cargoLoad.
 */
int ProgtestSolver(const std::vector<CCargo> &cargoAvailable,
                   int maxWeight,
                   int maxVolume,
                   std::vector<CCargo> &cargoLoad);

#endif /* PROGTEST_SOLVER_H_9128736516823541234 */
