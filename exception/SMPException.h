#ifndef SMP_SMP_EXCEPTION_H
#define SMP_SMP_EXCEPTION_H
#include "src/Includes.h"

#define INVALID_TOKEN 0

class FacebookException : public exception
{
	string str;

public:
	explicit FacebookException(const int& error);
	char const* what() const noexcept override;
};

#endif // SMP_SMP_EXCEPTION_H