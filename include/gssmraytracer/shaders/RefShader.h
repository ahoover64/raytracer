#ifndef __REFSHADER_H__
#define __REFSHADER_H__
#include "gssmraytracer/shaders/LambertianShader.h"
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Ray.h>
#include <memory>

namespace gssmraytracer {
  namespace shaders {
    class RefShader : public shaders::LambertianShader {
    public:
      RefShader();
      RefShader(utils::Color col, int max_bounces, float lamb_weight, float reflection_weight,
                float refraction_weight, float ref_index);
      utils::Color shade(const geometry::DifferentialGeometry &dg,
                         int bounce_num, const utils::Ray &ray) const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}

#endif
