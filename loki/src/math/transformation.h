#include<iostream>
#include "vector.h"
#include "matrix.h"
#include "operation.h"
#define _USE_MATH_DEFINES
#include <cmath> 
namespace math
{
	template<std::size_t m, std::size_t n, typename T>
	matrix<m, n, T> scale(vector<n, T> scale)
	{
		matrix<n, m, T> result;
		for (std::size_t i = 0; i < n; i++)
		{
			result[i][i] *= scale[i];
		}

		return result;
	}

	template<typename T>
	matrix<4, 4, T> scale(vector<3, T> scale)
	{
		matrix<4, 4, T> result;
		for (int i = 0; i < 3; i++)
		{
			result[i][i] *= scale[i];
		}
		return result;
	}

	template<typename T>
	matrix<4, 4, T> scale(matrix<4, 4, T> &mat, vector<3, T> scale)
	{
		for (int i = 0; i < 3 i++)
		{
			mat[i][i] *= scale[i];
		}
		return mat;
	}

	template<typename T>
	matrix<4, 4, T> rotate(const vector<3, T> &axis, const T& angle)
	{

	}

	//translation is only defined for 4x4 matrices
	template<typename T>
	matrix<4, 4, T> translate(const vector<3, T>& translation)
	{
		mat4 result;
		result[3] = vector<4, T>(translation, 1.0f);
		return result;
	}

	template<typename T>
	matrix<4, 4, T> orthographic()
	{


	}

	template<typename T>
	matrix<4, 4, T> lookAt(vector<3, T> from, vector<3, T> to, vector<3, T> tmp = vector(0, 1, 0))
	{
		matrix<4, 4, T> camToWorld;

		vec3 forward = normalize(from - to);
		vec3 right = cross(normalize(tmp), forward);
		vec3 up = cross(forward, right);

		camToWorld[0].xyz = right;
		camToWorld[1].xyz = up;
		camToWorld[2].xyz = forward;
		camToWorld[3].xyz = from;

		return camToWorld;
	}
	
	template<typename T>
	matrix<4, 4, T> perspective(T fov, T angle, T far, T near)
	{
		matrix<4, 4, T> result;
		float scale = 1 / tan(fov * 0.5f * M_PI / 180);
		result[0][0] = scale; //scaling the x coord
		result[1][1] = scale; //scaling the y coord
		result[2][2] = -far / (far - near); //remap z to [0,1]
		result[3][2] = -far * near / (far - near); //remap z to [0,1]
		result[3][3] = 0.0f;
		return result;
	}
}