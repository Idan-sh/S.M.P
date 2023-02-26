#ifndef SMP_MEMBER_H
#define SMP_MEMBER_H

#include "FanPage.h"

class Member : public FanPage{
	Date dateOfBirth;

	vector<FanPage*> fpArray;

	vector<Status*> feedArray;
	vector<string> username_of_status;

private:
	void addToFeed(Status* stat, string& username);
    void removeFriendFromFeed(const string& _name);
    bool checkDateOfBirth(Date dob) const;

public:
    Member() = default;
	Member(const string& _name, const Date& _dateOfBirth);
    ~Member() = default;

    Member(const Member& other){ *this = other; };          // cpy c'tor
    Member(Member&& other) noexcept { *this = std::move(other); };    // move c'tor
    Member& operator=(const Member& other);                 // cpy operator
    Member& operator=(Member&& other) noexcept;                      // move operator

	Member& operator+=(Member& other) override;
	Member& operator+=(FanPage& fp);

    friend ostream& operator<<(ostream& os, const Member& m);

    int getFpArraySize() { return (int) fpArray.size(); };
    const FanPage& getFP(int ind) { return *fpArray.at(ind); };

	void removeMember(Member* member) override;
	void LeaveFanPage(FanPage* fp);
	void writeStatus(Status* stat) override;

	void printFeed() const;
	void printMembers() const override;
    void printFanPages() const;

};

#endif // SMP_MEMBER_H