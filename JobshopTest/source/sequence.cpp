#include "sequence.h"
#include <algorithm>




Sequence::Sequence (unsigned nbItems_,unsigned nbMachines_) 
{

	items_.resize(nbItems_*nbMachines_);
    
	for(unsigned i=0;i<nbItems_;++i)
  	{
  		for(unsigned j=nbMachines_*i; j<nbMachines_*(i+1); ++j)
  			items_[j] = i;
  	}

  	std::random_shuffle(items_.begin(), items_.end());
  
}


void Sequence::swap(unsigned in1,unsigned in2)
{
   std::iter_swap(items_.begin() + in1, items_.begin() + in2);
}

std::ostream & operator<< (std::ostream & os, const Sequence & d)
{
  for (unsigned i = 0; i < d.items_.size() ; ++i )
  {
    os << d.items_[i] << " ";
  }
  os << std::endl;
  return os;
}
