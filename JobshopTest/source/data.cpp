#include "data.h"

#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>

Data::Data (const std::string & filename) : name_(filename), jobs_(0), last_cp_(0)
{
  std::ifstream is(filename.c_str());

  if (!is)
  {
    std::cerr << "Error: unable to open file \'" << filename << "\'" << std::endl;
    exit (EXIT_FAILURE);
  }

  // step over the first line
  std::string line;
  getline(is, line);

  // get the instance size
  is >> nbItems_ >> nbMachines_;
  
  // memory allocation
  jobs_.resize(nbItems_);
  for (unsigned i = 0; i < nbItems_; ++i)
  {
    jobs_[i].resize(nbMachines_);
  }
  first_.resize(nbMachines_);
  last_.resize(nbMachines_);

  // get the information
  for (unsigned i = 0; i < nbItems_; ++i)
  {
    for (unsigned m = 0; m < nbMachines_; ++m)
    {
      Job & job = jobs_[i][m];
      job.item_ = i;
      is >> job.machine_ >> job.duration_;
    }
  }
}


unsigned Data::assess(Sequence s)
{

  /* Vecteur des indices des opérations prochaines à traiter pour chaque job */
  std::vector<unsigned> availableOp(nbItems_,0);

  /* Vecteur des pointeurs sur les dernières opérations traitées par la machine */
  std::vector<Job *> lastOp(nbMachines_,0);

  unsigned currentJob;
  unsigned currentIndex;
  unsigned currentMachine;

  for(unsigned i = 0; i < s.items_.size() ; ++i)
  {
    /* Lire l'élément i du vecteur du Bierwith */
    currentJob   = s.items_[i];
    /* Chercher l'indice de l'opération en attente */
    currentIndex = availableOp[currentJob];
    /* Se positionner sur l'opération an attente du traitement */
    Job & currentOp  = jobs_[currentJob][currentIndex];
    /* On en aura besoin dans le parcours */
    currentOp.location_ = currentIndex;
    /* Récupérer le numéro de la machine */
    currentMachine = currentOp.machine_;
    /*Affecter la position dans le vecteur de Bierwith*/
    currentOp.positionBierwith = i;


    // Tester les noeuds successeurs de 0
    if(currentIndex == 0)
    {
        currentOp.prev_     = 0;
        currentOp.starting_ = 0;
    }
    else
    {
        if(lastOp[currentMachine] == 0 )
        {
            currentOp.starting_ = jobs_[currentJob][currentIndex-1].starting_ + jobs_[currentJob][currentIndex-1].duration_;
            currentOp.father_   = &jobs_[currentJob][currentIndex-1];
        }
    }
    // Tester si la machine est occupée
    if(lastOp[currentMachine] != 0 )
    {
        currentOp.prev_     = lastOp[currentMachine];
        if(currentIndex == 0 ){
            currentOp.starting_ = currentOp.prev_->starting_ + currentOp.prev_->duration_;
            currentOp.father_   = currentOp.prev_;
        }
        /* Calculer la date de démarrage pour l'opération actuelle et préciser le father */
        else if(currentOp.prev_->starting_ + currentOp.prev_->duration_ > jobs_[currentJob][currentIndex-1].starting_ + jobs_[currentJob][currentIndex-1].duration_)
        {
            currentOp.starting_ = currentOp.prev_->starting_ + currentOp.prev_->duration_;
            currentOp.father_   = currentOp.prev_;
        }
        else
        {
            currentOp.starting_ = jobs_[currentJob][currentIndex-1].starting_ + jobs_[currentJob][currentIndex-1].duration_;
            currentOp.father_   = &jobs_[currentJob][currentIndex-1];
        }
        
        lastOp[currentMachine]->next_ = &currentOp;
    }

    //std::cout << currentJob << "-" << currentMachine << std::endl;
    //std::cout << currentOp.starting_ << std::endl;

    // Mettre à jour availableOp
    ++availableOp[currentJob];

    // Mettre à jour lastOp 
   lastOp[currentMachine] = &currentOp;
 }

 unsigned max = 0;
 for(unsigned i = 0;i < nbItems_ ; ++i)
 {
    if(max < jobs_[i][nbMachines_ - 1].starting_ + jobs_[i][nbMachines_ - 1].duration_)
    {
        max = jobs_[i][nbMachines_ - 1].starting_ +  jobs_[i][nbMachines_ - 1].duration_;
    }
 }
    //std::cout << jobs_[0][nbMachines_ - 1].starting_ ;
makespan_ = max;
return max;

}





