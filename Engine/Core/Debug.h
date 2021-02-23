#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>

class Debug
{
	enum class MessageType : unsigned short {
		TYPE_NONE = 1,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO

	};

public:
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator =(const Debug&) = delete;
	Debug& operator =(Debug&&) = delete;

	static void OnCreate(const std::string& name = "Game258EngineLog");
	static void SetSeverity(MessageType type);
	static void Info(const std::string& message, const std::string& fileName, const int line);
	static void Trace(const std::string& message, const std::string& fileName, const int line);
	static void Warning(const std::string& message, const std::string& fileName, const int line);
	static void Error(const std::string& message, const std::string& fileName, const int line);
	static void FatalError(const std::string& message, const std::string& fileName, const int line);

private:
	static void Log(const MessageType type, const std::string& message, const std::string& fileName, const int line);
	static MessageType currentSev;
	static std::string outputName;
};
#endif
