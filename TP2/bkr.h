#pragma once

#include "data.h"

#include <string>


struct BKR
{
    static const std::string BKR_FILE;

    unsigned makespan_;

    BKR (const Data &);
};


std::ostream & operator<< (std::ostream &, const BKR &);
