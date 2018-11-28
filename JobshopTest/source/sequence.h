
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

struct Sequence
{

  std::vector<unsigned> items_;
  
  Sequence(){};

  Sequence (unsigned,unsigned); 

  void swap(unsigned,unsigned);

  //bool ameliorer();

  void clear ();

  void display_all (std::ostream &) const;
};

std::ostream & operator<< (std::ostream &, const Sequence &);
