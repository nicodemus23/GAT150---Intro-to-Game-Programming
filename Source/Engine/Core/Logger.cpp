#include "Logger.h"
#include <iostream>
#include "FileIO.h"


namespace kiko
{
	Logger g_logger(LogLevel::Info, &std::cout);
	bool Logger::Log(LogLevel logLevel, const std::string& filename, int line)

	{
		if (logLevel < m_logLevel) return false;

		switch (m_logLevel)

		{
		case kiko::LogLevel::Info:
			*m_ostream << "INFO: ";
			break;
		case kiko::LogLevel::Warning:
			*m_ostream << "WARNING: ";

			break;
		case kiko::LogLevel::Error:
			*m_ostream << "ERROR: ";

			break;
		case kiko::LogLevel::Assert:
			*m_ostream << "ASSERT: ";

			break;
		default:
			break;
		}

		*m_ostream << getFileName(filename) << "(" << line << ")\n"; // *m_ostream dereference 

		return true;
	}
}