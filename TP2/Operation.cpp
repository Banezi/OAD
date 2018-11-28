#include "Operation.h"

using namespace std;

int Operation::get_id()
{
    return id;
}
int Operation::get_id_machine()
{
    return id_machine;
}
int Operation::get_duree()
{
    return duree;
}
int Operation::get_id_job()
{
    return id_job;
}
int Operation::get_position()
{
    return position;
}
void Operation::set_id(int i)
{
    id=i;
}
void Operation::set_id_machine(int i)
{
    id_machine=i;
}
void Operation::set_duree(int d)
{
    duree = d;
}
void Operation::set_id_job(int idjob)
{
    id_job = idjob;
}
void Operation::set_position(int pos)
{
    position=pos;
}
