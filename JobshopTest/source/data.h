#pragma once

#ifndef CLASS_H
#define CLASS_H




#include "job.h"
#include "sequence.h"
#include <vector>
#include <random>
#include <map>


struct Data
{
  std::string name_;
  unsigned nbItems_;
  unsigned nbMachines_;
  std::vector< std::vector<Job> > jobs_;
  std::vector<Job*> first_;
  std::vector<Job*> last_;
  Job *  last_cp_; // TODO: mettre en in-class initialization
  unsigned makespan_;

  std::mt19937 rng_engine_;




  Data (const std::string &);

  unsigned assess(Sequence);

  void recherche_locale(Sequence &);

  std::vector<Job *> criticalPath();

  void afficherCP(std::vector<Job *>);

  bool ameliorer(Sequence &);

  void clear ();

  void display_all (std::ostream &) const;

  friend long Factoriel(long n);
};

std::ostream & operator<< (std::ostream &, const Data &);

long Factoriel(long n);




#endif