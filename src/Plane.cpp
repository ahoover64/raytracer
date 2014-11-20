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

Plane::Plane(const math::Vector &pos, const math::Vector &normal) : Shape(math::Transform()), mImpl(new Impl) {
  mImpl->norm = normal.normalized();
  mImpl->pt = geometry::Point(pos);
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit) const {
  math::Transform t = Shape::worldToObjectSpace();
  utils::Ray os_ray = t(ws_ray);
  //float d = mImpl->norm.x() * mImpl->pt.x() + mImpl->norm.y() * mImpl->pt.y() + mImpl->norm.z() * mImpl->pt.z();
  tHit = (0 - os_ray.origin().x()*mImpl->norm.x() - os_ray.origin().z()*mImpl->norm.y()
            - os_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(ws_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt())
    return true;
  return false;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
  math::Transform t = Shape::worldToObjectSpace();
  utils::Ray os_ray = t(ws_ray);
  //float d = mImpl->norm.x() * mImpl->pt.x() + mImpl->norm.y() * mImpl->pt.y() + mImpl->norm.z() * mImpl->pt.z();
  if(mImpl->norm.dot(os_ray.dir()))
    return false;
  tHit = (0 - os_ray.origin().x()*mImpl->norm.x() - os_ray.origin().z()*mImpl->norm.y()
            - os_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(os_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt()) {
    dg->nn = mImpl->norm;
    dg->p = ws_ray(tHit);
    dg->dir = ws_ray.dir()
    //dg->u = os_ray(tHit);
    //dg->v = os_ray(tHit);
    return true;
  }
  return false;
}
