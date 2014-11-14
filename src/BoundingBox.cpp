#include "gssmraytracer/geometry/BoundingBox.h"
#include <gssmraytracer/geometry/Point.h>
#include <gssmraytracer/utils/Ray.h>
#include <limits>

using namespace gssmraytracer::geometry;

class BoundingBox::Impl {
public:
  geometry::Point min;
  geometry::Point max;
};

BoundingBox::BoundingBox() : mImpl(new Impl) {
  mImpl->min = geometry::Point(0,0,0);
  mImpl->max = geometry::Point(std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity());
}

BoundingBox::BoundingBox(const geometry::Point &min, const geometry::Point &max) : mImpl(new Impl) {
  mImpl->min = min;
  mImpl->max = max;
}

bool BoundingBox::hit(const utils::Ray &r) const {
  float tymin = 0.0, tymax = 0.0, tzmin = 0.0, tzmax = 0.0, tmin = 0.0, tmax = 0.0;
  float divx, divy, divz;
  divx = 1 / r.dir().x();
  divy = 1 / r.dir().y();
  divz = 1 / r.dir().z();
  if(r.dir().x() >= 0) {
    tmin = (mImpl->min.x() - r.origin().x()) * divx;
    tmin = (mImpl->max.x() - r.origin().x()) * divx;
  }
  else {
    tmin = (mImpl->max.x() - r.origin().x()) * divx;
    tmax = (mImpl->min.x() - r.origin().x()) * divx;
  }
  if(r.dir().y() >= 0) {
    tymin = (mImpl->min.y() - r.origin().y()) * divy;
    tymin = (mImpl->max.y() - r.origin().y()) * divy;
  }
  else {
    tymin = (mImpl->max.y() - r.origin().y()) * divy;
    tymax = (mImpl->min.y() - r.origin().y()) * divy;
  }
  if(r.dir().z() >= 0) {
    tzmin = (mImpl->min.z() - r.origin().z()) * divz;
    tzmin = (mImpl->max.z() - r.origin().z()) * divz;
  }
  else {
    tzmin = (mImpl->max.z() - r.origin().z()) * divz;
    tzmax = (mImpl->min.z() - r.origin().z()) * divz;
  }
  if(tmax < tymax) {
    tmax = tymax;
  }
  if(tmax < tzmax) {
    tmax = tzmax;
  }
  if(tmin > tymin) {
    tmax = tymin;
  }
  if(tmin > tzmin) {
    tmax = tzmin;
  }
  return !((tmin < r.mint()) && (tmax > r.maxt()));
}
