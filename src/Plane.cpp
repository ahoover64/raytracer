#include "gssmraytracer/geometry/Plane.h"
#include "gssmraytracer/math/Transform.h"

using namespace gssmraytracer::geometry;

class Plane::Impl {
public:
  math::Vector norm;
  geometry::Point pt;
};

Plane::Plane() : Shape(math::Transform()), mImpl(new Impl){
  mImpl->norm = math::Vector();
  mImpl->pt = geometry::Point();
}

Plane::Plane(const geometry::Point &point, const math::Vector &normal) : Shape(math::Transform()), mImpl(new Impl) {
  mImpl->norm = normal.normalized();
  mImpl->pt = point;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit) const {
  float d = mImpl->norm.x() * mImpl->pt.x() + mImpl->norm.y() * mImpl->pt.y() + mImpl->norm.z() * mImpl->pt.z();
  tHit = (d - ws_ray.origin().x()*mImpl->norm.x() - ws_ray.origin().z()*mImpl->norm.y()
            - ws_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(ws_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt())
    return true;
  return false;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
  float d = mImpl->norm.x() * mImpl->pt.x() + mImpl->norm.y() * mImpl->pt.y() + mImpl->norm.z() * mImpl->pt.z();
  if(mImpl->norm.dot(ws_ray.dir()))
    return false;
  tHit = (d - ws_ray.origin().x()*mImpl->norm.x() - ws_ray.origin().z()*mImpl->norm.y()
            - ws_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(ws_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt()) {
    dg->nn = mImpl->norm;
    dg->p = ws_ray(tHit);
    return true;
  }
  return false;
}
