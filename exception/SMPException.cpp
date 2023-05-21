#include "SMPException.h"

FacebookException::FacebookException(const int& error)
{
	if (error == INVALID_TOKEN)
		str = "Invalid Input!";
}

char const* FacebookException::what() const noexcept
{
	return str.c_str();
}
