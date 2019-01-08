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
 * Core is a class that defines the main engine
 * for Bob to run off of. This code will be inhereted into
 * the necessary models and implemented there
 *
 * Abbreviations: irr - Insulin Release Rate
 *                gly_index - Glyecmic Index
 * *****************************************************/

#include <core/core.h>
#include <core/util.h>

#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace bob {
  void Core::usage(std::string opts) const {
    show_logo();
    std::cout << opts << std::endl;
  }

  void Core::show_logo() const {
    std::cout << bob_logo << std::endl;
    std::cout << "Version: " << appversion << std::endl;
  }

  float Core::carbohydrate_diffusion(float carbs, float glycemic_index, int time) const {
    return carbs * std::exp(-glycemic_index * time);
  }

  float Core::glucose_diffusion(float carbs, float glucose, float irr, float gly_index, int time) const {
    return glucose - (carbs * (gly_index / irr - gly_index)) * (std::exp(
          -gly_index * time) - std::exp(-irr * time));
  }


} // namespace bob
