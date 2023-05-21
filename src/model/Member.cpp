#include "Member.h"
#include "exception/MemberException.h"

/*
 * Reserve space for new fan pages, statuses and feed statuses to be added.
 */
Member::Member(const string& _name, const Date& _dateOfBirth) : FanPage(_name), dateOfBirth(_dateOfBirth)
{
	if (checkDateOfBirth(_dateOfBirth))
		throw MemberException(INVALID_DATE_OF_BIRTH);

	fpArray.reserve(DB_INIT_SIZE);
	feedArray.reserve(FEED_SIZE);
	memberNamesOfStatuses.reserve(FEED_SIZE);
    memberArray.reserve(DB_INIT_SIZE);
    statusArray.reserve(DB_INIT_SIZE);

    ref_counter = new int(1);
}


Member& Member::operator=(const Member& other)
{
    FanPage::operator=(other);
    dateOfBirth = other.dateOfBirth;

    for (const auto& curr : other.fpArray)
        fpArray.push_back(curr);
    for (const auto& curr : other.feedArray)
        feedArray.push_back(curr);
    for (const auto& curr : other.memberNamesOfStatuses)
        memberNamesOfStatuses.push_back(curr);
    return *this;
}


Member& Member::operator=(Member&& other) noexcept
{
    if (this != &other)
    {
        FanPage::operator=(other);
        dateOfBirth = other.dateOfBirth;

        for(int i = 0; i < other.fpArray.size(); i++)
        {
            fpArray.push_back(other.fpArray.at(i));
            other.fpArray.at(i) = nullptr;
        }
        for(int i = 0; i < other.feedArray.size(); i++)
        {
            feedArray.push_back(other.feedArray.at(i));
            other.feedArray.at(i) = nullptr;
        }
        for(int i = 0; i < other.memberNamesOfStatuses.size(); i++)
        {
            memberNamesOfStatuses.push_back(other.memberNamesOfStatuses.at(i));
            other.memberNamesOfStatuses.at(i) = nullptr;
        }
    }
    return *this;
}


ostream &operator<<(ostream &os, const Member &m)
{
    os << m.name << " " << m.dateOfBirth.year << " " << m.dateOfBirth.month << " " << m.dateOfBirth.day << endl;
    return os;
}


/*
	Adds friendship between members (in-case they aren't already friends)
*/
Member& Member::operator+=(Member& other)
{
	for (Member* curr : memberArray)
	{
		if (curr == &other)
			throw MemberException(ALREADY_FRIENDS);
	}

	memberArray.push_back(&other);
	other.memberArray.push_back(this);
    addRefCounter();
    other.addRefCounter();

	return *this;
}

/*
	Adds member to a fan page of choice (in-case he isn't a fan already)
*/
Member& Member::operator+=(FanPage& fp)
{	
	for (FanPage* curr : fpArray)
	{
		if (curr == &fp)
			throw MemberException(ALREADY_FAN);
	}

	fpArray.push_back(&fp);
	fp += *this;
    addRefCounter();
    fp.addRefCounter();
    return *this;
}

/*
	Removes friendship between two members (in-case they are friends)
*/
void Member::removeMember(Member* member)
{
	int counter = 0;
	for (Member* curr : memberArray)
	{
		if (curr == member)
		{
			removeFriendFromFeed(member->getName());
			memberArray.erase(memberArray.begin() + counter);
            subtractRefCounter();
			return;
		}
		counter++;
	}
	throw MemberException(NOT_FRIENDS);
}

/*
	Updates the member's feed and removes the statuses of the member in which is not a friend anymore
*/
void Member::removeFriendFromFeed(const string& _name)
{
	for (int i = 0; i < memberNamesOfStatuses.size(); i++)
	{
		if (memberNamesOfStatuses.at(i) == _name)
		{
			memberNamesOfStatuses.erase(memberNamesOfStatuses.begin() + i);
			feedArray.erase(feedArray.begin() + i);
			i--;
		}
	}
}

/*
	Removes a member as a fan from a fan page of choice (in-case he is a fan)
*/
void Member::LeaveFanPage(FanPage* fp)
{
	int counter = 0;
	for (FanPage* curr : fpArray)
	{
		if (curr == fp)
		{
			fpArray.erase(fpArray.begin() + counter);
			fp->removeMember(this);
            fp->subtractRefCounter();
            subtractRefCounter();
			return;
		}
		counter++;
	}
	throw MemberException(NOT_FAN);
}


/*
	Adds the new status to the statuses array.
*/
void Member::writeStatus(Status* stat)
{
    stat->addRefCounter();
	statusArray.push_back(stat);
    addToFeed(stat, name);
}


/*
	Adds a new status to the feeds of all friends.
*/
void Member::addToFeed(Status* stat, string& username)
{
	bool isEmpty;
	int size;
	for (Member* currFriend : memberArray)
	{
		size = (int) currFriend->feedArray.size();
		isEmpty = currFriend->feedArray.empty();

		if (!isEmpty && size < FEED_SIZE)
		{
			currFriend->feedArray.push_back(currFriend->feedArray[size - 1]);
			currFriend->memberNamesOfStatuses.push_back(currFriend->memberNamesOfStatuses[size - 1]);
		}

		for (int i = size - 1; i > 0; i--)
		{
			currFriend->feedArray[i] = currFriend->feedArray[i - 1];
			currFriend->memberNamesOfStatuses[i] = currFriend->memberNamesOfStatuses[i - 1];
		}

        stat->addRefCounter();
		if (isEmpty)
		{
			currFriend->feedArray.push_back(stat);
			currFriend->memberNamesOfStatuses.push_back(username);
		}
		else
		{
			currFriend->feedArray[0] = stat;
			currFriend->memberNamesOfStatuses[0] = username;
		}
	}
}

/*
	Prints the feed of this member.
*/
void Member::printFeed() const
{
	cout << name << "'s Feed:" << endl;
	for (int i = 0; i < (int) feedArray.size(); i++)
	{
		cout << i+1 << " - By " << memberNamesOfStatuses.at(i) << " " << flush;
		feedArray.at(i)->printStatus();
	}
}


/*
	Prints the friends list of this member.
*/
void Member::printMembers() const
{
	int counter = 0;
	cout << name << "'s Friends:" << endl;
	for (Member* curr : memberArray)
	{
		cout << counter + 1 << " - " << flush;
		cout << curr->getName() << endl;
		counter++;
	}
}

/*
	Print all the fan pages the member is a fan of
*/
void Member::printFanPages() const
{
	int counter = 0;
    cout << "Member " << name << "'s Fan Pages Are: " << flush;
    for(FanPage* curr : fpArray)
    {
		cout << counter + 1 << " - " << flush;
        cout << curr->getName() << endl;
		counter++;
    }
}

bool Member::checkDateOfBirth(Date dob) const
{
    return (dob.year < 1900 || dob.year > 2022 || dob.month < 1
            || dob.month > 12 || dob.day < 1 || dob.day > 31);
}
