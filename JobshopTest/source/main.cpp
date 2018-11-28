#include <random> 
#include "data.h"
#include "metaheuristique.h"
#include <unistd.h>
#include <fstream>


using namespace std;




int main(int ,char** argv)
{
	srand(time(NULL));

	/* Stage 1 */
	/*
	Data d("INSTANCES/la01.dat");
	d.display_all(cout);
	cout << d <<endl;
	*/


	/* Stage 2  */
	/*
	// Initiliser un JS  
	Data d("INSTANCES/la01.dat");
	// Construire la séquence de Bierwith 
	Sequence s(d.nbItems_,d.nbMachines_);
	// Afficher la séquence sur la sortie standard 
	cout << s ;
	// Evaluer la séquence 
	unsigned v = d.assess(s);
	cout << v << endl;
	*/

	/* Stage 3 Evaluer + Extraire CP */
	/*
	Data d("INSTANCES/la01.dat");
	Sequence s(d.nbItems_,d.nbMachines_);
	cout << "Vecteur de Bierwith   : " << s ;
	cout << "La valeur de Makespan : " << d.assess(s)<< endl;
	std::vector<Job *> cp = d.criticalPath();
	cout << "Chemin critique : " << endl;
	d.afficherCP(cp);
	*/

	/* Stage 4 : La recherche Locale */
	/*
	Data d("INSTANCES/la01.dat");
	Sequence s(d.nbItems_,d.nbMachines_);
	cout << s;
	d.assess(s);
	cout << d.makespan_ << endl;
	d.recherche_locale(s);
	cout << d.makespan_ << endl;
	*/

	/* Stage 5: Les métaheuristiques*/
	
	// GRASP
	/*
	Data d(argv[1]);
	Sequence solution = MetaHeuristique::grasp(d);
	cout << d.assess(solution) << endl;
	*/


	// GENETIQUE
	/*
	Data d(argv[1]);
	Sequence solution = MetaHeuristique::genetique(d);
	cout << d.assess(solution) << endl;
	*/
	// ILS 
	/*
	Data d(argv[1]);
	Sequence solution = MetaHeuristique::ILS(d);
	cout << d.assess(solution) << endl;
	*/

	// VNS 
	/*
	Data d(argv[1]);
	Sequence solution = MetaHeuristique::VNS(d);
	cout << d.assess(solution) << endl;
	*/

  
	return 0;
}