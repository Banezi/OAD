#pragma once

#include "node.h"
#include "rng.h"
#include "bkr.h"

#include <string>
#include <limits>
#include <set>


//const double distance_precision = 0.01;
const double distance_precision = 1.0;


enum Problem_type {TSP, NO_PROBLEM_TYPE};
enum Edge_weight_type {EXPLICIT, EUC_2D, EUC_3D, GEO, NO_WEIGHT_TYPE};
enum Edge_weight_format {FUNCTION, LOWER_DIAG_ROW, NO_WEIGHT_FORMAT};
enum Edge_data_format {EDGE_LIST, NO_DATA_FORMAT};
enum Node_coord_type {TWOD_COORDS, THREED_COORDS, NO_COORDS, NO_COORD_TYPE};
enum Display_data_type {NO_DISPLAY, NO_DATA_TYPE};


struct TSPLIB_Info
{
  Problem_type       problem_type;
  Edge_weight_type   edge_weight_type;
  Edge_weight_format edge_weight_format;
  Edge_data_format   edge_data_format;
  Node_coord_type    node_coord_type;
  Display_data_type  display_data_type;

  TSPLIB_Info ();
  void clear();
};

std::ostream & operator<< (std::ostream &, const TSPLIB_Info &);


class Data
{
  protected:
    std::string                        name_; // name of the instance
    TSPLIB_Info                        info_; // information about the data format
    std::vector<Node>                  nodes_; // list of nodes
    std::vector<std::vector<unsigned>> distance_; // distance matrix
    BKR                                bkr_; // best known value for the problem

    RNG &                              rng_; // random number generator for the methods

    static const unsigned INFINITE = std::numeric_limits<unsigned>::max();

    void readSpecification (std::ifstream &, std::string &);
    void buildNeighborhoodLists ();
    void buildDistanceMatrix ();
    void readNodeCoords (std::ifstream &);
    void readEdgeWeights(std::ifstream &);
    void readData (std::ifstream &, const std::string &);

  public:
    Data (RNG &);
    Data (const std::string &, RNG &);

    void clear ();
    void readTSPLIBFormat (const std::string &);
    void check () const;

    const std::string & name () const { return name_; }
    unsigned size () const { return nodes_.size(); }
    const std::vector<Node> & nodes () const { return  nodes_; }
    const BKR & bkr () const { return bkr_; }
    RNG & rng () { return rng_; }

    unsigned operator() (unsigned i, unsigned j) const { return distance_[i][j]; }

    friend class Solution;
};

std::ostream & operator<< (std::ostream &, const Data &);
