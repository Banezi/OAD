#include "Data.h"
#include <iostream>
#include <iomanip> // setw()
#include "Operation.h"
#include <cstdlib>
#include <time.h>

using namespace std;

int Data::get_n()
{
    return n;
}
void Data::set_n(int nn)
{
    n = nn;
}
int Data::get_m()
{
    return m;
}
void Data::set_m(int mm)
{
    m = mm;
}

void Data::afficher()
{
    cout << endl;
    cout << "\t";
    for(int i=0;i<m;i++)
        cout << "Operation" << i << "                       ";
    cout << endl<<endl;
    for(int i=0;i<m;i++)
        cout << "id id_mach duree id_job pos" << "\t";
    cout << endl << endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            //cout << "id \t id_machine \t duree \t id_job \t position" << endl;
            cout << setw(2) << setfill('0') << Op[i][j].get_id() << "    " << Op[i][j].get_id_machine() << "      " << Op[i][j].get_duree() << "    " << Op[i][j].get_id_job() << "     " << Op[i][j].get_position() << "\t";
        }
        cout << endl << endl;
    }

}

void Data::afficher_instance()
{
    cout << n << " " << m << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cout << Op[i][j].get_id_machine() << " " << Op[i][j].get_duree() << " " ;
        }
        cout << endl;
    }
}

void Data::afficher_matrice()
{
    cout << endl;
    for(int i=0;i<m;i++)
        cout << "Operation" << i << "\t";
    cout << endl<<endl;
    for(int i=0;i<m;i++)
        cout << "id_mach duree" << "\t";
    cout << endl << endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            //cout << "id \t id_machine \t duree \t id_job \t position" << endl;
            cout << Op[i][j].get_id_machine() << "      " << Op[i][j].get_duree() << "\t";
        }
        cout << endl << endl;
    }
}

void Data::afficher_solution_makespan()
{
    //Disjonction
    vector< vector<int> > M;
    M.resize(n);
    for(int i=0; i<m; i++)
        M[i].resize(m);
}

void Data::Evaluer(Bierwith & V)
{
    afficher_matrice();
    afficher();
    cout << "V = " ;
    for(int i=0; i< n*m; i++)
    {
        cout << V[i] << " ";
    }
    cout << endl;

    vector<int> Job(n,-1); //Nombre d'opération traité par chaque job . Job[i] = 0 : 1ere operation du job i
    vector<int> Mach(m,-1); //Dernière operation traitée sur la machine
    vector<int> id_pere(n*m, -2); // -2 : non traité   -1 : origine
    vector<int> EST(n*m, -1); //date de debut au plutôt   -1:non traité

    for(int i=0; i<n*m ; i++)
    {
        cout << endl << endl << "\t\tIteration : " << i+1 << endl;
        cout << "V["<<i<<"] = " << V[i] << endl;
        Job[V[i]] = Job[V[i]] + 1;
        Operation operation = Op[V[i]][Job[V[i]]];
        cout << "ID Operation Globale : " << operation.get_id() << endl;
        cout << "Machine utilisee : "<< operation.get_id_machine() << endl;
        if(id_pere[operation.get_id()] == -2 || id_pere[operation.get_id()] == -1)
        {
            id_pere[operation.get_id()] = Mach[operation.get_id_machine()];
        }

        /* -------- */
        /* Op[id_pere[operation.get_id()]/m][id_pere[operation.get_id()]%m].get_duree() */
        /* -------- */

        Mach[operation.get_id_machine()]=operation.get_id();

        cout << "Job " << V[i] << " : Operation " << Job[V[i]] << endl;

        // Affichage de Job
        for(int i=0; i< n; i++)
        {
            cout << "Job[" << i << "]=" << Job[i] << "\t";
        }
        cout << endl;

        // Affichage de Mach
        for(int i=0; i< m; i++)
        {
            cout << "Mach[" << i << "]=" << Mach[i] << "\t";
        }
        cout << endl;

        // Affichage de id_pere
        for(int i=0; i< n*m; i++)
        {
            cout << "id_pere[" << i << "]=" << id_pere[i] << "\t";
        }
        cout << endl;

        // Affichage de EST
        for(int i=0; i< n*m; i++)
        {
            cout << "EST[" << i << "]=" << EST[i] << "\t";
        }
        cout << endl;



    }

}
