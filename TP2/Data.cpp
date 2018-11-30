#include "Data.h"
#include <iostream>
#include <iomanip> // setw()
#include "Operation.h"
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <cstdio>
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

int Data::get_id_job(int id_op)
{
    return Op[id_op/m][id_op%m].get_id_job();
}

int Data::get_id_machine(int id_op)
{
    return Op[id_op/m][id_op%m].get_id_machine();
}

int Data::get_position(int id_op)
{
    return Op[id_op/m][id_op%m].get_position();
}

int Data::indice_op_vecteur(Bierwith& V1, int id_op)
{
    int id_job=get_id_job(id_op);
    int pos=get_position(id_op);
    //Recherche de l'indice dans le vecteur de bierwith
    int npos=0, indice;
    for(int i=0; i<V1.get_V().size(); i++)
    {
        if(V1.get_V()[i]==id_job)
        {
            npos++;
            if(npos==pos+1)
            {
                indice=i;
                break;
            }
        }
    }
    return indice;
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

int Data::Evaluer(Bierwith & V, vector<int>& chemin_critique)
{
    //afficher_matrice();
    //afficher();
    //Cr�ations des s�quences
    vector < vector<int> > sequence;
    sequence.resize(n);
    for(int i=0; i<m; i++)
        sequence[i].resize(m);

    vector<int> ni(n,0); // n[i]=k : k�me apparution de i dans le vecteur de Bierwirth
    for(int i=0; i<n*m; i++)
    {
        //cout << "\t*sequence[" << V[i] << "][" << ni[V[i]] << "] = " << Op[V[i]][ni[V[i]]].get_id_machine() << endl;
        sequence[V[i]][ni[V[i]]] = Op[V[i]][ni[V[i]]].get_id_machine();
        ni[V[i]]++;
    }
    /*for(int i=0; i<n; i++)
        for(int j=0;j<m; j++)
            cout << "sequence["<<i<<"]["<<j<<"] = " << sequence[i][j] << endl;
    */

    vector<int> Job(n,-1); //Nombre d'op�ration trait� par chaque job . Job[i] = 0 : 1ere operation du job i
    vector<int> Mach(m,-1); //Derni�re operation trait�e sur la machine
    vector<int> id_pere(n*m, -2); // -2 : non trait�   -1 : origine
    vector<int> EST(n*m, -1); //date de debut au plut�t   -1:non trait�
    pere.resize(n*m);

    for(int i=0; i<n*m ; i++)
    {
        /*cout << endl << endl << "\t\tIteration : " << i+1 << endl;
        cout << "V["<<i<<"] = " << V[i] << endl;*/
        Job[V[i]] = Job[V[i]] + 1;
        Operation operation = Op[V[i]][Job[V[i]]];
        /*cout << "ID Operation Globale : " << operation.get_id() << endl;
        cout << "Machine utilisee : "<< operation.get_id_machine() << endl;*/
        if(id_pere[operation.get_id()] == -2 )
        {
            //cout << "------------------> operation.get_idmachine() = " << operation.get_id_machine() << " et Mach[opgetidmach] = " << Mach[operation.get_id_machine()] << endl;
            //cout << "Avant : Mach[operation.get_id_machine()] = " << Mach[operation.get_id_machine()] << endl;
            id_pere[operation.get_id()] = Mach[operation.get_id_machine()];
            pere[operation.get_id()] = Mach[operation.get_id_machine()];

            if(Mach[operation.get_id_machine()] == -1 && operation.get_position()!=0)
            {
                //cout << "\t\t\t\t\t\t\t*!*!*!*!**!*!*!*! Alerte Point sensible *!*!*!*!*!*!" << endl;
                id_pere[operation.get_id()] = operation.get_id() - 1;
                pere[operation.get_id()] = operation.get_id() - 1;
            }
            if(operation.get_id_machine() >= 0 && Mach[operation.get_id_machine()] >= 0)
            {
                Operation precedentb = Op[Mach[operation.get_id_machine()]/m][Mach[operation.get_id_machine()]%m];
                Operation precedent = Op[(operation.get_id()-1)/m][(operation.get_id()-1)%m];
                if(EST[precedentb.get_id()]+precedentb.get_duree() < EST[precedent.get_id()] + precedent.get_duree() )
                {
                    //cout << "\t\t\t\t\t\t\t*!*!*!*!**!*!*!*! Alerte Point sensible 2 *!*!*!*!*!*!" << endl;
                    id_pere[operation.get_id()] = precedent.get_id();
                    pere[operation.get_id()] = precedent.get_id();
                }
            }


            Mach[operation.get_id_machine()]=operation.get_id();
            //cout << "Apres : Mach[operation.get_id_machine()] = " << Mach[operation.get_id_machine()] << endl;
        }
        //Non utilisé
        /*if( id_pere[operation.get_id()] == -1)
        {
            id_pere[operation.get_id()] = Mach[operation.get_id_machine()];
        }*/
        Operation operation_prec = Op[id_pere[operation.get_id()]/m][id_pere[operation.get_id()]%m] ;

        //EST[operation.get_id()] = ( id_pere[operation.get_id()]==-1 ) ? 0 : max( EST[operation.get_id()] , EST[id_pere[operation.get_id()]] + operation_prec.get_duree() ) ;
        if(id_pere[operation.get_id()]==-1)
        {
            EST[operation.get_id()] = 0;
        }
        else
        {
            EST[operation.get_id()] = max( EST[operation.get_id()] , EST[id_pere[operation.get_id()]] + operation_prec.get_duree() ) ;
        }
        /* -------- */
        /* Op[id_pere[operation.get_id()]/m][id_pere[operation.get_id()]%m].get_duree() */
        /* -------- */

        //Mach[operation.get_id_machine()]=operation.get_id();

        // cout << "Job " << V[i] << " : Operation " << Job[V[i]] << endl;

        /*
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
        */

    }

    //Calcul du makespan
    int maxEst=0, id_op_maxEST=0, makespan=0;
    for(int i=0; i<n*m; i++)
    {
        if(EST[i]>maxEst)
        {
            maxEst = EST[i];
            id_op_maxEST = ( EST[i]+Op[i/m][i%m].get_duree() > EST[id_op_maxEST]+Op[id_op_maxEST/m][id_op_maxEST%m].get_duree() ) ? i : id_op_maxEST;
        }
        else if(EST[i]==maxEst)
        {
            id_op_maxEST = ( EST[i]+Op[i/m][i%m].get_duree() > EST[id_op_maxEST]+Op[id_op_maxEST/m][id_op_maxEST%m].get_duree() ) ? i : id_op_maxEST;
        }
    }
    makespan = EST[id_op_maxEST]+Op[id_op_maxEST/m][id_op_maxEST%m].get_duree();

    vector<int> chemin;
    vector<int>::iterator it;
    while(id_op_maxEST!=-1)
    {
        chemin.push_back(id_op_maxEST);
        id_op_maxEST = id_pere[id_op_maxEST];
    }
    reverse(chemin.begin(), chemin.end());

    chemin_critique = chemin;
    V.chemin_critique = chemin;
    V.set_val(makespan);


    cout << "Evaluation du vecteur : "<< "V = " ;
    copy(V.get_V().begin(), V.get_V().end(), ostream_iterator<int>(cout, " "));
    cout << "makespan = " << makespan<< "\t Chemin critique : ";
    copy(chemin_critique.begin(),chemin_critique.end(),ostream_iterator<int>(cout, " ")); cout << endl;

    return makespan;
}

Bierwith& Data::Recherche_Locale(Bierwith& V1, vector<int>& ch_cri,int n)
{
    cout <<endl<<endl;
    cout << "||===================================================||" <<endl;
    cout << "||                Recherche Locale                   ||" << endl;
    cout << "||===================================================||" <<endl <<endl;
    cout << "Vecteur de Bierwith initial : ";
    copy(V1.get_V().begin(), V1.get_V().end(), ostream_iterator<int>(cout, " ") );
    cout << "Chemin critique initial : ";
    //copy(ch_cri.begin(), ch_cri.end(), ostream_iterator<int>(cout, " "));
    copy(V1.chemin_critique.begin(), V1.chemin_critique.end(), ostream_iterator<int>(cout, " "));
    cout << endl  <<endl ;

    Bierwith Solution(V1);


    for(int i=0; i<ch_cri.size(); i++)
    {
        int dernier = ch_cri[ch_cri.size()-1-i],
            peredernier = pere[dernier],
            indice_dernier=0,
            indice_peredernier=0;
        if(peredernier!=-1)
        {
            indice_dernier = indice_op_vecteur(V1, dernier);
            indice_peredernier = indice_op_vecteur(V1, peredernier);
        }

        //Permutation dans le vecteur de Bierwith
        if(peredernier!=-1)
        {
            int temp = V1.get_V()[indice_dernier];
            V1.get_V()[indice_dernier] = V1.get_V()[indice_peredernier];
            V1.get_V()[indice_peredernier] = temp;
        }

    }
    cout << "--------------------------------" << endl;
    //Affichage du nouveau vecteur
    cout << "Vecteur apres permutation : ";
    copy(V1.get_V().begin(), V1.get_V().end(), ostream_iterator<int>(cout, " ") ); cout << endl;
    Evaluer(V1,ch_cri);
    if(V1.get_val()<Solution.get_val())
    {
        cout << endl << "Nouveau vecteur : ";
        copy(V1.get_V().begin(), V1.get_V().end(), ostream_iterator<int>(cout, " ") ); cout << endl;
        cout << "Nouveau chemin critique : ";
        copy(ch_cri.begin(), ch_cri.end(), ostream_iterator<int>(cout, " ") ); cout << endl;
        cout << "Nouveau makespan : ";
        cout << V1.get_val() << endl;
        Solution = V1;
    }
    else
    {
        cout << "Pas d'amelioration !" << endl;
        cout << "Solution actuelle : V = ";
        copy(Solution.get_V().begin(), Solution.get_V().end(), ostream_iterator<int>(cout, " "));
        cout << "makespan = " << Solution.get_val() << " chemin_critique = ";
        copy(Solution.chemin_critique.begin(),Solution.chemin_critique.end(), ostream_iterator<int>(cout," ")); cout << endl;
        V1 = Solution;
    }

    return Solution;
}

