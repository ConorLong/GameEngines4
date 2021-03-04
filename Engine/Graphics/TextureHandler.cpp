#include "TextureHandler.h"
std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;
std::vector<Texture*> TextureHandler::textures = std::vector<Texture*>();

TextureHandler::TextureHandler()
{
	textures.reserve(10);
}

TextureHandler* TextureHandler::GetInstance()
{
	if (textureInstance.get() == nullptr) {
		textureInstance.reset(new TextureHandler);
	}
	return textureInstance.get();
}

void TextureHandler::CreateTexture(const std::string& textureName, const std::string& filePath)
{
	if (GetTextureData(textureName)) {
		return;
	}
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(filePath.c_str());
	if (surface == nullptr) {
		Debug::Error("Surface for texture " + textureName + "failed to be created", "TextureHandler.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}
	glGenTextures(1, &t->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	t->width = static_cast<float>(surface->w);
	t->height = static_cast<float>(surface->h);
	t->textureName = textureName;

	textures.push_back(t);

	SDL_FreeSurface(surface);
	surface = nullptr;
}

const GLuint TextureHandler::GetTexture(const std::string& textureName)
{
	for (auto t : textures) {
		if (t->textureName == textureName) {
			return t->textureID;
		}
	}
	return 0;
}

const Texture* TextureHandler::GetTextureData(const std::string textureName)
{
	for (auto t : textures) {
		if (t->textureName == textureName) {
			return t;
		}
	}
	return nullptr;
}

void TextureHandler::OnDestroy()
{
	if (textures.size() > 0) {
		for (auto t : textures) {
			glDeleteTextures(1, &t->textureID);
			delete t;
			t = nullptr;
		}
		textures.clear();
	}
}
TextureHandler::~TextureHandler()
{
	OnDestroy();
}
