#ifndef __DIRECTIONLIGHT_H__
#define __DIRECTIONLIGHT_H__

#include "gssmraytracer/utils/Light.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/geometry/Plane.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace lights {
    class DirectionLight : public Light {
    public:
      DirectionLight();
      DirectionLight(const utils::Color &c, float intensity, const geometry::Plane &plane, const math::Vector &dir);
      bool hit(const geometry::DifferentialGeometry &dg) const;
      math::Vector lightDir(const geometry::DifferentialGeometry &dg) const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}

#endif
