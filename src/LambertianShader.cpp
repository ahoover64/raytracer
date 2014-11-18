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
Color LambertianShader::shade(const geometry::DifferentialGeometry &dg) const {

  // initialize the return color for the shader to black
  Color shadeColor(0,0,0,1);

  /************************************************************************/
  // hardcoded light info in the shader
  // this implementation should be done in the light object

  std::shared_ptr<lights::Light> light(new lights::PointLight());

  // no light falloff based on distance (defaulted to no falloff)
//      float distanceVal_no_falloff = 1.0f;

  // linear light falloff based on distance
//      float distanceVal_linear = (light_vec.length());

  // quadratic light falloff based on distance
//      float distanceVal_quadratic = (light_vec.length() * light_vec.length());

  /************************************************************************/


  // ambient lighting - faking global illumination with constant
  // low color value
  shadeColor.red = mImpl->color.red * 0.2f;
  shadeColor.green = mImpl->color.green * 0.2f;
  shadeColor.blue = mImpl->color.blue * 0.2f;

  // This implementation uses the singleton of the scene to see if we
  // hit any objects.  Note that we do not need to pass in the Scene as
  // an argument since a singleton is in the global namespace,
  // essentially, a global class where there is only one instance)
  if (Scene::getInstance().hitLight(dg, light)) { // if no objects in the way, do lighting
    math::Vector light_vec = light->lightDir(dg); // CHECK FOR POINT LIGHT
    float fall_off = (light_vec.length() * light_vec.length());

    // this computes the cosine of the angle between the light vector
    // and the geometry normal
    float shadeAngle = light_vec.normalized().dot(dg.nn);

    // if the angle is greater than 0, do the lambertian shading
    if (shadeAngle < 0) {
      // add the diffuse (matte) lighting to the ambient lighting based on
      // the intensity and the falloff factor based on the distance
      float factor = -1*shadeAngle*light->intensity()/fall_off;
      shadeColor.red += mImpl->color.red*factor;
      shadeColor.green += mImpl->color.green*factor;
      shadeColor.blue += mImpl->color.blue*factor;
    }
  }

   return shadeColor;
}
