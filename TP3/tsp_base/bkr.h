#pragma once

#include <string>
#include <iostream>


struct BKR
{
    static const std::string BKR_FILE;
    static const unsigned NO_VALUE;

    unsigned value_;

    BKR ();

    void load (const std::string &);
};


std::ostream & operator<< (std::ostream &, const BKR &);
