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

#include <string>
#include <sstream>
#include <vector>

namespace bob {
  class Profile {
    public:
      int time_between_meals;
      int days;
      int interval;

      double carbs;
      double glucose;
      double irr;
      double gly_idx;

      std::vector<float> meals;
      Profile(std::string const& profile_path);

      void indexer(std::string const& profile_path);
      void modify_insulin_bolus(double bolus);
      void modify_glycemic_index(double gly_idx);
      void operator=(Profile const& p);
      void show_run_stats() const;

      bool operator==(Profile const& p) const;
      bool acceptable_glucose();

      double modulate_irr(double glucose);


      friend std::ostream& operator<<(std::ostream& os, Profile const& p);
    private:
      int maximum_upper_threshold = 155;
      int upper_threshold = 105;
      int lower_threshold = 75;
      int maximum_lower_threshold = 50;
      float standard_bolus_negative_multiplier = 0.75;
      float standard_bolus_positive_multiplier = 1.25;

      bool has_diabetes = false;
  };
}
