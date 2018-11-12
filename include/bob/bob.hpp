#ifndef BOB_BOB_HPP
#define BOB_BOB_HPP

#include <vector>

namespace bob {
  class Bob {
    public:
      Bob(float carbs, float glucose);
      ~Bob() = default;
      void RunSimulation(
          int time,
          float glycemic_index,
          float insulin_release_rate,
          int interval);

      void set_initial_carbs(float carbs);
      float get_initial_carbs();

      void set_initial_glucose(float glucose);
      float get_initial_glucose();

    private:
      float initial_carbs;
      float initial_glucose;

      std::vector<float> carbohydrate_diffusion(
          int time,
          float carbs,
          float glycemic_index,
          int interval);
      std::vector<float> glucose_diffusion(
          int time,
          float carbs,
          float glycemic_index,
          float insulin_release_rate,
          float glucose,
          int interval);

  };
} // namespace bob

#endif
