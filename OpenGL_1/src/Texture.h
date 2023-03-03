#pragma once
#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& path);
	Texture(const std::string& path, unsigned int req_channel, unsigned int min_filter_mode, unsigned int mag_filter_mode, unsigned int wrap_s_mode, unsigned int wrap_t_mode, bool fliped, bool generateMipmap);
	Texture(int width, int height, unsigned int min_filter_mode, unsigned int mag_filter_mode, unsigned int wrap_s_mode, unsigned int wrap_t_mode, unsigned int format);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void SetType(const std::string& type);
	inline int GetWith() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetRenderID() const { return m_RenderID; }
	inline std::string GetType() const { return m_Type; }

private:
	unsigned int m_RenderID;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BytesPerPixel;
	std::string m_Type;
};