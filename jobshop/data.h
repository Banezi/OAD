#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "Operation.h"
#include <vector>
class Data
{
    protected:
        int n;
        int m;
        //std::vector< std::vector <Operation> > Op;
    public:
        std::vector< std::vector <Operation> > Op; // Violation de l'encapsulation
        int get_n(); void set_n(int nn);
        int get_m(); void set_m(int mm);
        void afficher();
        void afficher_instance();
        void afficher_solution_makespan();
};

#endif // DATA_H_INCLUDED
