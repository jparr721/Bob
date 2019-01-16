 /* Copyright 2018- GVSU DEN Research Lab
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

#pragma once

#include <core/profile.h>
#include <core/reading.h>

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace bob {
  struct Core {
    Core() = default;

    float carbohydrate_diffusion(float carbs, float glycemic_index, int time) const;
    float glucose_diffusion(float carbs, float glucose, float irr, float gly_index, int time) const;

    void show_logo() const;

    const std::string appversion = "5.17.22";
    const std::string bob_logo =
                R"(
                      |  _ \      | |
                      | |_) | ___ | |__
                      |  _ < / _ \| '_ \
                      | |_) | (_) | |_) |
                      |____/ \___/|_.__/
                  )";
  };
} // namespace bob
