#include "node.h"

#include <algorithm>
#include <cassert>
#include <numeric>


Node::Node (unsigned i, double x, double y, double z): id_(0), public_id_(i), x_(x), y_(y), z_(z)
{
}


void Node::compute_neighbours (const std::vector<unsigned> & dist)
{
  // set the vector length
  const unsigned n = dist.size();
  assert((neighbours_.size() == n) && "error: wrong neighbours size");

  // sort the neighbours
  std::iota(neighbours_.begin(), neighbours_.end(), 0);
  std::sort(neighbours_.begin(), neighbours_.end(), [dist] (size_t i, size_t j) { return (dist[i] < dist[j]); } );

  // remove the node itself from the list, which is at the end
  assert((neighbours_[n - 1] == id_) && "error: last element in the neighbour list != elt");
  neighbours_.resize(n - 1);
}


void Node::check (const std::vector<unsigned> & dist) const
{
  for (size_t i = 0; i < neighbours_.size() - 1; ++i)
  {
    assert((dist[neighbours_[i]] <= dist[neighbours_[i+1]]) && "error: neighours list not in ascending order");
  }
}


std::ostream & operator<< (std::ostream & os, const Node & n)
{
  os << '(' << n.id() << ": " << n.x() << ',' << n.y() << ',' << n.z() << ')';
  return os;
}
