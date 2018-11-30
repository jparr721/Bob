#pragma once

#include <core/core.h>

namespace bob {
  class Naive : public Core {
    public:
     Naive(int carbs, int glucose) : initial_carbs(carbs), initial_glucose(glucose) {};
     ~Naive() = default;

     void adjust_insulin_bolus(double bolus) const;
     double get_insulin_bolus();

     void simulate(int time);
    private:
       double bolus = 0.0224;
  };
} // namespace bob
