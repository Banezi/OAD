#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

class Operation
{
    protected:
        int id;
        int id_machine;
        int duree;
        int id_job;
        int position;
    public:
        int get_id(); void set_id(int i);
        int get_id_machine(); void set_id_machine(int i);
        int get_duree(); void set_duree(int d);
        int get_id_job(); void set_id_job(int idjob);
        int get_position(); void set_position(int pos);
};

#endif // OPERATION_H_INCLUDED
