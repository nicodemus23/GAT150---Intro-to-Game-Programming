#pragma once
#include  <string>
#include  <cassert>
#include  <fstream> // output filestream

// preprocessor macro
#define INFO_LOG { kiko::g_logger.Log(kiko::LogLevel::Info, __FILE__, __LINE__);}
#define WARNING_LOG { kiko::g_logger.Log(kiko::LogLevel::Warning, __FILE__, __LINE__);}
#define ERROR_LOG { kiko::g_logger.Log(kiko::LogLevel::Error, __FILE__, __LINE__);}
#define ASSERT_LOG { kiko::g_logger.Log(kiko::LogLevel::Assert, __FILE__, __LINE__);}

namespace kiko
{
	enum class LogLevel // putting in a class puts in its own space 
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger
	{
	public:
		Logger(LogLevel logLevel, std::ostream* ostream) : // m_ostreamostream)// or can use m_ostream = ostream
			m_logLevel {logLevel},
			m_ostream{ostream} {}

		bool Log(LogLevel logLevel, const std::string& filename, int line);
	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr; // points to cout object 
		std::ofstream m_fstream; // not a pointer. object  

	};

	extern Logger g_logger; // declare logger
}