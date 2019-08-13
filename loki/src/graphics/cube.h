#pragma once
#include "mesh.h"


namespace Loki
{
	namespace Graphics
	{
		class Cube : public Mesh
		{
		public:
			Cube();
			void drawCube(Shader);
		};
	}
}