#include "gssmraytracer/geometry/Plane.h"
#include "gssmraytracer/math/Transform.h"

using namespace gssmraytracer::geometry;

class Plane::Impl {
public:
  math::Vector normal;
  geometry::Point point;
};

Plane::Plane() : Shape(math::Transform()), mImpl(new Impl){
  mImpl->normal = math::Vector();
  mImpl->point = geometry::Point();
}

Plane::Plane(const geometry::Point &pt, const math::Vector &norm) : Shape(math::Transform()), mImpl(new Impl) {
  mImpl->normal = norm;
  mImpl->point = pt;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit) const {
  return true;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
  return true;
}
