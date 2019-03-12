#include <iostream>
#include "vector.h"

namespace math
{
	struct quaternion
	{
		union
		{
			struct
			{
				float x, y, z;
			};
			vec3 vec;
		};
		float w;

		quaternion(const float x, const float y, const float z, const float w): x(x), y(y), z(z), w(w)
		{

		}
	};

	inline quaternion operator+(const quaternion& lhs, const quaternion& rhs)
	{
		return quaternion(lhs.x + rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, lhs.w+rhs.w);
	}

	inline quaternion operator*(const quaternion& lhs, const float scalar)
	{
		return quaternion(lhs.x*scalar, lhs.y*scalar, lhs.z*scalar, lhs.w*scalar);
	}

	inline quaternion operator*(const quaternion& rhs, const float scalar)
	{
		return quaternion(rhs.x*scalar, rhs.y*scalar, rhs.z*scalar, rhs.w*scalar);
	}

	inline quaternion operator/(const quaternion& lhs, const float scalar)
	{
		return quaternion(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar, lhs.w / scalar);
	}

	//quaternion geometry
	inline float length(const quaternion& quat)
	{
		return sqrt(quat.x * quat.x + quat.y*quat.y + quat.z*quat.z + quat.w*quat.w);
	}

	inline quaternion dot(const quaternion& lhs, const quaternion& rhs)
	{
		return quaternion(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
	}

	inline quaternion& normalize(quaternion& quat)
	{
		const float l = length(quat);
		quat = quat / l;
		return quat;
	}
}