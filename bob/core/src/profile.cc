#include <core/profile.h>
#include <core/util.h>

#include <cmath>

namespace bob {
  Pofile::Profile(std::string const& profile_path) {
    this->indexer(profile_path);
  }

  void Profile::indexer(std::string const& profile_path) {
    Util u;

    std::vector<std::string> lines = u.read_file(profile_path);
    std::vector<std::string values = u.split_by_space(lines[0]);

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
} // namespace bob
