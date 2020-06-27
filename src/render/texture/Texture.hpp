#pragma once

#include <string>

class Texture {
public:
	Texture(const std::string &path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const {
		return m_Width;
	}

	int GetHeight() const {
		return m_Height;
	}

private:
	std::string m_FilePath;
	unsigned int m_RendererID = 0;
	unsigned char *m_LocalBuffer = nullptr;
	int m_Width = 0;
	int m_Height = 0;
	int m_BPP = 0;
};

