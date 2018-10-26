#include <iostream>
#include "instance.h"
#include "Bierwith.h"
#include <cstdlib>
#include <time.h>
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
    D.Evaluer(V);
    return 0;
}
