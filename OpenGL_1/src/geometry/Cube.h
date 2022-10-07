#pragma once
#include "Image.h"
#include "Geometry.h"

class Cube : public Geometry
{
public:
	Cube();
	~Cube();

	void Update() override;
	void Draw(Shader& shader) override;
	void BindImage(unsigned int slot = 0) override;

private:
	std::unique_ptr<Image> m_Tex;
};