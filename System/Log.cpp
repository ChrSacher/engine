#include "Log.h"
#include <iostream>


Log::Log(LogLevel level) :
	//std::ostream (std::cout),
	__lvl (level),
	__logbuffer (std::cout)
{

}

Log::Log(std::ostream& stream, LogLevel level) :	
	//std::ostream(std::cout),
	__lvl (level),
	__logbuffer (stream)
{

}

void Log::debug(const std::string& msg)
{
	if(__lvl >= LogLevel::debug)
		__logbuffer << "[Debug]: " << msg << std::endl;
}

void Log::info(const std::string& msg)
{
	if(__lvl >= LogLevel::info)
		__logbuffer << "[Info]: " << msg << std::endl;
}

void Log::warning(const std::string& msg)
{
	if(__lvl >= LogLevel::warning)
		__logbuffer << "[Warning]: " << msg << std::endl;
}

void Log::error(const std::string& msg)
{
	if(__lvl >= LogLevel::error)
		__logbuffer << "[Error]: " << msg << std::endl;
}

void Log::fatal(const std::string& msg)
{
	if(__lvl >= LogLevel::fatal)
		__logbuffer << "[Fatal]: " << msg << std::endl;
}

