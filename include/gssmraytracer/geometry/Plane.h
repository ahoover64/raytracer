#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/math/Vector.h"
#include "gssmraytracer/geometry/Point.h"
#include <memory>

using namespace gssmraytracer;

namespace gssmraytracer {
  namespace geometry {
    class Plane : public Shape {
    public:
      Plane();
      Plane(const geometry::Point &pt, const math::Vector &norm);
      bool hit(const utils::Ray &ws_ray, float &tHit) const;
      bool hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<DifferentialGeometry> &dg) const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    }
  }
}
