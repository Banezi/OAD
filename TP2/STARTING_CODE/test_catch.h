#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "jobshop.h"

TEST_CASE("Tests de base sur les structures") {

  SECTION("creation d'une operation") {
    Operation op1;

	REQUIRE(op1.id() == 0);
	REQUIRE(op1.id_job() == 0);
	REQUIRE(op1.id_machine() == 0);
	REQUIRE(op1.duration() == 0);
	
    Operation op2;

	REQUIRE(op2.id() == 1);
  }

  SECTION("creation d'un job") {
    Job job1;

	REQUIRE(job1.id() == 0);
	REQUIRE(job1.nb_operations() == 0);

    Job job2;

	REQUIRE(job2.id() == 1);
  }
}

TEST_CASE ("Fonctionnement de Data") {
  Data data;

  SECTION("lecture des donnees") {
    data.read("la01.txt");

	// apply the internal check
	REQUIRE(data.check() == true);

	// check the instance name
	REQUIRE(data.name() == "la01.txt");

	// check the instance size
    REQUIRE(data.nb_jobs() == 10);
	REQUIRE(data.nb_machines() == 5);

	// check the first and the last job
	const std::vector<unsigned> ID_FIRST = { 1 , 0 , 4 , 3 , 2 };
	const std::vector<unsigned> DURATION_FIRST = { 21 , 53 , 95 , 55 , 34};
	unsigned id_job = 0;
	for (unsigned k = 0; k < data.nb_machines(); ++k) {
	  REQUIRE(data.job[id_job][k].id_machine() == ID_FIRST[k]);
	  REQUIRE(data.job[id_job][k].duration() == DURATION_FIRST[k]);
	}
	
	// check the last job
	const std::vector<unsigned> ID_LAST = { 4 , 3 , 2 , 1 , 0 };
	const std::vector<unsigned> DURATION_LAST = { 77 , 79 , 43 , 75 , 96};
	id_job = data.nb_jobs() - 1;
	for (unsigned k = 0; k < data.nb_machines(); ++k) {
	  REQUIRE(data.job[id_job][k].id_machine() == ID_LAST[k]);
	  REQUIRE(data.job[id_job][k].duration() == DURATION_LAST[k]);
	}
  }
}

TEST_CASE ("Fonctionnement de Solution") {
  Data data;
  data.read("la01.txt");

  SECTION("creation d'une solution") {
    // create a Bierwirth vector
    data.read("la01.txt");
    Bierwirth b1(data);
	
	// check its length
	REQUIRE(b1.size() == data.nb_jobs() * data.nb_machines());

	// check it is a Bierwirth vector
	REQUIRE(b1.check() == true);

	// check it is the trivial expected Bierwirth vector
	unsigned pos = 0;
	for (unsigned i = 0; i < data.nb_jobs(); ++i) {
	  for (unsigned j = 0; j < data.nb_machines(); ++j, ++pos) {
	    REQUIRE(b1[pos] == i);
	  }
	}
  }

  SECTION("copie d'une solution") {
    Bierwirth b1(data);

	// copy operator
	Bierwirth b2(b1);
	REQUIRE(b2.check());

	// check the copy
	REQUIRE(b2.size() == b1.size());
	for (unsigned i = 0; i < b1.size(); ++i) {
	  REQUIRE(b1[i] == b2[i]);
	}
  }
  
  SECTION("solution aleatoire") {
    Bierwirth b1(data);
	Bierwirth b2(b1);

	// randomly shake the vector
	b2.shake();
	
	// check it is different
	REQUIRE(b2.check() == true);
	unsigned pos;
	for (pos = 0; pos < b1.size(); ++pos) {
	  if (b1[pos] != b2[pos]) {
	    break;
	  }
	}
	REQUIRE(pos < b1.size());
  }

  SECTION("decodage d'une solution") {
    Bierwirth b1(data);

	REQUIRE(b1.makespan() == 55); // A DEFINIR EN FONCTION DE LA VRAIE VALEUR POUR la01.txt
  }
}

TEST_CASE("Recherche Locale") {
}

TEST_CASE("Regression") {
}