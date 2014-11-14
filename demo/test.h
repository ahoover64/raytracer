#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Ray.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/math/Transform.h>
#include <gssmraytracer/math/Vector.h>
#include <gssmraytracer/geometry/Point.h>
#include <gssmraytracer/geometry/DifferentialGeometry.h>
#include <gssmraytracer/geometry/Primitive.h>
#include "LambertianShader.h"
#include "Sphere.h"
#include "PointLight.h"
#include <memory>
#include <iostream>

using namespace gssmraytracer::math;
using namespace gssmraytracer::geometry;
using namespace gssmraytracer::utils;

int main(int argc, char* argv[]) {
    std::shared_ptr<gssmraytracer::Light> light(new gssmraytracer::PointLight(Color(1,1,1,1), 7.f, Point(0, 5, 0)));
    Vector v(5,0,0);
    Transform t;
    t.translate(v);
    std::shared_ptr<Sphere> s(new Sphere(t, 5.f));
    Ray r(Point(0,5,0), Vector(.5,-.5,0));
    float t_hit;
    std::shared_ptr<DifferentialGeometry> dg;
    std::shared_ptr<LambertianShader> shady(new LambertianShader(Color(0, 1, 0, 1)));
    Scene::getInstance().addLight(light);
    std::shared_ptr<Primitive> p(new Primitive(s, shady));
    Scene::getInstance().addPrimitive(p);
    std::cout << Scene::getInstance().hit(r, t_hit, dg) << std::endl;
    Color c = shady->shade(*dg);
    std::cout << c.red << ", " << c.green << ", " << c.blue << std::endl;
    return true;
}
