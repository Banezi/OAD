#include "metaheuristique.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "algorithm"
using namespace std;

int VNS(Data& D,Bierwith& B)
{
    cout <<endl<<endl;
    cout << "||===================================================||" <<endl;
    cout << "||                          VNS                      ||" << endl;
    cout << "||===================================================||" <<endl <<endl;

    Bierwith S(B);
    Bierwith S1(S);
    vector<int> ch_cri;
    D.Recherche_Locale(S,ch_cri);
    double alpha=0.05;
    while(alpha < 1)
    {
        shaking(S1, alpha);
        cout << "sortie shaking" << endl;
        D.Recherche_Locale(S1,ch_cri);
        if(S1.get_val()<S.get_val())
        {
            S = S1;
            alpha = 0.05;
        }
        else
        {
            alpha += 0.05;
        }
    }
    return S.get_val();
}
void shaking(Bierwith& B, double alpha)
{
    int i=0,j=0;
    while(abs(i-j)!= alpha*B.get_V().size())
    {
        i=rand()%B.get_V().size();
        j=rand()%B.get_V().size();
    }
    if(i<j)
        random_shuffle(B.get_V().begin()+i, B.get_V().begin()+j);
    else
        random_shuffle(B.get_V().begin()+j, B.get_V().begin()+i);
}
Bierwith& MultiStartRL(Data& D,Bierwith& S, int n)
{
    int best = INT_MAX;
    vector<int> ch_cri;
    for(int i=0; i<n; i++)
    {
        random_shuffle(S.get_V().begin(), S.get_V().end());
        D.Recherche_Locale(S,ch_cri);
        if(S.get_val()<best)
            best = S.get_val();
    }
    return S;
}
int ILS(Data& D,Bierwith& S, int n)
{
    vector<int> ch_cri;
    Bierwith S1(S);
    D.Recherche_Locale(S,ch_cri);
    for(int i=0; i<n; i++)
    {
        shaking(S1,0.01);
        D.Recherche_Locale(S1,ch_cri);
        if(S1.get_val()<S.get_val())
            S = S1;
    }
    return S.get_val();
}
