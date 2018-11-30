#ifndef METAHEURISTIQUE_H_INCLUDED
#define METAHEURISTIQUE_H_INCLUDED

#include "Data.h"
#include "Bierwith.h"

int VNS(Data& D,Bierwith& B);
void shaking(Bierwith& B, double alpha);
Bierwith& MultiStartRL(Data& D,Bierwith& B, int n=10);
int ILS(Data& D,Bierwith& S, int n=10);
Bierwith& GRASP(Data& D, Bierwith& B);

#endif // METAHEURISTIQUE_H_INCLUDED
