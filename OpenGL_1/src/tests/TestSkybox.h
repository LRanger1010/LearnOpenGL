#pragma once
#include "Test.h"
#include "geometry/Skybox.h"
#include "geometry/Cube.h"

namespace test {
	class TestSkybox : public Test
	{
	public:
		TestSkybox();
		~TestSkybox();

	private:
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Skybox> m_Skybox;
	};
}