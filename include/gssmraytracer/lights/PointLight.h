#include "gssmraytracer/utils/Light.h"
#include <gssmraytracer/geometry/Point.h>
#include <gssmraytracer/geometry/DifferentialGeometry.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/math/Vector.h>
#include <memory>

namespace gssmraytracer {
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
