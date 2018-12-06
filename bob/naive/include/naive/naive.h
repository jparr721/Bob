#pragma once

#include <core/core.h>

namespace bob {
  class Naive : public Core {
    public:
     Naive(int carbs, int glucose) : initial_carbs(carbs), initial_glucose(glucose) {};
     ~Naive() = default;

     void simulate(int time);
    private:
      const int MAXIMUM_UPPER_THRESHOLD = 155;
      const int UPPER_THRESHOLD = 105;
      const int LOWER_THRESHOLD = 75;
      const int MAXIMUM_LOWER_THRESHOLD = 50;
      const float STANDARD_BOLUS_NEGATIVE_MULTIPLIER = 0.75;
      const float STANDARD_BOLUS_POSITIVE_MULTIPLIER = 1.15;
      double bolus = 0.0224;
      double glycemic_index = 0.0453;

      void verify_insulin_dispersion(float current_glucose);
      void adjust_insulin_bolus(double bolus) const;

      double get_insulin_bolus();
  };
} // namespace bob
