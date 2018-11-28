/*
#include "bkr.h"

//#include <string>
#include <fstream>
#include <algorithm>


const std::string BKR::BKR_FILE = "BKR.txt";


BKR::BKR (const Data & d)
{
  // initialization
  makespan_ = std::numeric_limits<unsigned>::max();

  // get the instance name
  size_t first = d.name_.rfind('/');
  if (first == std::string::npos) first = 0; else ++first;
  size_t length = d.name_.rfind('.');
  if (length != std::string::npos) length -= first;
  std::string instance(d.name_.substr(first, length));
  std::transform(instance.begin(), instance.end(), instance.begin(), ::toupper);
  //std::cout << "instance = " << instance << std::endl;

  // open the BKR file
  std::ifstream is(BKR_FILE);
  if (!is.is_open())
  {
    std::cerr << "Error: unable to open \"" << instance << "\"" << std::endl;
  }

  // loop over the records
  do
  {
    std::string record_name;
    unsigned record_makespan;

    // read the first two information
    is >> record_name >> record_makespan;
    //std::cout << "read " << record_name << ' ' << record_makespan << std::endl;

    if (record_name == instance)
    {
      makespan_ = record_makespan;
      break;
    }

    // skip the end of the line
    std::string line;
    getline(is, line);
  } while (!is.eof());

  // close the BKR file
  is.close();
}


std::ostream & operator<< (std::ostream & os, const BKR & bkr)
{
  os << bkr.makespan_;
  return os;
}
*/
