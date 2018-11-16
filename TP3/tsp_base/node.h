#pragma once

#include <vector>
#include <iostream>


class Node
{
  protected:
    unsigned id_;        // id
    unsigned public_id_; // public id
    double   x_;         // abscissa
    double   y_;         // ordinate
    double   z_;         // elevation

    std::vector<unsigned> neighbours_; // neighbours list

    void compute_neighbours (const std::vector<unsigned> &);
    void check (const std::vector<unsigned> &) const;
    friend class Data;

  public:
    Node (unsigned = 0, double = 0.0, double = 0.0, double = 0.0);

    unsigned id () const { return id_; }
    unsigned publicId () const { return public_id_; }
    const double & x () const { return x_; }
    const double & y () const { return y_; }
    const double & z () const { return z_; }

    const std::vector<unsigned> & neighbours () const { return neighbours_; }
};

std::ostream & operator<< (std::ostream &, const Node &);
