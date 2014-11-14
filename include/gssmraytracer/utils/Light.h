#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <memory>
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/math/Vector.h"

namespace gssmraytracer {
	class Light{
	public:
		Light();
		Light(utils::Color c, float intensity);
		float intensity() const;
		utils::Color color() const;
		virtual bool hit(const geometry::DifferentialGeometry &dg) const = 0;
		virtual math::Vector lightDir(const geometry::DifferentialGeometry &dg) const = 0;

	private:
		class Impl;
		std::shared_ptr<Impl> mImpl;
	};
}
#endif // __LIGHT_H__
