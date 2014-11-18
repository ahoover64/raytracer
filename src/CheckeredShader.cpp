#include "gssmraytracer/shaders/CheckeredShader.h"
#include "gssmraytracer/utils/Color.h"

using namespace gssmraytracer;
using namespace gssmraytracer::shaders;

class CheckeredShader::Impl {
public:
  utils::Color color1;
  utils::Color color2;
  float square_side;
};

CheckeredShader::CheckeredShader() : mImpl(new Impl) {
  mImpl->color1 = utils::Color(0,0,0,1);
  mImpl->color2 = utils::Color(1,1,1,1);
  mImpl->square_side = 5.f;
}

CheckeredShader::CheckeredShader(const utils::Color &c1, const utils::Color &c2, float side_length) {
  mImpl->color1 = c1;
  mImpl->color2 = c2;
  mImpl->square_side = side_length;
}

utils::Color CheckeredShader::shade(const geometry::DifferentialGeometry &dg) {
  return utils::Color(0,0,0,1);
}
