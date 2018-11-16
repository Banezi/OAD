#pragma once

#include <random>


class RNG
{
  protected:
    std::mt19937 engine_;

  public:
    RNG (std::mt19937::result_type s = 0): engine_(s) {}
    void reset (std::mt19937::result_type s = 0) { engine_.seed(s); }

    unsigned operator() (unsigned max) { return std::uniform_int_distribution<unsigned>{0, max - 1}(engine_); }
};
