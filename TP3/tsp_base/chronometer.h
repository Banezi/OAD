#pragma once

#include <chrono>


class Chronometer
{
  public:
    using Duration = double;

  protected:
    Duration & duration_;
    std::chrono::time_point<std::chrono::system_clock> start_;

  public:
    Chronometer (Duration & d): duration_(d), start_(std::chrono::system_clock::now()) {}
    ~Chronometer () {duration_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_).count() * 0.001;}
};
