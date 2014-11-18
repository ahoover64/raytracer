#include "gssmraytracer/utils/Color.h"

namespace gssmraytracer {
  namespace utils {
    Color::Color() : red(0), green(0), blue(0), alpha(0) {}
    Color::Color(const float r,const float g,const float b,const float a) :
                red(r), green(g), blue(b), alpha(a)
                {}
    Color Color::operator+(const Color &other) const {
      Color c(red + other.red, green + other.green, blue + other.blue, alpha + other.alpha);
      c.alpha = (c.alpha > 1) ? 1:c.alpha;
      return c;
    }

    Color Color::operator/(const float factor) const {
      Color c(red / factor, green / factor, blue / factor, alpha);
      c.alpha = (c.alpha > 1) ? 1:c.alpha;
      return c;
    }

    Color operator*(const float factor) const {
      Color c(red * factor, green * factor, blue * factor, alpha * factor);
      c.alpha = (c.alpha > 1) ? 1:c.alpha;
      return c;
    }
  }
}
