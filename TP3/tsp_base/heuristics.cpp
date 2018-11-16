#include "heuristics.h"

#include "solution.h"

#include <algorithm>


// H1: create the natural sequence (0, 1, 2 ..., n-1)
void H1_heuristic (Solution & sol)
{
  // initialization
  sol.clear();

  // main loop
  sol.insert(0);
  for (unsigned i = 1; i < sol.size(); ++i)
  {
    sol.insert(i, i - 1);
  }
}


int twoOpt (Solution & sol)
{
  //std::cout << "entering " << __PRETTY_FUNCTION__ << std::endl;
  int delta = 0;
  const Data & data = sol.data();

  // scan for an improving 2opt
  unsigned best_i, best_j;
  unsigned start_i = 0;
  unsigned next_i = sol.next(0);
  unsigned stop_i = sol.prev(sol.prev(0));
  for (unsigned i = start_i; i != stop_i; i = next_i, next_i = sol.next(next_i))
  {
    unsigned start_j = sol.next(next_i);
    unsigned next_j = sol.next(start_j);
    unsigned stop_j = ((i == start_i) ? stop_i : sol.prev(start_i));
    for (unsigned j = start_j; j != stop_j; j = next_j, next_j = sol.next(next_j))
    {
      delta = int(data(i,next_i) + data(j,next_j)) - int(data(i,j) + data(next_i,next_j));
      if (delta > 0)
      {
          best_i = i;
          best_j = j;

          // std::cout << "2opt: got an improvement, gain = " << delta << " on i = " << i << " and  j = " << j << std::endl;
          goto twoOpt_update;
      }
    }
  }

  // check for an improving 2opt
  if (delta > 0)
  {
    twoOpt_update:
    // found one
    unsigned i = best_i;
    next_i = sol.next(i);
    unsigned j = best_j;
    unsigned next_j = sol.next(j);

    // revert the segment next_i -> j
    for (unsigned k = next_i; k != next_j; k = sol.prev((k)))
    {
      std::swap(sol.prev(k), sol.next(k));
    }

    // set the connections (i,j) (next_i,next_j)
    sol.next(i) = j; sol.prev(j) = i;
    sol.next(next_i) = next_j; sol.prev(next_j) = next_i;
    sol.value() -= delta;

    sol.check();
  }

  //std::cout << "leaving " << __PRETTY_FUNCTION__ << std::endl;

  return std::max(delta,0);
}

// ========================================
// Nearest Neighbor
// ========================================
void Nearest_Neighbor(Solution& s)
{

}

/* ======================================================================= */
/* end of file                                                             */
/* ======================================================================= */
