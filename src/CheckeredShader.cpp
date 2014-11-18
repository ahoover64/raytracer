#include "gssmraytracer/shaders/CheckeredShader.h"
#include "gssmraytracer/utils/Color.h"

class CheckeredShader:Impl {
public:
  geometry::Color color1;
  geometry::Color color2;
  float square_side;
}

CheckeredShader::CheckeredShader() : mImpl(new Impl) {
  mImpl->color1 = Color(0,0,0,1);
  mImpl->color2 = Color(1,1,1,1);
  mImpl->square_side = 5.f;
}

CheckeredShader::CheckeredShader(geometry::Color c1, geometry::Color c2, float side_length) {
  mImpl->color1 = c1;
  mImpl->color2 = c2;
  mImpl->square_side = side_length;
}

Color CheckeredShader::shade(const geometry::DifferentialGeometry &dg) {
  return Color(0,0,0,1);
}
