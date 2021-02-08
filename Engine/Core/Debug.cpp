#include "Debug.h"

Debug::MessageType Debug::currentSev = MessageType::TYPE_NONE;
std::string Debug::outputName = "";

void Debug::OnCreate(const std::string& name)
{
	outputName = name + ".txt";
	std::ofstream out;
	out.open(outputName.c_str(), std::ios::out);
	out.close();
	currentSev = MessageType::TYPE_INFO;
}

void Debug::SetSeverity(MessageType type)
{
	currentSev = type;
}

void Debug::Info(const std::string& message, const std::string& fileName, const int line)
{
	Log(MessageType::TYPE_INFO, "[INFO]:" + message, fileName, line);
}

void Debug::Trace(const std::string& message, const std::string& fileName, const int line)
{
	Log(MessageType::TYPE_TRACE, "[TRACE]:" + message, fileName, line);
}

void Debug::Warning(const std::string& message, const std::string& fileName, const int line)
{
	Log(MessageType::TYPE_WARNING, "[WARNING]:" + message, fileName, line);
}

void Debug::Error(const std::string& message, const std::string& fileName, const int line)
{
	Log(MessageType::TYPE_ERROR, "[ERROR]:" + message, fileName, line);
}

void Debug::FatalError(const std::string& message, const std::string& fileName, const int line)
{
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]:" + message, fileName, line);
}

void Debug::Log(const MessageType type, const std::string& message, const std::string& fileName, const int line)
{
	if (type <= currentSev && currentSev > MessageType::TYPE_NONE) {
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		out << message << "in: " << fileName << " on line: " << line << std::endl;
		out.flush();
		out.close();
	}
}
