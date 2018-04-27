#ifndef LOG_H
#define LOG_H

#include <iostream>

namespace LavaEngine { namespace Utils {

	class Log
	{
	public:
		enum Level
		{
			LEVEL_ERROR,
			LEVEL_WARNING,
			LEVEL_INFO
		};

	private:
		static Level m_logLevel;

	public:
		static inline void setLevel(Level level)
		{
#ifndef NDEBUG
		m_logLevel = level;
#endif
		}

		static inline void error(const char* message)
		{
#ifndef NDEBUG
		if(m_logLevel >= LEVEL_ERROR)
			std::cout << "[Error]: " << message << std::endl;
#endif
		}

		static inline void warn(const char* message)
		{
#ifndef NDEBUG
		if(m_logLevel >= LEVEL_WARNING)
			std::cout << "[Warning]: " << message << std::endl;
#endif
		}

		static inline void info(const char* message)
		{
#ifndef NDEBUG
		if(m_logLevel >= LEVEL_INFO)
			std::cout << "[Info]: " << message << std::endl;
#endif
		}
	};
}}

#endif
