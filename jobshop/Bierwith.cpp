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

    /* Fixation du vecteur de Bierwith pour le test */
    V[0]=0; V[1]=2; V[2]=0; V[3]=1; V[4]=1; V[5]=2; V[6]=0; V[7]=1; V[8]=2;
    //V[0]=2; V[1]=0; V[2]=1; V[3]=0; V[4]=0; V[5]=1; V[6]=2; V[7]=1; V[8]=2;


    /*
    for(int i=0;i< n*m; ++i)
    {
        cout << V[i];

    }
    */
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
    //Date de debut des operations et le plus long chemin
    //vector<int> est;

}

vector<int> & Bierwith::get_V()
{
    return V;
}
int Bierwith::get_val()
{
    return val;
}
void Bierwith::set_val(int makespan)
{
    val = makespan;
}