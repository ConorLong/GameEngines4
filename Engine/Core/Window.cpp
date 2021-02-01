#include "Window.h"

Window::Window() : window (nullptr), context(nullptr)
{

}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	std::cout << "Failed to init SDL" << std::endl;
	return false;
	}
	
	this->width = width;
	this->height = height;

	SetPreAtts();
	window = SDL_CreateWindow(name.c_str(), 
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							width,
							height,
							SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "failed to create window" << std::endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetPostAtts();

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "failed to init GLEW" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

inline int Window::GetWidth() const
{
	return width;
}

inline int Window::GetHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAtts()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::SetPostAtts()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
