#ifndef  __POINTLIGHT_H__
#define  __POINTLIGHT_H__

#include "gssmraytracer/lights/Light.h"
#include <gssmraytracer/geometry/Point.h>
#include <gssmraytracer/geometry/DifferentialGeometry.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/math/Vector.h>
#include <memory>

using namespace gssmraytracer::lights;

namespace gssmraytracer {
  namespace lights {
  class PointLight : public Light {
  public:
    PointLight ();
    PointLight (utils::Color c, float intensity, geometry::Point p);
    bool hit (const geometry::DifferentialGeometry &dg) const;
    math::Vector lightDir(const geometry::DifferentialGeometry &dg) const;

  private:
    class Impl;
    std::shared_ptr<Impl> mImpl;
  };
}
}

#endif
