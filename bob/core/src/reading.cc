#include <core/reading.h>

namespace bob {
  Reading Reading::make_reading(std::unique_ptr<Profile> const& p, int time = -1) {
    Reading *reading = new Reading();
    reading->set_glucose(p->get_glucose());
    reading->set_carbs(p->get_carbs());
    reading->set_time(time);

    return *reading;
  }

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

  int Reading::get_time() {
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

  std::string Reading::to_string() {
    Reading r;
    std::stringstream os;
    os << "{ " <<
    r.get_glucose() <<
    ", " <<
    r.get_carbs() <<
    ", " <<
    r.get_time() <<
    " }";

    return os.str();
  }

  std::ostream& operator<<(std::ostream& os, Reading const& r) {
    os << "{ " <<
      r.glucose <<
      ", " <<
      r.carbs <<
      ", " <<
      r.time <<
      " }";

    return os;
  }

} // namespace bob
