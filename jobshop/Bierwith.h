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
};

#endif // BIERWITH_H_INCLUDED
