#include "gssmraytracer/shaders/BestShader.h"
#include <gssmraytracer/utils/Color.h>

using namespace gssmraytracer::geometry;
namespace gssmraytracer {
  namespace utils {


    BestShader::BestShader() : Shader() {}

    Color BestShader::shade(const geometry::DifferentialGeometry &dg) {
		     int n = (int) (dg.u * 8) % 2;
		     int n2 = (int) (dg.v * 8) % 2;
                     return Color(n, 1, n2, 1);
                   }
  }
}
