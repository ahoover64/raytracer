#include "gssmraytracer/shaders/RefShader.h"
#include "gssmraytracer/utils/Ray.h"
#include <math.h>

using namespace gssmraytracer::shaders;
using namespace gssmraytracer;

class RefShader::Impl {
public:
  int MAX_BOUNCE;
  float refl_w;
  float refr_w;
  float lamb_w;
  float n;
  utils::Color color;
};

RefShader::RefShader() : LambertianShader(utils::Color(0,0,0,1)), mImpl(new Impl) {
  mImpl->MAX_BOUNCE = 5;
  mImpl->refl_w = 1.f;
  mImpl->refr_w = 1.f;
  mImpl->lamb_w = 1.f;
  mImpl->n = .5f;
  mImpl->color = utils::Color(0,0,0,1);
}

RefShader::RefShader(utils::Color col, int max_bounces, float lamb_weight, float reflection_weight,
                    float refraction_weight, float ref_index) : LambertianShader(col), mImpl(new Impl) {
  mImpl->MAX_BOUNCE = max_bounces;
  mImpl->lamb_w = lamb_weight;
  mImpl->refl_w = reflection_weight;
  mImpl->refr_w = refraction_weight;
  mImpl->n = ref_index;
  mImpl->color = col;
}

utils::Color RefShader::shade(const std::shared_ptr<geometry::DifferentialGeometry> &dg,
                              int bounce_num, const utils::Ray &ray) const {
  utils::Color c_refl = mImpl->color;
  utils::Color c_refr = mImpl->color;
  utils::Color c_lamb = mImpl->color;
  if(bounce_num < mImpl->MAX_BOUNCE) {
    std::shared_ptr<geometry::DifferentialGeometry> dg_refl;
    float thit_refl;
    utils::Ray refl(dg.p, ray.dir() - 2*(ray.dir().dot(dg.nn))*dg.nn);

    std::shared_ptr<geometry::DifferentialGeometry> dg_refr;
    utils::Ray refr(dg.p, mImpl->n*ray.dir() + (mImpl->n*(ray.dir().dot(dg.nn))
                    - sqrt(1 - mImpl->n*mImpl->n*(1 - (ray.dir().dot(dg.nn))*(ray.dir().dot(dg.nn))))*dg.nn));
    float thit_refr;
    if(Scene::getInstance().hit(refl, thit_refl, dg_refl)) {
      c_refl = shade(dg_refl, ++bounce_num, refl);
      --bouncen_um;
    }
    if(Scene::getInstance().hit(refr, thit_refr, dg_refr)) {
      c_refr = shade(dg_refl, ++bounce_num, refr);
      --bounce_num;
    }
  }
  c_lamb = LambertianShader::shade(dg);
  utils::Color avg_color = (c_refl*mImpl->refl_w
                          + c_refr*mImpl->refr_w
                          + c_lamb*mImpl->lamb_w) / (3 * mImpl->refl_w * mImpl->refr_w * mImpl->lamb_w);
  return avg_color;
}
