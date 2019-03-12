#include <iostream>

namespace math
{
	//generic matrix representation
	template <std::size_t m, std::size_t n, class T>
	struct matrix
	{
		union
		{
			T mat[n][m];
			struct
			{
				vector<m, T> col[n];
			};
		};
		
		//constructor0: initialize into an identity matrix
		matrix()
		{
			for (std::size_t i = 0; i < n; i++)
			{
				for (std::size_t j = 0; i < m; i++)
				{
					//if row=col => diagonal index
					if (i == j)
						mat[i][j] = 1.0f;
					else
						mat[i][j] = 0.0f;
				}
			}
		}

		//constructor1: intialize all values of a matrix to given one
		matrix(const T& v)
		{
			for (std::size_t i = 0; i < n; i++)
			{
				for (std::size_t j = 0; j < m; j++)
				{
					mat[i][j] = v;
				}
			}
		}

		matrix(const std::initializer_list<T> list)
		{

		}

		//returns a column vector: allows to use [] and [][] for index access
		vector<m, T>& operator[](const std::size_t index)
		{
			return col[index];
		}

	};

	typedef matrix<2, 2, float> mat2;
	typedef matrix<3, 3, float> mat3;
	typedef matrix<4, 4, float> mat4;

	//matrix operator overrides
	template<std::size_t m, std::size_t n, typename T>
	inline matrix<n, m, T> operator+(matrix<n, m, T> &lhs, matrix<n,m,T> &rhs)
	{
		matrix<n, m, T> result;
		for (std::size_t i = 0; i < n; i++)
		{
			for (std::size_t j = 0; j < m; j++)
			{
				result[i][j] = lhs[i][j] + rhs[i][j];
			}
		}
		return result;
	}

	template<std::size_t m, std::size_t n, typename T>
	inline matrix<n, m, T> operator-(matrix<m, n, T> &lhs, matrix <m, n, T> &rhs)
	{
		matrix<n, m, T> result;
		for (std::size_t i = 0; i < n; i++)
		{
			for (std::size_t j = 0; j < m; j++)
			{
				result[i][j] = lhs[i][j] - rhs[i][j];
			}
		}
		return result;
	}

	template<std::size_t m, std::size_t n, typename T>
	inline matrix<n, m, T> operator*(matrix<m, n, T> &lhs, matrix<m, n, T> &rhs)
	{
		matrix<n, m, T> result;
		for (std::size_t i = 0; i < n; i++)
		{
			for (std::size_t j = 0; j < m; j++)
			{
				result[i][j] = lhs[i][j] * rhs[i][j];
			}
		}
		return result;
	}

	template<std::size_t m, std::size_t n, typename T>
	inline matrix<n, m, T> operator/(matrix<m, n, T> &lhs, matrix<m, n, T> &rhs)
	{
		matrix<n, m, T> result;
		for (std::size_t i = 0; i < n; i++)
		{
			for (std::size_t j = 0; j < m; j++)
			{
				result[i][j] = lhs[i][j] / rhs[i][j];
			}
		}
		return result;
	}
}