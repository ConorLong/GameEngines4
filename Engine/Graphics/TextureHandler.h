#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include<memory>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<memory>
#include<glew.h>
#include"../Core/Debug.h"

struct Texture {
	GLuint textureID = 0;
	float width;
	float height;
	std::string textureName = "";
};
class TextureHandler
{
public:
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator= (TextureHandler&&) = delete;
	static TextureHandler* GetInstance();
	void OnDestroy();

	void CreateTexture(const std::string& textureName, const std::string& filePath);
	const GLuint GetTexture(const std::string& textureName);
	const Texture* GetTextureData(const std::string textureName);

private:
	TextureHandler();
	~TextureHandler();

	static std::unique_ptr<TextureHandler> textureInstance;
	friend std::default_delete<TextureHandler>;
	static std::vector<Texture*> textures;
};
#endif

