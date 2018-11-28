#include <iostream>
#include "instance.h"
#include "Bierwith.h"
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <iterator>
#include "metaheuristique.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Data D;
    lecture_instance(D, "la00.dat");
    //D.afficher_instance();
    //D.afficher();
    //D.afficher_solution_makespan();
    Bierwith V(D.get_n(), D.get_m());
    vector<int> ch_cri;
    D.Evaluer(V, ch_cri);
    D.Recherche_Locale(V,ch_cri,3);
    //VNS(D, V);
    return 0;
}
