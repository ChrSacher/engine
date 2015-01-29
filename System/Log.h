#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <sstream>


/**
 * @brief The LogLevel enum class is for defining which level should be logged in Log \sa Log
 *
 */

enum class LogLevel
{
	debug	= 5,	/** Debuggingoutput */
	info	= 4,	/** Infooutput like timemeasurements */
	warning	= 3,	/** Warnings, for example functions you shouldnt use or maybe unsafe stuff */
	error	= 2,	/** Stuff that is for sure wrong, bad doesn't lead the programm to a shutdown */
	fatal	= 1,	/** Errors, that cause the programm to terminate/don't work correct */
};

/**
 * @brief operator >
 * @param a
 * @param b
 * @return bool
 */
//constexpr bool operator>(LogLevel a, LogLevel b)
//{
//	return static_cast<int>(a) > static_cast<int>(b);
//}

/**
 * @brief operator <
 * @param a
 * @param b
 * @return bool
 */
//constexpr bool operator<(LogLevel a, LogLevel b)
//{
//	return static_cast<int>(a) < static_cast<int>(b);
//}

/**
 * @brief operator >=
 * @param a
 * @param b
 * @return bool
 */
//constexpr bool operator>=(LogLevel a, LogLevel b)
//{
//	return static_cast<int>(a) >= static_cast<int>(b);
//}

/**
 * @brief operator <=
 * @param a
 * @param b
 * @return bool
 */
//bool operator<=(LogLevel a, LogLevel b)
//{
//	return static_cast<int>(a) <= static_cast<int>(b);
//}


/**
 * @brief The Log class is for logging in every programm.
 *
 * For logging there are different logging-levels \sa LogLevel.
 *
 * Each loglevel has different colors, which are a map from stringliterals to colors.
 * \sa OutputColor
 *
 * The default output is standardout(std::cout), you can choose a stream for logging.
 *
 * Inspired by http://stackoverflow.com/a/8337882
 */
class Log
{
public:
	/**
	 * @brief Log defaultconstructor for logging
	 * @param level determines the loglevel \sa LogLevel
	 *
	 * Constructs a object for logging. The Loglevel ist default error and the output is default
	 * std::cout
	 */
	Log(std::ostream& out = std::cout, LogLevel level = LogLevel::debug) : 
		__stream { out },
		__sstream {},
		__lvl{ level },
		__lvl_msg{ "LogLevel" }
	{
	
	}

	~Log() {
		__sstream << "\n";
		__stream << __sstream.rdbuf();
		__stream.flush();
	}

	void setLevel(LogLevel l)
	{
		__globalLvl = l;
	}

	/**
	 * @brief operator<< template overload, will output everything, which overloads operator<< for std::cout for example
	 * @param el the elemnt to log
	 *
	 * Nice way, to dont write everything 10 times :)
	*/
	template<typename T>
	Log& operator<<(T el)
	{
		//if (__lvl <= __globalLvl)
		// until bug is fixed and operator overloading is possible
		if (static_cast<int>(__lvl) <= static_cast<int>(__globalLvl))
			__sstream << "[" << __lvl_msg << "]: " << el; 
		
		return *this;
	}


private:
	std::ostream&		__stream;	/** Outstream for logging */
	std::stringstream	__sstream;	/** stringstream for output, actual data which is written */

	static LogLevel		__globalLvl;/** This member defines, which loglevel is wanted in the application */

protected:
	LogLevel			__lvl;		/** loglevel determines which logmessages are printed */
	std::string			__lvl_msg;	/** determines what should be written in front of each log */
};


class Debug : public Log
{
	Debug() :
		Log()
	{
		__lvl		= LogLevel::debug;
		__lvl_msg	= "DEBUG";
	}
};

class Info : public Log
{
	Info() :
		Log()
	{
		__lvl = LogLevel::info;
		__lvl_msg = "INFO";
	}
};

class Warning : public Log
{
	Warning() :
		Log()
	{
		__lvl = LogLevel::warning;
		__lvl_msg = "WARN";
	}
};

class Error : public Log
{
	Error() :
		Log()
	{
		__lvl = LogLevel::error;
		__lvl_msg = "ERROR";
	}
};

class Fatal : public Log
{
	Fatal() :
		Log()
	{
		__lvl = LogLevel::fatal;
		__lvl_msg = "FATAL";
	}
};


#endif // LOG_H
