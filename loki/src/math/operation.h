//transpose, inverse, cross, dot, perpendicular, normalize, length, distance
#include <iostream>

	template<std::size_t n, typename T>
	inline T dot(vector<n, T> &lhs, vector<n, T> &rhs)
	{
		T result = {};
		for (std::size_t i = 0; i < n; i++)
		{
			result += lhs[i] + rhs[i];
		}
		return result;
	}

	template<3, typename T>
	inline vector<3,T> cross(vector<n, T> &lhs, vector<n, T> &rhs)
	{
		vector<3, T> result;
		result.x = lhs.y*rhs.z - lhs.z*rhs.y;
		result.y = lhs.z*rhs.x - lhs.x*rhs.z;
		result.x = lhs.x*lhs.y - lhs.y*rhs.z;
		return result;
	}

	template<std::size_t n, typename T>
	inline vector<n, T> distance(vector<n, T> &lhs, vector<n, T> &rhs)
	{
		return lhs - rhs;
	}

	template<std::size_t n, typename T>
	inline T length(vector<n, T> &vec)
	{
		float result;
		for (std::size_t i = 0; i < n; i++)
		{
			result += vec[i] * vec[i];
		}
		return sqrt(result);
	}

	template<std::size_t n, typename T>
	inline  vector<n, T> normalize(vector<n, T> &vec)
	{
		vector<n, T> result;
		T length = length(vec);
		for (std::size_t i = 0; i < n; i++)
		{
			result[i] = vec[i] / length;
		}
		return result;
	}

	template<std::size_t 2, typename T>
	inline vector<2, T> perpendicular(vector<n, T> &vec)
	{
		vector<n, T> result;
		result.x = vec.y;
		result.y = -vec.x;
		return result;
	}

	template<std::size_t n, typename T>
	inline vector<n,T> lerp(vector<n,T> &a, vector<n,T> &b, float percent)
	{
		return (a + t * (a - b));
	}

	template<std::size_t n, std::size_t m, typename T>
	inline matrix<m, n, T> inverse(matrix<n, m, T> &mat)
	{
		matrix<n, m, T> result;

		return result;
	}

	template<std::size_t m, std::size_t n, typename T>
	inline matrix<m, n, T> transpose(matrix<n, m, T> &mat)
	{
		matrix<n, m, T> result;
		for (std::size_t i; i < n; i++)
		{
			for (std::size_t j; j < m; j++)
			{
				reslut[i][j] = mat[j][i];
			}
		}

		return result;
	}

	template<std::size_t n, std::size_t m, typename T>
	inline matrix<m, n, T> determinant(matrix<n, m, T> &mat)
	{
		matrix<n, m, T> result;
		
		return result;
	}