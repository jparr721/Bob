#include <bob/bob.hpp>

#include <cmath>
#include <iostream>

namespace bob {
  Bob::Bob(float carbs, float glucose) : initial_carbs(carbs), initial_glucose(glucose) {}

  void Bob::set_initial_carbs(float carbs) {
    this->initial_carbs = carbs;
  }

  float Bob::get_initial_carbs() {
    return this->initial_carbs;
  }

  void Bob::set_initial_glucose(float glucose) {
    this->initial_glucose = glucose;
  }

  float Bob::get_initial_glucose() {
    return this->initial_glucose;
  }

  std::vector<float> Bob::carbohydrate_diffusion(
      int time,
      float carbs,
      float glycemic_index,
      int interval) {
    std::vector<float> concentrations(time / interval, 0);
    for (int i = 0; i < time; ++i) {
      if (i % interval == 0) {
        concentrations.push_back(this->initial_carbs * std::exp(-glycemic_index * time));
      }
    }

    return concentrations;
  }

  std::vector<float> Bob::glucose_diffusion(
      int time,
      float carbs,
      float glycemic_index,
      float insulin_release_rate,
      float glucose,
      int interval) {
    std::vector<float> concentrations(time / interval, 0);
    float diffusion_rate = (glycemic_index / insulin_release_rate - glycemic_index);
    for (int i = 0; i < time; ++i) {
      if (i % interval == 0) {
        concentrations.push_back(
            this->initial_carbs * diffusion_rate * (
              std::exp(-glycemic_index * time) - std::exp(-insulin_release_rate * time)) + glucose);
      }
    }

    return concentrations;
  }

  /**
   * The goal of the simulation is to simulate
   * the diffusion of glucose and carbohydrates
   * given some initial basic quantity
   *
   * @param time - The simulation time in minutes
   * @param glycemic_index - The absorbtion rate of carbs
   * @param insulin_release_rate - The rate insulin
   *        is released to handle the carbohydrates in the
   *        blood stream
   * @param interval - The intervals in which to make
   *        observations
   */
  void Bob::RunSimulation(
      int time,
      float glycemic_index,
      float insulin_release_rate,
      int interval) {
    auto carbs = this->carbohydrate_diffusion(time, this->initial_carbs, glycemic_index, interval);
    auto glucose = this->glucose_diffusion(time, this->initial_carbs, glycemic_index, insulin_release_rate, this->initial_glucose, interval);

    std::cout << "Carbohydrates over " << time << " min " << "Glucose over " << time << " min" << std::endl;
    int timestamp = 0;

    // Linearly scan and print our values
    for (auto it1 = carbs.begin(), it2 = glucose.begin(); it1 != carbs.end() && it2 != glucose.end(); ++it1, ++it2) {
      std::cout << timestamp << " minutes: " << *it1 << timestamp << " minutes: " << *it2 << std::endl;
    }

    return;
  }
} // namespace bob
