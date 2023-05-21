#include "MemberException.h"

MemberException::MemberException(const int& error)
{
	switch (error)
	{
	case INVALID_DATE_OF_BIRTH:
		cout << "Date of birth invalid!" << endl;
		break;
	case ALREADY_FRIENDS:
		str = "Members are already friends!";
		break;
	case ALREADY_FAN:
		str = "This member is already a fan of this page!";
		break;
	case NOT_FRIENDS:
		str = "Given Member is not a friend of this Member!";
		break;
	case NOT_FAN:
		str = "This member is not a fan of this page!";
		break;
	case NAME_TAKEN:
		str = "Name of Member already in use!";
		break;
	case MEMBER_NOT_FOUND:
		str = "Member not found!";
		break;
	case SAME_MEMBER:
		str = "Member1 and Member2 are the same!";
		break;
    default:
        str = "Unknown member exception!";
    }
}

char const* MemberException::what() const noexcept
{
	return str.c_str();
}