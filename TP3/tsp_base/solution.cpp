#include "solution.h"

#include <algorithm>
#include <iterator>
#include <cassert>


const unsigned Solution::NO_SOLUTION = std::numeric_limits<unsigned>::max();
const unsigned Solution::NOBODY      = std::numeric_limits<unsigned>::max();


Solution::Solution (const Data & d): data_(d), next_(d.size()), prev_(d.size())
{
  clear();
}


void Solution::clear ()
{
  std::fill(prev_.begin(), prev_.end(), Solution::NOBODY);
  std::fill(next_.begin(), next_.end(), Solution::NOBODY);
  value_ = Solution::NO_SOLUTION;
}


void Solution::check () const
{
  //std::cout << "entering " << __PRETTY_FUNCTION__ << std::endl;

  // quick check
  if (value_ == NO_SOLUTION)
    return;

  const unsigned n = data_.size();
  std::vector<unsigned> cpt(n, 0);

  // check the chain on next
  unsigned node_id = 0;
  for (unsigned i = 0; i < n; ++i)
  {
    assert(cpt[node_id] == 0);
    ++cpt[node_id];
    node_id = next_[node_id];
  }

  // check the chain on prev
  node_id = 0;
  for (unsigned i = 0; i < n; ++i)
  {
    assert(cpt[node_id] == 1);
    --cpt[node_id];
    node_id = prev_[node_id];
  }

  // check the value
  unsigned value = 0.0;
  for (unsigned i = 0; i < n; ++i)
  {
    value += data_(i,next_[i]);
  }
  if (value != value_)
  {
    std::cerr << "error: mismatching values, got value_ = " << value_ << " and computed value = " << value << std::endl;
  }
  assert((value == value_) && "error: wrong value");

  //std::cout << "leaving " << __PRETTY_FUNCTION__ << std::endl;
}


// remove node i from the solution
void Solution::remove (unsigned i)
{
  assert((prev_[i] != Solution::NOBODY) && "error: node already removed");
  if (prev_[i] == i)
  {
    // solution becomes empty
    value_ = 0;
  }
  else
  {
    // solution is not empty
    next_[prev_[i]] = next_[i];
    prev_[next_[i]] = prev_[i];
    value_ -= data_(prev_[i], i) + data_(i, next_[i]);
    value_ += data_(prev_[i], next_[i]);
  }
  prev_[i] = next_[i] = Solution::NOBODY;
}


// insert node i in the empty solution
void Solution::insert(unsigned i)
{
//  std::cout << "entering " << __PRETTY_FUNCTION__ << std::endl;

//  std::cout << "insert " << i << " alone" << std::endl;

  assert((prev_[i] == Solution::NOBODY) && "error: node already inserted");
  assert((value_ == Solution::NO_SOLUTION) && "error: solution not empty");
  prev_[i] = next_[i] = i;
  value_ = 0;

//  std::cout << "leaving " << __PRETTY_FUNCTION__ << std::endl;
}


// insert the node i just after the node j
void Solution::insert(unsigned i, unsigned j)
{
//  std::cout << "entering " << __PRETTY_FUNCTION__ << std::endl;

//  std::cout << "insert " << i << " after " << j << std::endl;

  assert((prev_[i] == Solution::NOBODY) && "error: node already inserted");
  assert((prev_[j] != Solution::NOBODY) && "error: target is not inserted");
  prev_[next_[j]] = i;
  next_[i] = next_[j];
  next_[j] = i;
  prev_[i] = j;
  value_ -= data_(prev_[i], next_[i]);
  value_ += data_(prev_[i], i) + data_(i, next_[i]);

//  std::cout << "leaving " << __PRETTY_FUNCTION__ << std::endl;
}


// display all the info from the solution
void Solution::display (std::ostream & os) const
{
  os << "next = [";
  std::copy(next_.begin(), next_.end(), std::ostream_iterator<unsigned>(os, " "));
  os << "]\nprec = [";
  std::copy(prev_.begin(), prev_.end(), std::ostream_iterator<unsigned>(os, " "));
  os << "]\n val = ";
  if (value_ == Solution::NO_SOLUTION)
  {
    os << "none";
  }
  else
  {
    os << value_;
  }
}


// display the solution: node sequence and value
std::ostream & operator<< (std::ostream & os, const Solution & s)
{
  os << '[';
  std::copy(s.next_.begin(), s.next_.end(), std::ostream_iterator<unsigned>(os, " "));
  os << "] val = ";
  if (s.value_ == Solution::NO_SOLUTION)
  {
    os << "none";
  }
  else
  {
    os << s.value_;
  }

  return os;
}
