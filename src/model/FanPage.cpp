#include "src/model/Member.h"
#include "FanPage.h"

/*
 * Reserve space for new members and statuses to be added.
 */
FanPage::FanPage(const string& _name) : name(_name)
{
    memberArray.reserve(DB_INIT_SIZE);
	statusArray.reserve(DB_INIT_SIZE);

    ref_counter = new int(1);
}

FanPage& FanPage::operator=(const FanPage& other)
{
    if (this != &other)
    {
        for (const auto &curr: memberArray) // Removes existing members.
            curr->subtractRefCounter();
        memberArray.clear();
        for (const auto &curr: statusArray) // Removes existing statuses.
            curr->subtractRefCounter();
        statusArray.clear();

        ref_counter = other.ref_counter;

        for (const auto &curr: other.memberArray)   // Get members from the other.
            memberArray.push_back(curr);
        for (const auto &curr: other.statusArray)   // Get statuses from the other.
            statusArray.push_back(curr);
    }
    return *this;
}


FanPage& FanPage::operator=(FanPage&& other) noexcept
{
    if (this != &other)
    {
        for (const auto &curr: memberArray) // Removes existing members.
            curr->subtractRefCounter();
        memberArray.clear();
        for (const auto &curr: statusArray) // Removes existing statuses.
            curr->subtractRefCounter();
        statusArray.clear();

        ref_counter = other.ref_counter;
        other.ref_counter = nullptr;

        for (int i = 0; i < other.memberArray.size(); i++)  // Get members from the other.
        {
            memberArray.push_back(other.memberArray.at(i));
            other.memberArray.at(i) = nullptr;
        }
        for (int i = 0; i < other.statusArray.size(); i++)  // Get statuses from the other.
        {
            statusArray.push_back(other.statusArray.at(i));
            other.statusArray.at(i) = nullptr;
        }
    }
    return *this;
}


ostream &operator<<(ostream &os, const FanPage &fp)
{
    os << fp.name << endl;
    return os;
}


/*
	Adds a given Status to the Status array of the Fan Page.
*/
void FanPage::writeStatus(Status* stat)
{
    stat->addRefCounter();
    statusArray.push_back(stat);
}


/*
	Adds the member on Fan Page fans array.
*/
FanPage& FanPage::operator+=(Member& member)
{
    memberArray.push_back(&member);
    (*member.ref_counter)++;
	return *this;
}


bool FanPage::operator>(FanPage& other) const
{
	if (memberArray.size() > other.memberArray.size())
		return true;
	return false;
}


bool FanPage::operator<(FanPage& other) const
{
	if (memberArray.size() < other.memberArray.size())
		return true;
	return false;
}


/*
	Removes the member from the members array.
*/
void FanPage::removeMember(Member* member)
{
	int counter = 0;
	for (Member* curr : memberArray)
	{
		if (curr == member)
		{
            memberArray.erase(memberArray.begin() + counter);
            (*member->ref_counter)--;
            break;
		}
		counter++;
	}
}


/*
	Print all statuses of this Fan Page.
*/
void FanPage::printStatuses() const
{	
	int counter = 0;
	cout << name << "'s Statuses:" << endl;
	for (Status* curr : statusArray)
	{
		cout << counter + 1 << " - " << flush;
		curr->printStatus();
		counter++;
	}
}


/*
	Print all the fans of this fan page.
*/
void FanPage::printMembers() const
{
	int counter = 0;
	cout << name << "'s Fans:" << endl;
	for (Member* curr : memberArray)
	{
		cout << counter + 1 << " - " << flush;
		cout << curr->getName() << endl;
		counter++;
	}
}

void FanPage::subtractRefCounter()
{
    if(--(*ref_counter) == 0)
    {
        delete ref_counter;
        delete this;
    }
}

void FanPage::addRefCounter()
{
    ++(*ref_counter);
}
