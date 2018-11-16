#pragma once

#include "data.h"


class Solution
{
  protected:
    const Data &          data_;
    std::vector<unsigned> next_;
    std::vector<unsigned> prev_;

    unsigned              value_;

    static const unsigned NO_SOLUTION;
    static const unsigned NOBODY;

  public:
    Solution (const Data &);
    void clear ();
    void check () const;
    bool is_empty () const { return value_ == Solution::NO_SOLUTION; }

    unsigned & next (unsigned i) { return next_[i]; }
    unsigned & prev (unsigned i) { return prev_[i]; }
    unsigned & value () { return value_; }
    double real_value () const { return value_ * distance_precision; }
    unsigned size () const { return next_.size(); }
    const Data & data () const { return data_; }

    Solution & operator= (const Solution & s) { if (this != &s) {next_ = s.next_; prev_ = s.prev_; value_ = s.value_;} return *this; }
    bool operator< (const Solution & s) const { return (value_ < s.value_); }

    void remove (unsigned);
    void insert (unsigned);
    void insert (unsigned, unsigned);

    void display (std::ostream &) const;
    friend std::ostream & operator<< (std::ostream &, const Solution &);
};

std::ostream & operator<< (std::ostream &, const Solution &);

