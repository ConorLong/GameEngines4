#include "ShaderHandler.h"
std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
std::unordered_map<std::string, GLuint> ShaderHandler::programs = std::unordered_map<std::string, GLuint>();


ShaderHandler::ShaderHandler() {

}

ShaderHandler* ShaderHandler::GetInstance()
{
	if (shaderInstance.get() == nullptr) {
		shaderInstance.reset(new ShaderHandler);
	}
	return shaderInstance.get();
}
void ShaderHandler::CreateProgram(const std::string& shaderName, const std::string& vertFile, const std::string& fragFile)
{
	std::string vertShaderCode = ReadShader(vertFile);
	std::string fragShaderCode = ReadShader(fragFile);
	if (vertShaderCode == "" || fragShaderCode == "") {
		return;
	}
	GLuint vertShader = CreateShader(GL_VERTEX_SHADER, vertShaderCode, shaderName);
	GLuint fragShader = CreateShader(GL_FRAGMENT_SHADER, fragShaderCode, shaderName);

	if (vertShader == 0 || fragShader == 0) {
		return;
	}

	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (!linkResult) {
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength); 
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::string programString(programLog.begin(), programLog.end());
		Debug::Error("Failed to link shader " + shaderName + ". Error: " + programString, "ShaderHandler.cpp", __LINE__);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		glDeleteProgram(program);
		return;
	}
	programs[shaderName] = program;
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

GLuint ShaderHandler::GetShader(const std::string& programName)
{
	if (programs.find(programName) != programs.end()) {
		return programs[programName];
	}
	return 0;
}

void ShaderHandler::OnDestroy()
{
	if (programs.size() > 0) {
		for (auto p : programs) {
			glDeleteProgram(p.second);
		}
		programs.clear();
	}
}

ShaderHandler::~ShaderHandler()
{
	OnDestroy();
}

std::string ShaderHandler::ReadShader(const std::string& filePath)
{
	std::string shaderCode = "";
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try {
		file.open(filePath);
		std::stringstream tmpStream;
		tmpStream << file.rdbuf();
		file.close();
		shaderCode = tmpStream.str();
	}
	catch (std::ifstream::failure error) {
		Debug::Error("Could not read shader: " + filePath, "ShaderHandler.cpp", __LINE__);
		return"";
	}
	return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName)
{
	GLint compileResult = 0;
	GLuint shader = glCreateShader(shaderType);
	const char* shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (!compileResult) {
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::string shaderString(shaderLog.begin(), shaderLog.end());
		Debug::Error("Error compiling shader" + shaderName + ". Error: \n" + shaderString, "ShaderHandler.cpp", __LINE__);
		return 0;
	}
	return shader;
	return GLuint();
}
