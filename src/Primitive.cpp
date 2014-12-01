#include "gssmraytracer/geometry/Primitive.h"
namespace gssmraytracer {
  namespace geometry {
    class Primitive::Impl {
    public:
      std::shared_ptr<Shape> shape;
      std::shared_ptr<shaders::Shader> shader;

    };

    Primitive::Primitive(const std::shared_ptr<Shape> &shape,
      const std::shared_ptr<shaders::Shader> &shader) : mImpl(new Impl) {
        mImpl->shape = shape;
        mImpl->shader = shader;
      }

    bool Primitive::hit(const utils::Ray &ws_ray) const {
      float thit;
      return hit(ws_ray, thit);
    }
    bool Primitive::hit(const utils::Ray &ws_ray, float &hit_time) const {
      return mImpl->shape->hit(ws_ray, hit_time);
    }

    bool Primitive::hit(const utils::Ray &ws_ray, float &hit_time,
                        std::shared_ptr<DifferentialGeometry> &dg) const {
      return mImpl->shape->hit(ws_ray, hit_time, dg);
    }

    const utils::Color Primitive::shade(const std::shared_ptr<DifferentialGeometry> &dg, int bounce_num) const {
      return mImpl->shader->shade(*dg, bounce_num);
    }

    const BBox worldBound() const {
      return mImpl->shape->worldBB();
    }
  }
}
