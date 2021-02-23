#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include<sstream>
#include<unordered_map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Core/Debug.h"
class ShaderHandler
{
public:
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();

	void CreateProgram(const std::string& shaderName, const std::string& vertFile, const std::string& fragFile);
	GLuint GetShader(const std::string& programName);
	void OnDestroy();

private:
	ShaderHandler();
	~ShaderHandler();
	
	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>;

	std::string ReadShader(const std::string& filePath);
	GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);

	static std::unordered_map<std::string, GLuint> programs;
};
#endif
