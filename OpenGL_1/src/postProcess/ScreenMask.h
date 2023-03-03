#pragma once
#include "geometry/Quad.h"

#define DEFAULT_SCREEN_SHADER "screen"

class ScreenMask
{
public:
	ScreenMask();
	~ScreenMask();

	inline Shader& GetShader() const { return *m_Shader; }
	void SetShader(const std::string& name);
	void Update();
	//void BindTexture(unsigned int id, unsigned int slot = 0);
	void Draw(Texture& tex, unsigned int bindSlot = 0);

private:
	std::unique_ptr<Quad> m_Mask;
	std::shared_ptr<Shader> m_Shader;
};