#include "gssmraytracer/geometry/Plane.h"

class Plane::Impl {
public:
  math::Vector normal;
  geometry::Point point;
};

Plane::Plane() : mImpl(new Impl){
  mImpl->normal = new Vector();
  mImpl->point = new Point();
}

Plane::Plane(const geometry::Point &pt, const math::Vector &norm) : mImpl(new Impl) {
  mImpl->normal = norm;
  mImpl->point = pt;
}

bool Plane::Plane(const utils::Ray &ws_ray, float &tHit) const {
  return true;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
  return true;
}
