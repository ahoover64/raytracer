#ifndef __SCENE_H__
#define __SCENE_H__
#include <memory>
#include <vector>
#include "gssmraytracer/geometry/Primitive.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"
#include "gssmraytracer/lights/Light.h"

namespace gssmraytracer {
  namespace utils {
    class Scene {
    public:
      static Scene& getInstance();
      void addPrimitive(const std::shared_ptr<geometry::Primitive> &);
      void addLight(const std::shared_ptr<lights::Light> &lite);
      bool hit(const Ray &ws_ray) const;
      bool hit(const Ray &ws_ray, float &hit_time) const;
      bool hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg) const;
      bool hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg,
        std::shared_ptr<geometry::Primitive> &prim) const;
      bool hitLight(const geometry::DifferentialGeometry &dg, std::shared_ptr<lights::Light> &lite) const;
      float totalLight(const geometry::DifferentialGeometry &dg) const;
      ~Scene();
    private:
      Scene();
      Scene(const Scene&);
      Scene& operator=(const Scene&);
      class Impl;
      std::shared_ptr<Impl> mImpl;


    };
  }
}

#endif // __SCENE_H__
