#include "gssmraytracer/lights/DirectionLight.h"

class DirectionLight::Impl {
public:
  geometry::Plane plane;
  math::Vector direction;
};

DirectionLight::DirectionLight() : Light(Color(), 1.f), mImpl(new Impl) {
  mImpl->plane = new geometry::Plane();
  mImpl->direction = new math::Vector();
}

DirectionLight::DirectionLight(const Color &c, float intensity, const geometry::Plane &plane, const math::Vector &dir) :
                                Light(c, intensity), mImpl(new Impl) {
    mImpl->plane = plane;
    mImpl->direction = dir;
}

bool hit(const geometry::DifferentialGeometry &dg) const {

}

math::Vector lightDir(const geometry::DifferentialGeometry &dg) const {

}
