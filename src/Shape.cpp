#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/shaders/Shader.h"
#include "gssmraytracer/math/Transform.h"
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {
    class Shape::Impl {
    public:
      math::Transform o2w;
      math::Transform w2o;
    };
    Shape::Shape(const math::Transform &transform) :
      mImpl(new Impl) {
        mImpl->o2w = transform;
        mImpl->w2o = transform.inverse();
    }


    Shape::Shape(const Shape& shape) : mImpl(new Impl) {
      mImpl->o2w = shape.mImpl->o2w;
      mImpl->w2o = shape.mImpl->w2o;
    }
    Shape::~Shape() {

    }

    const math::Transform Shape::worldToObjectSpace() const{
      return mImpl->w2o;


    }
    const math::Transform Shape::objectToWorldSpace() const{
      return mImpl->o2w;
    }

    const utils::Ray Shape::worldToObjectSpace(const utils::Ray &ws_ray) const{
      utils::Ray os_ray = mImpl->w2o(ws_ray);

      return os_ray;

    }
    const utils::Ray Shape::objectToWorldSpace(const utils::Ray &os_ray) const{
      utils::Ray ws_ray = mImpl->o2w(os_ray);

      return ws_ray;

    }

  }
}
