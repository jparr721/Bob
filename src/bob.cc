#include <bob/bob.h>
#include <bob/util.h>

#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace bob {
  Bob::Bob(std::string infile, std::string outfile) : infile(infile), outfile(outfile) {}
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

  void Bob::show_logo() const {
    std::cout << this->bob_logo << std::endl;
    std::cout << "Version: " << this->appversion << std::endl;
    std::cout << "\n\n" << std::endl;
  }

  std::vector<float> Bob::carbohydrate_diffusion(
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

  std::vector<float> Bob::glucose_diffusion(
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

  std::vector<std::string> Bob::format_data(
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

  void Bob::write_to_file(std::vector<std::string> output_vector) const {
    std::ostringstream filename;

    // Get time of current run
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    filename << "Run" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%X");

    std::ofstream runfile(filename.str());

    std::cout << "Done writing to file..." << std::endl;
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
    Util u;
    std::vector<float> carbs = this->carbohydrate_diffusion(time, this->initial_carbs, glycemic_index, interval);
    std::vector<float> glucose = this->glucose_diffusion(
        time, this->initial_carbs, glycemic_index, insulin_release_rate, this->initial_glucose, interval, carbs);

    auto meals = u.read_file("meals.txt");
    for (const auto meal : meals) {
      this->set_initial_carbs(std::stof(meal));
      carbs = this->carbohydrate_diffusion(time, this->initial_carbs, glycemic_index, interval);
      glucose = this->glucose_diffusion(
          time, this->initial_carbs, glycemic_index, insulin_release_rate, this->initial_glucose, interval, carbs);
    }
  }

  /**
   * Runs a basic simulation for the usage of
   * running one-off tests to make rapid prototyping
   * of features easier. The full RunSimulation function
   * will be used for all legitimate research
   *
   * @param time - The simulation time in minutes
   * @param glycemic_index - The absorbtion rate of carbs
   * @param insulin_release_rate - The rate insulin
   *        is released to handle the carbohydrates in the
   *        blood stream
   * @param interval - The intervals in which to make
   *        observations
   */
  void Bob::RunBasic(
      int time,
      float glycemic_index,
      float insulin_release_rate,
      int interval) {
    this->show_logo();
    auto carbs = this->carbohydrate_diffusion(time, this->initial_carbs, glycemic_index, interval);
    auto glucose = this->glucose_diffusion(time, this->initial_carbs, glycemic_index, insulin_release_rate, this->initial_glucose, interval, carbs);

    std::cout << "Carbohydrates over " << time << " min " << "Glucose over " << time << " min" << std::endl;
    std::cout << "Initial Levels: " << this->initial_carbs << " carbs " << this->initial_glucose << " glucose" << std::endl;
    int timestamp = 0;

    // Linearly scan and print our values
    for (auto it1 = carbs.begin(), it2 = glucose.begin(); it1 != carbs.end() && it2 != glucose.end(); ++it1, ++it2) {
      std::cout << timestamp << " minutes: " << *it1 << " " << timestamp << " minutes: " << *it2 << std::endl;
      timestamp += interval;
    }
  }
} // namespace bob
