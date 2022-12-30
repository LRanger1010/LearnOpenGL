#pragma once
#include "Geometry.h"

class Quad : public Geometry
{
public:
	Quad();
	~Quad();

	void Update() override;
	void Draw(Shader& shader) override;
	
protected:
	void SetMesh() override;
	void SetMaterial() override;

private:
	
};