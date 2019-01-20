#include <core/reading.h>

namespace bob {
  Reading Reading::make_reading(std::unique_ptr<Profile> const& p, int time = -1) {
    Reading *reading = new Reading();
    reading->glucose = p->glucose;
    reading->carbs = p->carbs;
    reading->time = time;
    reading->irr = p->irr;

    return *reading;
  }

  bool Reading::operator==(Reading const& r) const {
    return glucose == r.glucose &&
      carbs == r.carbs &&
      time == r.time &&
      irr == r.irr;
  }

  void Reading::operator=(Reading const& r) {
    glucose = r.glucose;
    carbs = r.carbs;
    time = r.time;
    irr = r.irr;
  }

  std::string Reading::to_string() {
    Reading r;
    std::stringstream os;
    os << "{ " <<
    r.glucose << " glucose" <<
    ", " <<
    r.carbs << " carbs" <<
    ", " <<
    r.time << " minutes" <<
    ", " <<
    r.irr << " mg/dl" <<
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
    ", " <<
    r.irr << " mg/dl" <<
    " }";

    return os;
  }

} // namespace bob
