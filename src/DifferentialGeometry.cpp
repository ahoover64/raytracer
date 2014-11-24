#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace geometry {
    DifferentialGeometry::DifferentialGeometry() : p(Point(0,0,0)), nn(Normal(0,0,0)), u(0.f), v(0.f), dpdu(math::Vector(0,0,0))
                                            , dpdv(math::Vector(0,0,0)), dir(math::Vector(0,0,0)), dndu(Normal(0,0,0)), dndv(Normal(0,0,0)){}

    DifferentialGeometry::DifferentialGeometry(
          const Point &P,
          const math::Vector &DPDU, const math::Vector &DPDV,
          const Normal &DNDU, const Normal &DNDV,
          const float uu,
          const float vv,
          const Shape *sh) : p(P), nn(0.,1.,0.), u(uu), v(vv), dpdu(DPDU), dpdv(DPDV), dir(math::Vector()),
                      dndu(DNDU), dndv(DNDV), shape(sh){

              nn = Normal(dpdu.cross(dpdv)).normalized();

          }
          DifferentialGeometry::DifferentialGeometry(
                                            const DifferentialGeometry &dg) :
            p(dg.p), nn(dg.nn), u(dg.u), v(dg.v), dpdu(dg.dpdu), dpdv(dg.dpdv),
            dndu(dg.dndu), dndv(dg.dndv), shape(dg.shape) {}



  }
}
