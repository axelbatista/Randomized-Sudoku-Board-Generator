#pragma once
#include <string>

class Texture {
public:
	Texture(const std::string& filepath);
	~Texture();
	void Bind(unsigned int slot);
private:
	unsigned char* buffer;
	int width, height, mBPP;
	unsigned int renderId;
};