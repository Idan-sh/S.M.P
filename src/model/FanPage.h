#ifndef SMP_FAN_PAGE_H
#define SMP_FAN_PAGE_H

#include "src/Includes.h"
#include "src/model/status/Status.h"

class Member;

class FanPage
{
protected:
	string name;

	vector<Member*> memberArray;
	vector<Status*> statusArray;

    int* ref_counter = nullptr;

public:
    FanPage() = default;
	explicit FanPage(const string& _name);
    ~FanPage() = default;

    FanPage(const FanPage& other) { *this = other; ref_counter = other.ref_counter; ++(*ref_counter); };    // copy c'tor
    FanPage(FanPage&& other) noexcept { ref_counter = other.ref_counter; *this = std::move(other); };       // move c'tor
    FanPage& operator=(const FanPage& other);       // copy operator
    FanPage& operator=(FanPage&& other) noexcept;   // move operator

    virtual FanPage& operator+=(Member& member);
	bool operator>(FanPage& other) const;
	bool operator<(FanPage& other) const;

    friend ostream& operator<<(ostream& os, const FanPage& fp);

    void addRefCounter();
    void subtractRefCounter();

    const string& getName() { return name; };
    int getMemberArraySize() { return (int) memberArray.size(); };
    const Member& getMember(int ind) { return *memberArray.at(ind); };

    int getStatusArraySize() { return (int) statusArray.size(); };
    Status* getStatus(int ind) { return statusArray.at(ind); };

    virtual void writeStatus(Status* stat);
	virtual void removeMember(Member* member);
	void printStatuses() const;
	virtual void printMembers() const;
};

#endif // SMP_FAN_PAGE_H
