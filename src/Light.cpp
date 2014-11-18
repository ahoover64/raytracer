#include "gssmraytracer/lights/Light.h"
#include "gssmraytracer/utils/Color.h"

using namespace gssmraytracer::lights;

namespace gssmraytracer{
namespace lights {
  class Light::Impl {
  public:
    float intensity;
    utils::Color color;
  };

  Light::Light() : mImpl(new Impl) {
    mImpl->intensity = 1;
    mImpl->color = utils::Color();
  }

  Light::Light(utils::Color c, float intensity) : mImpl(new Impl) {
    mImpl->intensity = intensity;
    mImpl->color = c;
  }

  float Light::intensity() const {
    return mImpl->intensity;
  }

  utils::Color Light::color() const {
    return mImpl->color;
  }
}
}
