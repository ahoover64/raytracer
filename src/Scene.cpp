#include <vector>
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/lights/Light.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"
#include <limits>

namespace gssmraytracer {
  namespace utils {
    class Scene::Impl {
    public:
      Impl() : primitives(), lights(), bvh(), max_bounce_count(0) {}
      std::vector<std::shared_ptr<geometry::Primitive> > primitives;
      std::vector<std::shared_ptr<lights::Light>> lights;
      std::shared_ptr<BVHAccel> bvh;
      int max_bounce_count;
    };

    Scene::Scene() : mImpl(new Impl) {}

    Scene::~Scene() {

    }

    Scene& Scene::getInstance() {
      static Scene instance;
      return instance;
    }

    void Scene::init() {
      if (!mImpl->bvh) {
        uint32_t var = 1;
          std::shared_ptr<BVHAccel> bvh(new BVHAccel(mImpl->primitives, var));
          mImpl->bvh = bvh;

      }
    }


    void Scene::addPrimitive(const std::shared_ptr<geometry::Primitive> &primitive) {

      mImpl->primitives.push_back(primitive);
    }

    void Scene::addLight(const std::shared_ptr<lights::Light> &lite) {
      mImpl->lights.push_back(lite);
    }

    bool Scene::hit(const Ray &ws_ray) const {
      float thit = std::numeric_limits<float>::infinity();
      for (std::vector<std::shared_ptr<geometry::Primitive> >::const_iterator iter =
        mImpl->primitives.begin(); iter != mImpl->primitives.end(); ++iter) {

          if ((*iter)->hit(ws_ray, thit)) {
            return true;
          }
        }

        return false;

    }

    bool Scene::hit(const Ray &ws_ray, float &hit_time) const {
      std::shared_ptr<geometry::DifferentialGeometry> dg;
      std::shared_ptr<geometry::Primitive> prim;

      return hit(ws_ray, hit_time, dg, prim);
    }

    bool Scene::hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg) const {
      std::shared_ptr<geometry::Primitive> prim;
      return hit(ws_ray, hit_time, dg, prim);
    }

    bool Scene::hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg,
      std::shared_ptr<geometry::Primitive> &prim) const {

        bool result = mImpl->bvh->intersect(ws_ray, hit_time, dg, prim);

        return result;

      }

      const int Scene::maxBounceCount() const {
        return mImpl->max_bounce_count;
      }

      void Scene::maxBounceCount(const int max_bounce_count) {
        mImpl->max_bounce_count = max_bounce_count;
      }


    bool Scene::hitLight(const geometry::DifferentialGeometry &dg, std::shared_ptr<lights::Light> &lite) const {
        for (std::vector<std::shared_ptr<lights::Light>>::const_iterator iter =
          mImpl->lights.begin(); iter != mImpl->lights.end(); ++iter) {
            if ((*iter)->hit(dg)) {
              lite = (*iter);
              return true;
            }
          }
          return false;
    }

    float Scene::totalLight(const geometry::DifferentialGeometry &dg) const {
      float total_light = 0;
      float inten;
      for (std::vector<std::shared_ptr<lights::Light>>::const_iterator iter =
        mImpl->lights.begin(); iter != mImpl->lights.end(); ++iter) {
        if ((*iter)->hit(dg, inten)) {
          total_light += inten;
        }
      }
      return total_light;
    }


  }
}
