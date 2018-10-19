#include "Bierwith.h"
#include <iostream>
using namespace std;

Bierwith::Bierwith(int n, int m)
{
    for(int i=0;i< n; i++)
    {
        for(int j=0; j <m; j++)
        {
            V.push_back(i);
        }
    }
    suffle();
    for(int i=0;i< n*m; ++i)
    {
        cout << V[i];

    }
}

void Bierwith::suffle()
{
    random_shuffle(V.begin(), V.end());
}

int Bierwith::operator[](int i)
{
    return V[i];
}

void Bierwith::value()
{

}
void Bierwith::eval()
{

}
