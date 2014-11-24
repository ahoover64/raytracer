#include "gssmraytracer/lights/DirectionLight.h"

using namespace gssmraytracer::lights;

class DirectionLight::Impl {
public:
  geometry::Plane plane;
  math::Vector direction;
};

DirectionLight::DirectionLight() : Light(utils::Color(), 1.f), mImpl(new Impl) {
  mImpl->plane = geometry::Plane();
  mImpl->direction = math::Vector();
}

DirectionLight::DirectionLight(const utils::Color &c, float intensity, const geometry::Plane &plane, const math::Vector &dir) :
                                Light(c, intensity), mImpl(new Impl) {
    mImpl->plane = plane;
    mImpl->direction = dir.normalized();
}

bool DirectionLight::hit(const geometry::DifferentialGeometry &dg) const {
  return true;
}

bool DirectionLight::hit(const geometry::DifferentialGeometry &dg, float &intensity) const {
  intensity = 100.f;
  return true;
}

math::Vector DirectionLight::lightDir(const geometry::DifferentialGeometry &dg) const {
  return mImpl->direction;
}
