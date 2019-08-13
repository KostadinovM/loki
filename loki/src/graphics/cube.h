#pragma once
#include "mesh.h"


namespace Loki
{
	class Cube : public Mesh
	{
	public:
		Cube();
		void drawCube(Shader);
	};
}