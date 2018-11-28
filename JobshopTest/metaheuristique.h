


#include "data.h"



class MetaHeuristique
{
	public :
	static Sequence grasp(Data &);
	static Sequence genetique(Data);
	static Sequence croisement(Sequence &,Sequence &,unsigned);
	static Sequence ILS(Data);
	static Sequence VNS(Data &);

};