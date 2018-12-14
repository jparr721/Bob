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
      void modify_insulin_bolus(double glucose_level);
      void operator=(Profile const& p);

      bool operator==(Profile const& p) const;

      std::ostream& operator<<(std::ostream& os, Profile const& p);
    private:
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
