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
    lecture_instance(D, "la01.dat");
    D.afficher_instance();
    D.afficher();
    //D.afficher_solution_makespan();
    Bierwith B(D.get_n(), D.get_m());
    return 0;
}
