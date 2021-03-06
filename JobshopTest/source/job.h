#pragma once

#include <iostream>
#include <limits>


struct Job
{
    static const unsigned NO_TIME;
    static const unsigned NO_LOCATION;

  unsigned item_;
  unsigned machine_;
  unsigned duration_;

  Job * next_;        // TODO: set an in-class initialization
  Job * prev_;        // TODO: set an in-class initialization
  Job * father_;      // TODO: set an in-class initialization
  unsigned starting_; // TODO: set an in-class initialization
  unsigned location_; // TODO: set an in-class initialization

  
  unsigned positionBierwith;
  
  Job () : item_(0), machine_(0), duration_(0), next_(0), prev_(0), father_(0), starting_(0), location_(NO_LOCATION) {}
  //Job (unsigned i, unsigned m, unsigned d) : item_(i), machine_(m), duration_(d), next_(0), prev_(0), father_(0), starting_(NO_TIME) {}
  
  void clear () {next_ = prev_ = father_ = 0; starting_ = NO_TIME; location_ = NO_LOCATION;}

  void display_all (std::ostream &) const;
};

std::ostream & operator<< (std::ostream &, const Job &);
