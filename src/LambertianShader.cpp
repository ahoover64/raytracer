/*****************************************************
LambertianShader.cpp
October 27, 2014
Kacey Coley
Description:
This shader uses the lambertian shading model to determine the surface color.
The lambertian shading model is essentially a matte surface.
However, this shader is missing a proper light class in the implementation.
The lighting information has been hardcoded in.  You should implement a light
class and replace the hardcoded information with your team's implementation.

*****************************************************/
#include "gssmraytracer/shaders/LambertianShader.h"
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Scene.h>
#include "gssmraytracer/lights/PointLight.h"
#include "gssmraytracer/lights/Light.h"

using namespace gssmraytracer::geometry;
using namespace gssmraytracer::shaders;
using namespace gssmraytracer::utils;

class LambertianShader::Impl {
public:
  Color color;
};

LambertianShader::LambertianShader(const Color &color) : mImpl(new Impl) {
  mImpl->color = color;
}
LambertianShader::LambertianShader(const LambertianShader &other) :
                                        Shader(),
                                        mImpl(new Impl) {
  mImpl->color = other.mImpl->color;
}

LambertianShader& LambertianShader::operator=(const LambertianShader &other) {
  if (this != &other) {
    mImpl->color = other.mImpl->color;
  }
  return *this;
}
Color LambertianShader::shade(const geometry::DifferentialGeometry &dg, int bounce_num) const {

  // initialize the return color for the shader to black
  Color shadeColor(0,0,0,1);

  std::shared_ptr<lights::Light> light(new lights::PointLight());

  // ambient lighting - faking global illumination with constant
  // low color value
  shadeColor.red = mImpl->color.red * 0.2f;
  shadeColor.green = mImpl->color.green * 0.2f;
  shadeColor.blue = mImpl->color.blue * 0.2f;

  if (Scene::getInstance().hitLight(dg, light)) { // if no objects in the way, do lighting
    math::Vector light_vec = light->lightDir(dg);
    float fall_off = (light_vec.length() * light_vec.length());

    float shadeAngle = abs(light_vec.normalized().dot(dg.nn));

    float factor = -1*shadeAngle*light->intensity()/fall_off;
    shadeColor.red += mImpl->color.red*factor;
    shadeColor.green += mImpl->color.green*factor;
    shadeColor.blue += mImpl->color.blue*factor;
  }

   return shadeColor;
}
