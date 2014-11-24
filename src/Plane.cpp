#include "gssmraytracer/geometry/Plane.h"
#include "gssmraytracer/math/Transform.h"

using namespace gssmraytracer::geometry;

class Plane::Impl {
public:
  math::Vector norm;
  math::Vector q1;
  math::Vector q2;
  geometry::Point pt;
};

Plane::Plane() : Shape(math::Transform()), mImpl(new Impl){
  mImpl->norm = math::Vector();
  mImpl->pt = geometry::Point();
}

Plane::Plane(const math::Transform &pos, const math::Vector &v1, const math::Vector &v2) :
                    Shape(pos), mImpl(new Impl) {
  mImpl->q1 = v1.normalized();
  mImpl->q2 = (v2.normalized() - (v1.dot(v2)/v1.dot(v1))*v1).normalized();
  mImpl->norm = (mImpl->q1.cross(mImpl->q2)).normalized();
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit) const {
  math::Transform t = Shape::worldToObjectSpace();
  utils::Ray os_ray = t(ws_ray);
  tHit = (0 - os_ray.origin().x()*mImpl->norm.x() - os_ray.origin().z()*mImpl->norm.y()
            - os_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(ws_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt())
    return true;
  return false;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
  math::Transform t = Shape::worldToObjectSpace();
  utils::Ray os_ray = t(ws_ray);
  if(fabs(mImpl->norm.dot(os_ray.dir())) < 0.01)
    return false;
  tHit = (0 - os_ray.origin().x()*mImpl->norm.x() - os_ray.origin().z()*mImpl->norm.y()
            - os_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(os_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt()) {
    dg->nn = mImpl->norm;
    dg->p = ws_ray(tHit);
    dg->dir = ws_ray.dir();

    // FIND WHERE IT HIT
    float q12 = mImpl->q1.dot(mImpl->q1);
    float q22 = mImpl->q2.dot(mImpl->q2);
    math::Vector vec(geometry::Point(0,0,0), dg->p);
    float v_dot_q1 = vec.dot(mImpl->q1);
    float v_dot_q2 = vec.dot(mImpl->q2);
    dg->u = q22 * v_dot_q1;
    dg->v = q12 * v_dot_q2;
    return true;
  }
  return false;
}
