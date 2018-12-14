#include <core/reading>

namespace bob {
  void Reading::set_glucose(double glucose) {
    this->glucose = glucose;
  }

  void Reading::set_carbs(double carbs) {
    this->carbs = carbs;
  }

  void Reading::set_time(int time) {
    this->time = time;
  }

  double Reading::get_glucose() {
    return this->glucose;
  }

  double Reading::get_carbs() {
    return this->carbs;
  }

  int Raading::get_time() {
    return this->time;
  }

  bool Reading::operator==(Reading const& r) const {
    return this->glucose == r.glucose &&
      this->carbs == r.carbs &&
      this->time == r.time;
  }

  void Reading::operator=(Reading const& r) {
    this->glucose = r.glucose;
    this->carbs = r.carbs;
    this->time = r.time;
  }

  std::ostream& Reading::operator<<(std::ostream& os, Reading const& r) {
    os << "{ " <<
      r.glucose <<
      ", " <<
      r.carbs <<
      ", " <<
      r.time;

    return os;
  }

} // namespace bob
