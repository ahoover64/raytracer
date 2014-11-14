#ifndef __BOUNDING_BOX__
#define __BOUNDING_BOX__

#include <memory>
#include <gssmraytracer/utils/Ray.h>
#include <gssmraytracer/geometry/Point.h>

namespace gssmraytracer {
  namespace geometry {
    class BoundingBox {
    public:
      BoundingBox();
      BoundingBox(const geometry::Point &min, const geometry::Point &max);
      bool hit(const utils::Ray &ws_ray) const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}

#endif //__BOUNDING_BOX__
