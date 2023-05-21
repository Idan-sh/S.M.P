#ifndef SMP_FAN_PAGE_EXCEPTION_H
#define SMP_FAN_PAGE_EXCEPTION_H
#include "src/Includes.h"

enum FAN_PAGE_ERROR_CODE {FP_NOT_FOUND, FP_NAME_TAKEN};

class FanPageException : public exception
{
	string str;

public:
	explicit FanPageException(const int& error);
	char const* what() const noexcept override;
};

#endif // SMP_FAN_PAGE_EXCEPTION_H