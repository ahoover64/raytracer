#ifndef __POINT_H__
#define __POINT_H__
#include <memory>
#include <OpenEXR/ImathVec.h>
namespace gssmraytracer {
  namespace math {
    class Vector;
  }
}

namespace gssmraytracer {
  namespace geometry {
    class Point {
    public:
      //! Initializes a point at (0,0,0)
      Point();

      //! Initializes a point based on x, y and z
      Point(const float x, const float y, const float z);

      //! Initializes a point based on an OpenEXR vec3<float>
      Point(const Imath::Vec3<float> &vec);

      //! converts a Vector to a point
      Point(const math::Vector &vec);

      //! Copy constructor
      Point(const Point &);

      //! Assignment operator
      Point& operator=(const Point &);

      //! Returns a new Point which is the sum of a Vector and this point
      Point operator+(const math::Vector &vec) const;

      //! Returns a new Point which is the sum of a Vector and this point
      Point operator+(const Point &pt) const;

      //! Returns a Vector
      math::Vector operator-(const geometry::Point &pt) const;

      //! Return a new scaled point
      Point operator*(const float s) const;

      //! Allows for printing on Point in std::cout
      friend std::ostream& operator<<(std::ostream &os, const Point &point);

      const float operator[](const float index) const;

      //! returns the x component of a Point
      const float x() const;

      //! sets the x component of a Point
      void x(float xx);

      //! returns the y component of a Point
      const float y() const;

      //! sets the y component of a Point
      void y(float yy);

      //! returns the z component of a Point
      const float z() const;

      //! sets the z component of a Point
      void z(float zz);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
#endif //__POINT_H__
