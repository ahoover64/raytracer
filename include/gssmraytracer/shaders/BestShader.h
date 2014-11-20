#ifndef __BESTSHADER_H__
#define __BESTSHADER_H__
#include <gssmraytracer/shaders/Shader.h>
#include <gssmraytracer/utils/Color.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class BestShader: public shaders::Shader {
    public:
      BestShader();
      BestShader& operator=(const BestShader &);
      Color shade(const geometry::DifferentialGeometry &dg, int bounce_num) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}

#endif
