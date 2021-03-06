#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "Operation.h"
#include "Bierwith.h"
#include <vector>
class Data
{
    protected:
        int n;
        int m;
        //std::vector< std::vector <Operation> > Op;
    public:
        std::vector<int> pere;
        std::vector< std::vector <Operation> > Op; // Violation de l'encapsulation
        int get_n(); void set_n(int nn);
        int get_m(); void set_m(int mm);
        int get_id_job(int id_op);
        int get_position(int id_op);
        int get_id_machine(int id_op);
        int indice_op_vecteur(Bierwith& V1, int id_op); //indice de l'id_op dans le vecteur de Bierwith
        void afficher();
        void afficher_instance();
        void afficher_solution_makespan();
        void afficher_matrice();
        int Evaluer(Bierwith& V, std::vector<int>& chemin_critique);
        Bierwith& Recherche_Locale(Bierwith& V, std::vector<int>& ch_cri,int n=3);
        void GRASP();
};

#endif // DATA_H_INCLUDED
