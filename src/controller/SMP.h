#ifndef SMP_SMP_H
#define SMP_SMP_H

#include "src/Includes.h"
#include "src/model/Member.h"
#include "src/model/status/Status.h"
#include "src/model/FanPage.h"
#include "exception/MemberException.h"
#include "exception/FanPageException.h"
#include "exception/SMPException.h"
#include "src/model/status/ImageStatus.h"
#include "src/model/status/VideoStatus.h"

enum token{ EMPTY, MEMBER , FAN_PAGE };
enum menu{ NONE , NEW_MEMBER , NEW_FAN_PAGE , NEW_STATUS, PRINT_STATUSES , PRINT_FEED , NEW_FRIENDSHIP ,
	REMOVE_FRIENDSHIP , ADD_TO_FAN_PAGE , REMOVE_FROM_FAN_PAGE, PRINT_ALL , PRINT_ALL_FRIENDS_OR_FANS, EXIT};
enum status_token{ TEXT = 1, IMAGE, VIDEO };

#define DATABASE_FILE_NAME "DataBase.txt"

// Tokens for file commands.
#define ADD_MEMBER 'm'
#define ADD_FAN_PAGE 'f'
#define ADD_FRIENDSHIP 'a'
#define ADD_MEMBER_FAN_PAGE 'b'
#define ADD_STATUS_MEMBER 'c'
#define ADD_STATUS_FAN_PAGE 'd'
// -------------------------

class Facebook
{
	vector<Member*> members;
	vector<FanPage*> fanPages;

private:
    template <class T> void enterStatus(T& curr);
    int findIndMembers(const Member& member) const;
    int findIndFanPages(const FanPage& fp) const;
    void getDB();
    Status* getStatus(ifstream& file);
    void doAction(int token);
    void checkName(const string& name, int token) const;
    void outStatus(Status* st, ofstream& outFile, int ind, char token) const;
    void exitFacebook() const;

public:
	Facebook();
    ~Facebook();

    Facebook(const Facebook& other) { *this = other; };                 // cpy c'tor.
    Facebook(Facebook&& other) noexcept { *this = std::move(other); }; // move c'tor.
    Facebook& operator=(const Facebook& other) noexcept;                // cpy operator.
    Facebook& operator=(Facebook&& other) noexcept;                     // move operator.

	void launch();
    void InitDB();

	void addMember();
	void addFanPage();
	void addStatus();

	void addFriendship();
    void addFanToPage();

    void removeFriendship();
	void removeFanFromPage();

    void printAllStatuses() const;
    void printMemberFeed() const;
    void printDatabase() const;
    void printFriendsOrFans() const;
};

#endif // SMP_SMP_H