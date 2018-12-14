/**
 * Copyright 2018- GVSU DEN Research Lab
 *
 * Licensed under the GNU Public License, Version 3.0
 * you may not use this file except in compliance with
 * the license. You may obtain a copy of this license
 * at:
 *
 *   https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * DOC
 * Profile is a class that handles the propagation of user
 * profile iformation throughout the applicaiton. This
 * enables the system to keep a constant reference to
 * the currently active profile without needing to worry
 * about any issues with handling of cumbersome loader
 * methods in multiple spots
 * *****************************************************/

#pragma once

#include <sstream>
#include <vector>

namespace bob {
  class Profile {
    public:
      Profile(std::string const& profile_path);
      ~Profile() = default;

      void indexer(std::string const& profile_path);
      void modify_insulin_bolus(double bolus);
      void operator=(Profile const& p);

      bool operator==(Profile const& p) const;

      int get_time();
      int get_interval();

      double get_init_meal();
      double get_init_glucose();
      double get_irr();
      double get_gly_idx();

      std::vector<float> get_meals();

      friend std::ostream& operator<<(std::ostream& os, Profile const& p);
    private:
      const int MAXIMUM_UPPER_THRESHOLD = 155;
      const int UPPER_THRESHOLD = 105;
      const int LOWER_THRESHOLD = 75;
      const int MAXIMUM_LOWER_THRESHOLD = 50;
      const float STANDARD_BOLUS_NEGATIVE_MULTIPLIER = 0.75;
      const float STANDARD_BOLUS_POSITIVE_MULTIPLIER = 1.25;
      bool has_diabetes;

      int time;
      int interval;

      double init_meal;
      double init_glucose;
      double irr;
      double gly_idx;

      std::vector<float> meals;
  };
}
