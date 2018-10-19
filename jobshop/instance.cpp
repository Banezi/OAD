#include "instance.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void lecture_instance(Data& D, string f_instance)
{
    f_instance = "STARTING_CODE/INSTANCES/" + f_instance;
    //ifstream instance(f_instance);  // Ne marche pas sous Windows ?
    ifstream instance("STARTING_CODE/INSTANCES/la01.dat"); // A optimiser avec la ligne ci-dessus
    if(!instance)
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
    }
    string ligne;
    int n, m;//, machine, duree;
    getline(instance, ligne);
    //cout << ligne <<endl;
    instance >> n;
    instance >> m;
    //cout << n << " " << m << endl;
    //Initialisation
    D.set_m(m);
    D.set_n(n);
    D.Op.resize(n);
    for(int i=0; i<n; i++)
        D.Op[i].resize(m);
    int id_machine, duree;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            instance >> id_machine;
            instance >> duree;
            //cout << id_machine << " " << duree << " " ;
            D.Op[i][j].set_id(i*10 + id_machine);
            D.Op[i][j].set_id_machine(id_machine);
            D.Op[i][j].set_duree(duree);
            D.Op[i][j].set_id_job(i);
            D.Op[i][j].set_position(j);
        }
        //cout << endl; // pour l'affichage de l'instance
    }
    //D.afficher();
}
