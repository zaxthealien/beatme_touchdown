#ifndef BTM_TD_EXCEPTIONS_H
#define BTM_TD_EXCEPTIONS_H

#include <exception>

namespace btm_td{

	namespace helper{

		namespace db{

			struct InvalidDBException : public std::exception
			{
				char * _what;
				InvalidDBException(char * __what = "Tried to open an invalid database."){
					this->_what = __what;
				}
				const char * what()
				{
					return this->_what;
				}
			};

		}

	}

	namespace music_vars {

	}

	struct BaseClassException : public std::exception
	{
		char * _what;
		BaseClassException(char * __what = "Cannot call a function from an abstract class, please derive the class and implement it first."){
			this->_what = __what;
		}
		const char * what()
		{
			return this->_what;
		}
	};

	struct NullPointerException : public std::exception
	{
		char * _what;
		NullPointerException(char * __what = ""){
			this->_what = __what;
		}
		const char * what()
		{
			return this->_what;
		}
	};

	struct InvalidArgumentsException : public std::exception
	{
		char * _what;
		InvalidArgumentsException(char * __what = "Tried to call function with invalid arguments."){
			this->_what = __what;
		}
		const char * what()
		{
			return this->_what;
		}
	};

}

#endif