#ifndef BIERWITH_H_INCLUDED
#define BIERWITH_H_INCLUDED

#include <vector>
#include <algorithm> // shuffle

class Bierwith
{
    protected:
        std::vector <int> V;
        int val; //makespan calculé par la methode eval
    public:
        Bierwith(int n, int m);
        void suffle();
        int operator[](int);
        void value();
        void eval();

        std::vector<int> & get_V();
        int get_val(); void set_val(int makespan);
};

#endif // BIERWITH_H_INCLUDED
