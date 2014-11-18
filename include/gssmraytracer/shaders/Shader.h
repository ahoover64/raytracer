#ifndef __SHADER_H__
#define __SHADER_H__

#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace shaders {
    class Shader {
    public:
      virtual utils::Color shade(const geometry::DifferentialGeometry &dg) const = 0;
    };
  }
}
#endif //__SHADER_H__
