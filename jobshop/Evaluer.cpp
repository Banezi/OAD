int Bierwidth::eval(){

    //LES OPERATIONS EN ATTENTE DE CHAQUE JOB
    vector<int> next_op_job(data->nbJobs,0);
    //LES DERNIERS OPERATIONS TRAITEES PAR UNE MACHINE
    vector<int> last_op_machine(data->nbMachines,-1);

    makespan = 0;

    for(int i=0; i<tab.size(); i++){
        //RECUPERER LE JOB A TRAITE
        int idJob = tab[i];
        Job job = data->jobs[idJob];
        //RECUPERER L'OPERATION DE JOB A TRAITEE
        int sid = next_op_job[idJob];
        //LA DATE DE FIN AU PLUS TOT DE L'OPERATION PRECEDENTE DE MEME JOB
        int pjid = (sid== 0 ? -1 : job.sequence[sid-1]);
        int stop_pjid = (pjid== -1 ? 0 : data->operations[pjid].stop);
        //LA DATE DE FIN AU PLUS TOT DE LA DERNIERE OPERATION EXECUTEE DANS LA MEME MACHINE
        int pmid = last_op_machine[(data->operations[job.sequence[sid]]).id_machine];
        int stop_pmid = (pmid== -1 ? 0 : data->operations[pmid].stop);
        //LA POSITION DANS LE VECTEUR DE BIERWIDTH
        data->operations[job.sequence[sid]].position_sequence = i;
        data->operations[job.sequence[sid]].position_job = sid;
        //LA DATE DE DEMARRAGE AU PLUS TOT DE L'OPERATION
        data->operations[job.sequence[sid]].start = max(stop_pjid, stop_pmid);
        //LA DATE DE FIN AU PLUS TOT DE L'OPERATION
        data->operations[job.sequence[sid]].stop = data->operations[job.sequence[sid]].start + data->operations[job.sequence[sid]].duree;
        //LA DATE AU PLUS TOT
        makespan = max(makespan,data->operations[job.sequence[sid]].stop);
        //L'OPERATION QUI CONDITIONNE LA DATE AU PLUS TOT
        data->operations[job.sequence[sid]].pred = (data->operations[job.sequence[sid]].start== stop_pjid? pjid: pmid);

        //LA PROCHAINE OPERATION DE JOB A EXECUTEE
        next_op_job[idJob] = next_op_job[idJob] + 1;
        //LA DERNIERE OPERATION EXECUTEE DANS UNE MACHINE
        last_op_machine[data->operations[job.sequence[sid]].id_machine] = data->operations[job.sequence[sid]].id;
    }

    return makespan;
}