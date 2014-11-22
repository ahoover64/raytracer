#include "gssmraytracer/shaders/RefShader.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/geometry/Primitive.h"
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

utils::Color RefShader::shade(const geometry::DifferentialGeometry &dg, int bounce_num) const {
  utils::Color c_refl = mImpl->color;
  utils::Color c_refr = mImpl->color;
  utils::Color c_lamb = mImpl->color;
  math::Vector dir = dg.dir;
  math::Vector normal(dg.nn.x(), dg.nn.y(), dg.nn.z());
  normal.normalize();
  int next_bounce = bounce_num + 1;
  if(bounce_num < mImpl->MAX_BOUNCE) {

    // REFLECTION SET UP
    std::shared_ptr<geometry::DifferentialGeometry> dg_refl;
    std::shared_ptr<geometry::Primitive> p_refl;
    utils::Ray refl(dg.p, dir - 2*(dir.dot(normal))*normal);
    refl.setMint(0.05);
    float thit_refl;

    // REFRACTION SET UP
    std::shared_ptr<geometry::DifferentialGeometry> dg_refr;
    std::shared_ptr<geometry::Primitive> p_refr;
    utils::Ray refr(dg.p, (mImpl->n*dir + (mImpl->n*(dir.dot(normal))
                    - sqrt(1 - mImpl->n*mImpl->n*(1 - (dir.dot(normal))*
                    (dir.dot(normal)))))*normal));
    refr.setMint(0.05);
    float thit_refr;
    if(mImpl->refl_w > 0.f && utils::Scene::getInstance().hit(refl, thit_refl, dg_refl, p_refl)) {
      c_refl = p_refl->shade(dg_refl, next_bounce);
    }
    if(mImpl->refr_w > 0.f && utils::Scene::getInstance().hit(refr, thit_refr, dg_refr, p_refr)) {
      c_refr = p_refr->shade(dg_refr, next_bounce);
    }
  }
  c_lamb = LambertianShader::shade(dg, next_bounce);
  utils::Color avg_color = (c_refl*mImpl->refl_w + c_refr*mImpl->refr_w
                         + c_lamb*mImpl->lamb_w) / (mImpl->refl_w+mImpl->refr_w+mImpl->lamb_w);
  return avg_color;
}
