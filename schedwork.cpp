#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

static bool scheduleHelper(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCount,
    size_t day,
    size_t pos);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    
    if(avail.empty()){
        return false;
    }
    size_t n = avail.size();
    size_t k = avail[0].size();
    // Cannot need more workers than available
    if (dailyNeed > k) return false;

    // Initialize schedule and shift counts
    sched.clear();
    // Add your code below



    sched.assign(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shiftCount(k, 0);

    
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);
}

static bool scheduleHelper(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCount,
    size_t day,
    size_t pos
)
{
    size_t n = avail.size();
    size_t k = avail[0].size();

    
    if (day == n) return true;
    
    if (pos == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day + 1, 0);
    }

    for (Worker_T w = 0; w < k; ++w) {
    
        if (avail[day][w] && shiftCount[w] < maxShifts) {

            bool already = false;
            for (size_t i = 0; i < pos; ++i) {
                if (sched[day][i] == w) {
                    already = true;
                    break;
                }
            }
            if (already) continue;

            sched[day][pos] = w;
            ++shiftCount[w];

            
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day, pos + 1)) {
                return true;
            }

            --shiftCount[w];
            sched[day][pos] = INVALID_ID;
        }
    }

    return false;
}
