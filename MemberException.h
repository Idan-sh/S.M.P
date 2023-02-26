#ifndef SMP_MEMBER_EXCEPTION_H
#define SMP_MEMBER_EXCEPTION_H
#include "Includes.h"

enum MEMBER_ERROR_CODE{INVALID_DATE_OF_BIRTH ,ALREADY_FRIENDS, ALREADY_FAN, NOT_FRIENDS, NOT_FAN,
	NAME_TAKEN, MEMBER_NOT_FOUND, SAME_MEMBER};

class MemberException : public exception
{
	string str;

public:
	explicit MemberException(const int& error);
	char const* what() const noexcept override;
};

#endif // SMP_MEMBER_EXCEPTION_H