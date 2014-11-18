#ifndef __CHECKEREDSHADER_H__
#define __CHECKEREDSHADER_H__

#include "gssmraytracer/shaders/Shader.h"
#include <memory>

namspace gssmraytracer {
  namespace shaders {
    class CheckeredShader : public Shader {
    public:
      CheckeredShader();
      CheckeredShader(geometry::Color c1, geometry::Color c2, float side_length);
      Color shade(const geometry::DifferentialGeometry &dg);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    }
  }
}

#endif
