#ifndef __NORMALSHADER_H__
#define __NORMALSHADER_H__
#include "gssmraytracer/shaders/Shader.h"
#include <gssmraytracer/utils/Color.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class NormalShader: public shaders::Shader {
    public:
      NormalShader();
      NormalShader& operator=(const NormalShader &);
      Color shade(const geometry::DifferentialGeometry &dg, int bounce_num) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}

#endif
