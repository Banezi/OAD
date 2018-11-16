#include "bkr.h"

#include "data.h"

#include <fstream>
#include <algorithm>
#include <limits>


const std::string BKR::BKR_FILE = "../tsp_base/BKR.txt";
const unsigned BKR::NO_VALUE = std::numeric_limits<unsigned>::infinity();


BKR::BKR(): value_(BKR::NO_VALUE)
{
}


void BKR::load (const std::string & filename)
{
  // initialization
  value_ = std::numeric_limits<unsigned>::max();

  // get the instance name
  size_t first = filename.rfind('/');
  if (first == std::string::npos) first = 0; else ++first;
  size_t length = filename.rfind('.');
  if (length != std::string::npos) length -= first;
  std::string instance(filename.substr(first, length));
  std::transform(instance.begin(), instance.end(), instance.begin(), ::toupper);
  //std::cout << "instance = " << instance << std::endl;

  // open the BKR file
  std::ifstream is(BKR_FILE);
  if (!is.is_open())
  {
    std::cerr << "Error: unable to open \"" << BKR_FILE << "\"" << std::endl;
  }

  // loop over the records
  //std::cout << "looking for " << instance << std::endl;
  do
  {
    std::string record_name;
    unsigned record_value;

    // read the first two information
    is >> record_name >> record_value;
    std::transform(record_name.begin(), record_name.end(), record_name.begin(), ::toupper);
    //std::cout << "read " << record_name << ' ' << record_value << std::endl;

    if (record_name == instance)
    {
      value_ = record_value;
      //std::cout << "    found " << record_name << ' ' << record_value << std::endl;
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
  if (bkr.value_ == BKR::NO_VALUE)
  {
    os << "none";
    return os;
  }

  os << bkr.value_;
  return os;
}
