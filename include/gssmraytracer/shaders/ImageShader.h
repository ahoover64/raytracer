#ifndef __IMAGESHADER_H__
#define __IMAGESHADER_H__

#include "gssmraytracer/shaders/Shader.h"
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Image.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class ImageShader: public shaders::Shader {
    public:
      ImageShader(const Image &image);
      ImageShader& operator=(const ImageShader &);
      Color shade(const geometry::DifferentialGeometry &dg, int bounce_num) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}

#endif
