#ifndef __CHECKEREDSHADER_H__
#define __CHECKEREDSHADER_H__

#include "gssmraytracer/shaders/Shader.h"
#include <memory>

namespace gssmraytracer {
  namespace shaders {
    class CheckeredShader : public shaders::Shader {
    public:
      CheckeredShader();
      CheckeredShader(const utils::Color &c1, const utils::Color &c2, float side_length);
      utils::Color shade(const geometry::DifferentialGeometry &dg);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}

#endif
