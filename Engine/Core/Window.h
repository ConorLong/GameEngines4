#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>


class Window
{
public:
	Window();
	~Window();

	bool OnCreate(std::string name, int width, int height);
	void OnDestroy();
	inline int GetWidth() const;
	inline int GetHeight() const;
	SDL_Window* GetWindow() const;


private:

	void SetPreAtts();
	void SetPostAtts();

	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext context;

};

#endif