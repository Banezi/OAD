#include <iostream>
#include "instance.h"
#include "Bierwith.h"
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <iterator>
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
    /*
    cout << "Notre chemin critique : ";
    copy(ch_cri.begin(), ch_cri.end(), ostream_iterator<int>(cout, " "));
    cout << endl ;
    */
    Bierwith V1(D.get_n(), D.get_m());
    vector<int> S;
    D.Recherche_Locale(V1,S,3);
    return 0;
}
