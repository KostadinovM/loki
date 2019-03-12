#include <iostream>
#include <array>
#include <assert.h>
namespace math
{
	//generic vector representation
	template <std::size_t n, class T>
	struct vector
	{
		std::array<T, n> data;

		//constructor1: default constructor; initializes to default values
		vector(const T& v)
		{
			for (auto& el : data)
			{
				el = v;
			}
		}

		//constructor2: initializes all vector values to the given value
		vector(const std::initializer_list<T> list)
		{
			//data = list;
		}


		
		T& operator[](const std::size_t index)
		{
			return data.at(index);
		}


	};

	//2D specific custom vector class
	template <typename T>
	struct vector<2, T>
	{
		union
		{
			std::array<T, 2> data;

			//position coordinates
			struct 
			{
				T x, y;
			};

			//texture coordinates
			struct
			{
				T s, t;
			};
		};

		//constructor0: initialize an empty vector
		vector()
		{
			data = {};
		}

		//constructor1: intialize vector to a single given value
		vector(const T& v)
		{
			data = { v, v };
		}

		//constructor2: takes elements separately
		vector(const T& x, const T& y)
		{
			data = { x, y };
		}

		//contructor3: vec2 initialization
		vector(const T& x, const vector<2, T> vec2)
		{
			data = { x, vec2.x, vec2.y };
		}

		//contructor4: vec2 initialization
		vector(const vector<2,T> vec2, const T& z)
		{
			data = { vec2.x, vec2.y,z };
		}

		//constructor5: takes a list 
		vector(const std::initializer_list<T> list)
		{

		}


		T& operator[](const std::size_t index)
		{
			return data.at(index);
		}

	};

	template<typename T>
	struct vector<3, T>
	{
		union
		{
			std::array<T, 3> data;

			//position coordinates
			struct
			{
				T x, y, z;
			};

			//color coordinates
			struct
			{
				T r, g, b;
			};
			//texture coordinates
			struct
			{
				T s, t, r;
			};
		};

		//constructor0: initialize an empty vector
		vector()
		{
			data = {};
		}

		//constructor1: intialize vector to a single given value
		vector(const T& v)
		{
			data = { v, v, v };
		}

		//constructor2: takes elements separately
		vector(const T& x, const T& y, const T& z)
		{
			data = { x, y, z };
		}

		//constructor 3: takes a list 
		vector(const std::initializer_list<T> list)
		{

		}


		T& operator[](const std::size_t index)
		{
			return data.at(index);
		}
	};

	template<typename T>
	struct vector<4, T>
	{
		union
		{
			std::array<T, 4> data;

			//position coordinates
			struct
			{
				T x, y, z, w;
			};

			//color coordinats
			struct
			{
				T r, g, b, a;
			};

			//texture coordinates
			struct
			{
				T s, t, r;
			};
		};

		//constructor0: initialize an empty vector
		vector()
		{
			data = {};
		}

		//constructor1: intialize vector to a single given value
		vector(const T& v)
		{
			data = { v, v, v, v };
		}

		//constructor2: takes elements separately
		vector(const T& x, const T& y, const T& z, const T& w)
		{
			data = { x, y, z, w };
		}

		//constructor3: initialization with vec2s
		vector(const vector<2, T> xy, const vector<2, T> zw)
		{
			data = { xy.x, xy.y, zw.x, zw.y };
		}

		//costructor4: lnitialize with vec3
		vector(const vector<3, T> vec3, const T &w)
		{
			data = { vec3.x, vec3.y, vec3.z, w };
		}

		//constructor5: initialize with vec3
		vector(const T& x, const vector<3, T> vec)
		{
			data = { x, vec.y, vec.z, vec.w };
		}

		//constructor 6: list initialization
		vector(const std::initializer_list<T> list)
		{

		}

		T& operator[](const std::size_t index)
		{
			return data.at(index);
		}
	};

	typedef vector<2, float> vec2;
	typedef vector<3, float> vec3;
	typedef vector<4, float> vec4;
		

	//vector operator overrides

	//adding
	template<std::size_t n, typename T>
	inline vector<n, T> operator+(const vector<n, T>& lhs, const T& scalar)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; ++i)
		{
			result[i] = lhs[i] + scalar;
		}
		return result;
	}

	template<std::size_t n, typename T>
	inline vector<n, T> operator+ (vector<n, T>& lhs, vector<n, T>& rhs)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; ++i)
		{
			result[i] = lhs[i] + rhs[i];
		}
		return result;
	}

	//subtracting
	template<std::size_t n, typename T>
	inline vector<n, T> operator-(vector<n, T>& lhs, T& scalar)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; ++i)
		{
			result[i] = lhs[i] = scalar;
		}
		return result;
	}

	template<std::size_t n, typename T>
	inline vector<n, T> operator-(vector<n, T>& lhs, vector<n, T>& rhs)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; ++i)
		{
			result[i] = lhs[i] - rhs[i];
		}
		return result;
	}
	
	//multiplying
	template<std::size_t n, typename T>
	inline vector<n, T> operator*(vector<n, T>& lhs, T& scalar)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; ++i)
		{
			result[i] = lhs[i] * scalar;
		}
		return result;
	}

	template<std::size_t n, typename T>
	inline vector<n, T> operator*(vector<n, T>& lhs, vector<n, T>& rhs)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; ++i)
		{
			result[i] = lhs[i] * rhs[i];
		}
		return result;
	}

	//dividing
	template<std::size_t n, typename T>
	inline vector<n, T> operator/(vector<n, T>& lhs, T& scalar)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; i++)
		{
			result[i] = lhs[i] / scalar;
		}
		return result;
	}

	template<std::size_t n, typename T>
	inline vector<n, T> operator/(vector<n, T>& lhs, vector<n, T>& rhs)
	{
		vector<n, T> result;
		for (std::size_t i = 0; i < n; i++)
		{
			result[i] = lhs[i] / rhs[i];
		}
		return result;
	}
}