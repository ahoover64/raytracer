#include "gssmraytracer/lights/PointLight.h"
#include <gssmraytracer/geometry/Point.h>

#include <iostream>

namespace gssmraytracer {
  class PointLight::Impl {
  public:
    geometry::Point location;
  };

  PointLight::PointLight() : Light(), mImpl(new Impl) {
    mImpl->location = geometry::Point();
  }

  PointLight::PointLight(utils::Color c, float intensity, geometry::Point p) : Light(c, intensity), mImpl(new Impl) {
    mImpl->location = p;
  }

  bool PointLight::hit(const geometry::DifferentialGeometry &dg) const {
    math::Vector v(mImpl->location, dg.p);
    utils::Ray ray_to_point(mImpl->location, v.normalized());
    ray_to_point.setMint(0);
    ray_to_point.setMaxt(v.length() - 0.05);
    if(utils::Scene::getInstance().hit(ray_to_point)) {
      return false;
    }
    return true;
  }

  math::Vector PointLight::lightDir(const geometry::DifferentialGeometry &dg) const {
    return math::Vector(mImpl->location, dg.p);
  }
}
