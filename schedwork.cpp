//schedwork.cpp

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool recursiveHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& numShifts, size_t nextWorkerID);
//void printSchedule2(const DailySchedule& sched);


// Add your implementation of schedule() and other helper functions here

bool recursiveHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& numShifts, size_t nextWorkerID)
{
  
  //base cases

  //check if the schedule is fully complete
  if(sched.size() == avail.size() && sched[sched.size()-1].size() == dailyNeed)
  {
    	return true;
  }
  
  // if we ran out of workers for today - if the id is invalid
  if(nextWorkerID >= avail[0].size())
  {
    return false;
  }
  
  //if number of shifts exceeds the max shifts allowed
  if (numShifts[nextWorkerID] >= maxShifts)
  {
    return false;
  }
  
  if(sched.size() == 0)
  {
    // for the first day, we're gonna add a blank day
    sched.push_back(std::vector<Worker_T>());
  }
  
  //if no possible solutions from this point
  // get availabilities for today
  const std::vector<bool> availToday = avail[sched.size() - 1];
  if (availToday[nextWorkerID] == false)
  {
    return false;
  }
  
  // fill in today's spot with the given worker
  sched[sched.size()-1].push_back(nextWorkerID);
  numShifts[nextWorkerID]++;
  //printSchedule2(sched);
  
  // if the schedule is complete, now return true
  if(sched.size() == avail.size() && sched[sched.size()-1].size() == dailyNeed)
  {
    	return true;
  }
  
  //sched[sched.size()-1] represents workers we've scheduled for today
  // continue our recursion - branch our behavior based on whether the day is complete or not
  if (sched[sched.size()-1].size() == dailyNeed)
  {
    // add a new empty day to the end of the schedule/ new row
    sched.push_back(std::vector<Worker_T>());
    for(size_t i = 0 ; i < numShifts.size() ; i++)
    {	
      // if we find a solution this way, return true
      //each recursive step will fill in one slot in the schedule
      if(recursiveHelper(avail, dailyNeed, maxShifts, sched, numShifts, i))
      {
        return true;
      }
    }
    
    // if we get to this point, there was no solution from our current point
    //change schedule and numshifts back
    sched.pop_back();
    numShifts[nextWorkerID]--;
    sched[sched.size()-1].pop_back();
    
    // backtracking
    
    return false;
  }
  
  //else the day is not complete
  else
  {
    for(size_t i = nextWorkerID + 1 ; i < numShifts.size() ; i++)
    {	
      // if we find a solution this way, return true
      //each recursive step will fill in one slot in the schedule
      if(recursiveHelper(avail, dailyNeed, maxShifts, sched, numShifts, i))
      {
        return true;
      }
    }
    
    // if we get to this point, there was no solution from our current point
    //change schedule and numshifts back
    numShifts[nextWorkerID]--;
    sched[sched.size()-1].pop_back();
    
    // backtracking
    
    return false;
  }

  
  
}


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
		try
    {
      if(avail.size() == 0U){
          return false;
      }
      sched.clear();
      // Add your code below
      std::vector<size_t> numShifts; //(avail[0].size());
      for(unsigned int i = 0 ; i < avail[0].size() ; i++)
      {
      	numShifts.push_back(0);
      }
      
      for(size_t i = 0 ; i < numShifts.size() ; i++)
      {
        if(recursiveHelper(avail, dailyNeed, maxShifts, sched, numShifts, i))
        {
        	return true;
        }
      }
    }
    catch(std::bad_alloc& e)
    {
    	cout << "Exception: " << e.what() << endl;
    
    }
    
    return false;
}

/*void printSchedule2(const DailySchedule& sched)
{
    int day = 0;
    for(auto s : sched)
    {
        cout << "Day " << day << ": ";
        for(auto nurse : s)
        {
            cout << nurse << " ";
        }
        cout << endl;
        day++;
    }
    cout<<endl;
}*/