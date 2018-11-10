#include <bob/bob.hpp>

#include <cmath>

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
} // namespace bob
