#include <naive/naive.h>
#include <core/util.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>


namespace bob {
  void Naive::calculate(
      double input,
      std::vector<Reading>& outputs,
      std::unique_ptr<Profile> const& profile,
      int current_time_step,
      float& current_glucose,
      float& current_carbs) {
    Reading r;
    input = input + profile->carbs;
    std::cout << input << std::endl;

    current_glucose = glucose_diffusion(
       input,
       60,
       profile->irr,
       profile->gly_idx,
       current_time_step);
    profile->glucose = current_glucose;

    current_carbs = carbohydrate_diffusion(
      input,
      profile->gly_idx,
      current_time_step);
    profile->carbs = current_carbs;

    if (!profile->acceptable_glucose()) {
      double profile_glucose = profile->glucose;
      profile->irr = profile->modulate_irr(profile_glucose);
    }

    auto reading = r.make_reading(profile, current_time_step);
    std::cout << reading << std::endl;
    outputs.push_back(reading);
  }

  std::vector<Reading> Naive::engine(std::unique_ptr<Profile> const& profile) {
    profile->show_run_stats();
    show_logo();
    std::vector<Reading> outputs;
    std::atomic<double> input{0.001};
    std::atomic<bool> running{true};

    float current_glucose, current_carbs;
    // Run for 3 hours
    int days = profile->days * 3 * 60;
    bool breaker = false;

    for (int current_time = 1; current_time < days; ++current_time) {
      std::thread stdin_poll([&input, &running, &breaker] {
        std::string new_value = "";
        std::cin >> new_value;
        if (new_value.compare("quit") == 0) {
          std::cout << "Breaker called" << std::endl;
          breaker = true;
        }
        else { input = std::stod(new_value); }
      });
      if (breaker) {
        std::cout << "breaker flag" << std::endl;
        std::cout << "Killing the processes" << std::endl;
        running = false;
        stdin_poll.join();
        break;
      }

      calculate(input.load(), outputs, profile, current_time, current_glucose, current_carbs);

      running = false;
      stdin_poll.join();
    }

    std::cout << "All done!" << std::endl;
    return outputs;
  }

  int Naive::simulation(int argc, char** argv) {
    Util u;
    if (argc < 2) {
      show_logo();
      std::cout << OPTS << std::endl;
      return EXIT_SUCCESS;
    }

    std::unique_ptr<Profile> p(new Profile(std::string(argv[1])));
    std::vector<Reading> outputs = engine(p);
    u.write_to_file(outputs);

    /* for (int i = 1; i < 180; ++i) { */
    /*   std::cout << glucose_diffusion(127.17, 90, 0.0224, 0.0453, i) << std::endl; */
    /* } */

    return EXIT_SUCCESS;
  }
} // namespace bob
