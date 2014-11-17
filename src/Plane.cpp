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
  float d = norm.x() * pt.x() + norm.y() * pt.y() + norm.z() * pt.z();
  tHit = (d - ws_ray.origin().x()*norm.x() - ws_ray.origin().z()*norm.y()
            - ws_ray.origin().z()*norm.z()) / norm.dot(ws_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt())
    return true;
  return false;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
  float d = norm.x() * pt.x() + norm.y() * pt.y() + norm.z() * pt.z();
  if(norm.dot(ws_ray.dir()))
    return false;
  tHit = (d - ws_ray.origin().x()*norm.x() - ws_ray.origin().z()*norm.y()
            - ws_ray.origin().z()*norm.z()) / norm.dot(ws_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt()) {
    dg.nn = norm;
    dg.p = ws_ray(tHit);
    return true;
  }
  return false;
}
