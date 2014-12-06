#include "log.h"

#include <iostream>

Log::Log(LogLevel level) :
	__lvl { level },
	__outstream (std::cout)
{

}

Log::Log(std::ostream& stream, LogLevel level) :
	__lvl { level },
	__outstream (stream)
{

}

void Log::debug(const std::string& msg)
{
	if(__lvl >= LogLevel::debug)
		__outstream << "Debug: " << msg << std::endl;
}

void Log::info(const std::string& msg)
{
	if(__lvl >= LogLevel::info)
		__outstream << "Info: " << msg << std::endl;
}

void Log::warning(const std::string& msg)
{
	if(__lvl >= LogLevel::warning)
		__outstream << "Warning: " << msg << std::endl;
}

void Log::error(const std::string& msg)
{
	if(__lvl >= LogLevel::error)
		__outstream << "Error: " << msg << std::endl;
}

void Log::fatal(const std::string& msg)
{
	if(__lvl >= LogLevel::fatal)
		__outstream << "Fatal: " << msg << std::endl;
}
