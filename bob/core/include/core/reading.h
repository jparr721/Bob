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
 * Reading is a class that maps readings into a simple
 * and easily interactable data structure for quick
 * access of packed data
 * *****************************************************/

#pragma once
#include <core/profile.h>

#include <memory>
#include <sstream>

namespace bob {
  class Reading {
    public:
      double glucose;
      double carbs;
      int time;

      Reading make_reading(std::unique_ptr<Profile> const& p, int time);

      void operator=(Reading const& r);

      std::string to_string();

      bool operator==(Reading const& r) const;

      friend std::ostream& operator<<(std::ostream& os, Reading const& r);
  };

} // namespace bob
