#include "metaheuristique.h"

using namespace std;

Sequence MetaHeuristique::grasp(Data & d)
{
    unsigned solution = std::numeric_limits<unsigned>::max();
    Sequence result;
	for(unsigned i = 0;i<1000;++i)
	{
		Sequence s(d.nbItems_,d.nbMachines_);
		d.assess(s);
		d.recherche_locale(s);
		if(d.makespan_ < solution)
		{
			solution = d.makespan_;
			result = s;
		}
		d.clear();
	}
	return result;
}


Sequence MetaHeuristique::genetique(Data d )
{
	// La map qui va contenir les solutions : clé->makespan , valeur->solution
	std::map<unsigned,Sequence> s;
	map<unsigned,Sequence>::iterator it;
	int i;
	unsigned j,count=0;
	std::vector<unsigned> restart1(5,0),restart2(5,0);
	std::uniform_int_distribution<> dis1(1, 5);
	std::uniform_int_distribution<> dis2(6, 30);
	std::random_device rd;
	std::mt19937 rng_engine_(rd());


	// Evaluation des solutions générées + leur insertion dans la map selon la valeur du makespan
	for( i = 0;i<30;++i)
	{
		Sequence solution(d.nbItems_,d.nbMachines_);

		d.assess(solution);

		d.recherche_locale(solution);

		s[d.makespan_] = solution;

		d.clear();
	}

	// Copier les 5 premières solutions pour la procédure de RESTART
	// C-à-d les garder, pour détecter l'invariance des premièrs éléments 
	// au bout d'un moment.
	i = 0;
	for(map<unsigned,Sequence>::iterator it = s.begin();i<5;++it,++i)
	{
		restart1[i] = it->first;
	}


	for(unsigned k =0 ;k<500;++k)
	{	
		// Eextraire une solution des 5 premiers
		i =0;
		for(it=s.begin(); i< dis1(rng_engine_); ++it,++i );	
		Sequence s1 = it->second;
		// Extraire une autre solution du reste dee la population
		i =0;
		for(it=s.begin(); i< dis2(rng_engine_); ++it,++i );
		Sequence s2 = it->second;
		// Croiser les deux solutions
		Sequence s3 = MetaHeuristique::croisement(s1,s2,d.nbMachines_);		
		// Evaluer la nouvelle solution et effectuer une recherche locale
		d.assess(s3);
		d.recherche_locale(s3);
		s[d.makespan_] = s3;
		d.clear();
		// Méthode de RESTART
		i = 0;
		for(it = s.begin();i<5;++it,++i)
		{
			restart2[i] = it->first;
		}
		if(equal(restart1.begin(),restart1.end(),restart2.begin()))
			++count;
		else
		{
			count = 0;
			restart1 = restart2;
		}
		if(count==5)
		{
			std::cout << "RESTART METHOD WAS CALLED" << std::endl;
			//MetaHeuristique::Restart(d,s);
			for(j = 6;j<30;++j)
			{
				Sequence solution(d.nbItems_,d.nbMachines_);

				d.assess(solution);

				d.recherche_locale(solution);

				s[d.makespan_] = solution;

				d.clear();
			}
			count = 0;
			j = 0;
			for(map<unsigned,Sequence>::iterator it = s.begin();i<5;++it,++i)
			{
				restart1[i] = it->first;
			}
		}

	}
	i = 0;
	for(map<unsigned,Sequence>::iterator it2=s.begin(); /*it2!=s.end()*/ i < 1 ; ++it2,++i )
	{
		//cout << it2->first << " " << it2->second ;
	}

  return (s.begin()->second);
}



Sequence MetaHeuristique::croisement(Sequence & s1,Sequence & s2,unsigned nb_items)
{
	Sequence s3;
	for(unsigned i=0;i<s1.items_.size()/2;++i)
	{
		s3.items_.push_back(s1.items_[i]);
	}
	//unsigned j = s1.size()/2;
	for(unsigned i=0 ;i<s2.items_.size();++i)
	{
		unsigned occ = 0;
		for(auto p : s3.items_)
		{
			if(p==s2.items_[i])
				++occ;
		}
		if(occ < nb_items){
			s3.items_.push_back(s2.items_[i]);
		}
	}
	return s3;
}

Sequence MetaHeuristique::ILS(Data d)
{
	unsigned result = std::numeric_limits<unsigned>::max();
	Sequence s(d.nbItems_,d.nbMachines_);
	Sequence s1;

	for(unsigned i = 0 ;i<1000;++i)
	{
		s1 = s;
		if(i>0)
			std::random_shuffle(s1.items_.begin(), s1.items_.end());

		d.assess(s1);

		d.recherche_locale(s1);

		//std::cout << val << std::endl;

		if( result > d.makespan_)
		{
			s = s1;
			result = d.makespan_;
			//std::cout << result << std::endl;
		}

		d.clear();

	}
	return s;
}


Sequence MetaHeuristique::VNS(Data & d)
{
	unsigned result = std::numeric_limits<unsigned>::max();
	Sequence s(d.nbItems_,d.nbMachines_);
	Sequence s1;

	for(unsigned i = 1 ;i<10000;++i)
	{
		s1 = s;
		if(i>0)
			std::random_shuffle(s1.items_.begin(), s1.items_.end());

		d.assess(s1);

		d.recherche_locale(s1);

		if( result > d.makespan_)
		{
			i = 1;
			s = s1;
			result = d.makespan_;
			//std::cout << result << std::endl;
		}
		else
			++i;

		d.clear();

	}
	return s;
}
















