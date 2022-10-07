#pragma once
#include "Geometry.h"
#include "Image.h"

class Plane : public Geometry
{
public:
	Plane();
	~Plane();

	void Update() override;
	void Draw(Shader& shader) override;
	void BindImage(unsigned int slot = 0) override;

private:
	std::unique_ptr<Image> m_Tex;
};