#include <core/reading.h>

namespace bob {
  Reading Reading::make_reading(std::unique_ptr<Profile> const& p, int time = -1) {
    Reading *reading = new Reading();
    reading->glucose = p->glucose;
    reading->carbs = p->carbs;
    reading->time = time;

    return *reading;
  }

  bool Reading::operator==(Reading const& r) const {
    return glucose == r.glucose &&
      carbs == r.carbs &&
      time == r.time;
  }

  void Reading::operator=(Reading const& r) {
    glucose = r.glucose;
    carbs = r.carbs;
    time = r.time;
  }

  std::string Reading::to_string() {
    Reading r;
    std::stringstream os;
    os << "{ " <<
    r.glucose << " glucose"
    ", " <<
    r.carbs << " carbs"
    ", " <<
    r.time << " minutes"
    " }";

    return os.str();
  }

  std::ostream& operator<<(std::ostream& os, Reading const& r) {
    os << "{ " <<
    r.glucose << " glucose"
    ", " <<
    r.carbs << " carbs"
    ", " <<
    r.time << " minutes"
    " }";

    return os;
  }

} // namespace bob
