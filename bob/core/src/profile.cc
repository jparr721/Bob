#include <core/profile.h>
#include <core/util.h>

#include <cmath>
#include <stdexcept>

namespace bob {
  Pofile::Profile(std::string const& profile_path) {
    this->indexer(profile_path);
  }

  void Profile::operator=(Profile const& p) {
    this->time = p.time;
    this->interval = p.interval;
    this->init_meal = p.init_meal;
    this->init_glucose = p.init_glucose;
    this->irr = p.irr;
    this->gly_idx = p.gly_idx;
    this->meals = p.meals;
  }

  bool Profile::operator==(Profile const& p) const {
    return this->time == p.time &&
      this->interval == p.interval &&
      this->init_meal == p.init_meal &&
      this->init_glucose == p.init_glucose &&
  }

  std::ostream& operator<<(std::ostream& os, Profile const& p) {
    os << "{ " <<
      p.time <<
      ", " <<
      p.interval <<
      ", " <<
      p.init_meal <<
      ", " <<
      p.init_glucose <<
      ", " <<
      p.irr <<
      ", " <<
      p.gly_idx <<
      ", ";
    for (const auto& val : p)
      os << val << ", ";
    os << " }";
    return os;
  }

  void Profile::indexer(std::string const& profile_path) {
    Util u;

    std::vector<std::string> lines = u.read_file(profile_path);
    std::vector<std::string values = u.split_by_space(lines[0]);

    if (!values[0] == "I") throw std::invalid_argument("Invalid profile sequence");

    this->time = std::stoi(values[0]);
    this->carbs = std::stof(values[1]);
    this->glucose = std::stof(values[2]);
    this->bolus_init = std::stof(values[3]);
    this->gly_idx = std::stof(values[4]);
    this->interval = std::stoi(values[5]);
    this->has_diabetes = std::stoi(values[6]);

    std::vector<std::string> meals_string = u.split_by_space(lines[1]);
    std::vector<float> meals;
    meals.reserve(meals_string.size());

    for (const auto& meal : meals_string) meals.push_back(meal);
  }

  void Profile::modify_insulin_bolus(double bolus) {
    if (bolus <= 0) {
      return;
    }

    this->irr = std::fmod(bolus, 1.0);
  }

  void Profile::modify_glycemic_index(double gly_idx) {
    if (gly_idx <= 0) {
      return;
    }

    this->gly_idx = std::fmod(gly_idx, 1.0);
  }

  int Profile::get_time() {
    return this->time;
  }

  int Profile::get_interval() {
    return this->interval;
  }

  double Profile::get_init_meal() {
    return this->init_meal;
  }

  double Profile::get_init_glucose() {
    return this->init_glucose;
  }

  double Profile::get_irr() {
    return this->irr;
  }

  double Profile::get_gly_idx() {
    return this->gly_idx;
  }

  std::vector<float> Profile::get_meals() {
    return this->meals;
  }
} // namespace bob
