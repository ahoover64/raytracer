#include "gssmraytracer/geometry/Plane.h"

class Plane::Impl {
public:
  math::Vector normal;
  geometry::Point point;
};

Ray::Ray() : mImpl(new Impl){
  mImpl->normal = new Vector();
  mImpl->point = new Point();
}

Ray::Ray(const geometry::Point &pt, const math::Vector &norm) : mImpl(new Impl) {
  mImpl->normal = norm;
  mImpl->point = pt;
}

bool Ray::hit(const utils::Ray &ws_ray, float &tHit) {

}

bool Ray::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<DifferentialGeometry> &dg) {
  
}