std::vector<Job *> Data::criticalPath()
{
  std::vector<Job *> CC;//(1,0); 
  //std::cout << "******" << CC.size() << std::endl;
  Job * CP = NULL;
  //unsigned max;
  // Repérer un sommet sur la dernière colonne
  for(unsigned i = 0;i < nbItems_ ; ++i)
  {
      if(jobs_[i][nbMachines_-1].starting_ + jobs_[i][nbMachines_-1].duration_ == makespan_)
      {
        CP = &jobs_[i][nbMachines_-1];
        CC.push_back(CP);
      }
  }
  
  while(CP!=0)
  {
      CP = CP->father_; 
      if(CP != 0)
      CC.push_back(CP);
  }
  std::reverse(CC.begin(),CC.end());
  return CC;
}

void Data::afficherCP(std::vector<Job *> cp)
{

    for (auto & op : cp)
    {
      std::cout << "(" << op->item_ << "," << op->location_ << ")" << std::endl;
    }
}


 bool Data::ameliorer(Sequence & alpha)
 {
    bool improve = false;
    std::vector<Data> JS;
    JS.push_back(*this);
    std::vector<unsigned> optimal;
    unsigned solution = makespan_;
    // Liste qui va contenir les indices des éléments dans le vecteur de Bierwith à permuter
    std::vector<unsigned> permutable;
    std::vector<Job *> cp = criticalPath();
    // Construire la liste des arcs dijonctifs
    for(auto p : cp)
    {
      if(p->father_ != &jobs_[p->item_][p->location_-1] && p->father_ != 0 )
      {
          permutable.push_back(p->father_->positionBierwith);
          permutable.push_back(p->positionBierwith);
      }
    }
    // 
    for(std::vector<unsigned>::iterator it = permutable.begin(); it!=permutable.end(); ++it){
        unsigned in1 = *it;
        ++it;
        unsigned in2 = *(it);
        alpha.swap(in1,in2);
        //std::cout << alpha;    // On accède à l'élément pointé via l'étoile
        clear();
        unsigned out = assess(alpha);
        if(out < solution)
        {
          solution = out;
          JS.push_back(*this);
          improve = true;
        }
        else
        {
          alpha.swap(in2,in1);
          *this = JS[JS.size()-1];
        }
    }

    return improve;
 }

void Data::recherche_locale(Sequence & alpha)
{
    bool stop = false;
    while(!stop)
    {
        if(ameliorer(alpha)==false)
          stop = true;
    }
}
















void Data::clear ()
{
  for (auto & line : jobs_)
  {
    for (auto & elt : line)
    {
      elt.clear();
    }
  }
  for (auto & jobptr : first_)
  {
    jobptr = 0;
  }
  for (auto & jobptr : last_)
  {
    jobptr = 0;
  }
  last_cp_ = 0;
  //makespan_ = Job::NO_TIME;
}


void Data::display_all (std::ostream & os) const
{
  os << "instance " << name_ << ": " << nbItems_ << " items " << nbMachines_ << " machines" << std::endl;
  for (auto & line : jobs_)
  {
    for (auto & job : line)
    {
      job.display_all(os);
    }
    os << std::endl;
  }
  os << "last_cp = ";
  if (last_cp_ == 0)
  {
    os << "null";
  }
  else
  {
    last_cp_->display_all(os);
  }
  os << std::endl;
}


std::ostream & operator<< (std::ostream & os, const Data & d)
{
  os << "instance " << d.name_ << ": " << d.nbItems_ << " items " << d.nbMachines_ << " machines" << std::endl;
  for (auto & line : d.jobs_)
  {
    for (auto & job : line)
    {
      os << ' ' << job.machine_ << ' ' << job.duration_;
    }
    os << std::endl;
  }
  return os;
}


long Factoriel(long n) {
   return n > 1?(n * Factoriel(n-1)):1;
}