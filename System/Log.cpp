#include "System/Log.h"
#include <iostream>


Log::Log(LogLevel level) :
	std::ostream (std::cout),
	__lvl (level),
	__logbuffer (std::cout)
{

}

Log::Log(std::ostream& stream, LogLevel level) :	
	std::ostream(std::cout),
	__lvl (level),
	__logbuffer (stream)
{

}

void Log::debug(const std::string& msg)
{
	if(__lvl >= LogLevel::debug)
		*this << "Debug: " << msg << std::endl;
}

void Log::info(const std::string& msg)
{
	if(__lvl >= LogLevel::info)
		*this << "Info: " << msg << std::endl;
}

void Log::warning(const std::string& msg)
{
	if(__lvl >= LogLevel::warning)
		*this << "Warning: " << msg << std::endl;
}

void Log::error(const std::string& msg)
{
	if(__lvl >= LogLevel::error)
		*this << "Error: " << msg << std::endl;
}

void Log::fatal(const std::string& msg)
{
	if(__lvl >= LogLevel::fatal)
		*this << "Fatal: " << msg << std::endl;
}

