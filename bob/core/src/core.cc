/**
 * Copyright 2018- GVSU DEN Research Lab
 *
 * Licensed under the GNU Public License, Version 3.0
 * you may not use this file except in compliance with
 * the license. You may obtain a copy of this license
 * at:
 *
 * https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * DOC
 * Core is an abstract class that defines the main engine
 * for Bob to run off of. This code will be inhereted into
 * the necessary models and implemented there
 * *****************************************************/

#include <core/core.h>
#include <core/util.h>

#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace bob {
  void Core::set_initial_carbs(float carbs) {
    this->initial_carbs = carbs;
  }

  float Core::get_initial_carbs() {
    return this->initial_carbs;
  }

  void Core::set_initial_glucose(float glucose) {
    this->initial_glucose = glucose;
  }

  float Core::get_initial_glucose() {
    return this->initial_glucose;
  }

  void Core::show_logo() const {
    std::cout << this->bob_logo << std::endl;
    std::cout << "Version: " << this->appversion << std::endl;
  }

  std::vector<float> Core::carbohydrate_diffusion(
      int time,
      float carbs,
      float glycemic_index,
      int interval) const {
    std::vector<float> concentrations;
    for (int current_time = 0; current_time < time; ++current_time) {
      if (current_time % interval == 0) {
        concentrations.push_back(this->initial_carbs * std::exp(-glycemic_index * current_time));
      }
    }

    return concentrations;
  }

  std::vector<float> Core::glucose_diffusion(
      int time,
      float carbs,
      float glycemic_index,
      float insulin_release_rate,
      float glucose,
      int interval,
      std::vector<float> carb_dist) const {
    std::vector<float> concentrations;
    float diffusion_rate = (glycemic_index / insulin_release_rate - glycemic_index);

    for (int current_time = 0; current_time < time; ++current_time) {
      if (current_time % interval == 0) {
        auto data = glucose - (carbs * (glycemic_index / insulin_release_rate - glycemic_index))
          * (std::exp(-glycemic_index * current_time) - std::exp(-insulin_release_rate * current_time));
        concentrations.push_back(data);
      }
    }

    return concentrations;
  }

  std::vector<std::string> Core::format_data(
      std::vector<float> carbs,
      std::vector<float> glucose,
      int time,
      int interval) {
    std::vector<std::string> output_vector;
    // Before storage, verify uniform sizing on input vectors
    if (carbs.size() != glucose.size()) {
      throw new std::invalid_argument("Input vectors are not the same size, output will be improper");
    }

    // Use a string stream to build our file lines
    std::ostringstream run_header, data_line;
    run_header << "Carbohydrates over " << time << " min " << "Glucose over " << time << " min";

    data_line << "Initial Levels: " << this->initial_carbs << " carbs " << this->initial_glucose << " glucose" << std::endl;
    output_vector.push_back(data_line.str());
    int timestamp = 0;

    for (auto it1 = carbs.begin(), it2 = glucose.begin();
        it1 != carbs.end() && it2 != glucose.end(); ++it1, ++it2) {
      data_line << timestamp << " minutes" << *it1 << " " << timestamp << " minutes: " << *it2;
      output_vector.push_back(data_line.str());
      timestamp += interval;
    }

    return output_vector;
  }

  void Core::write_to_file(std::vector<std::string> output_vector) const {
    std::ostringstream filename;

    // Get time of current run
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    filename << "Run" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%X");

    std::ofstream runfile(filename.str());

    std::cout << "Done writing to file..." << std::endl;
  }
} // namespace bob
