#include "SMP.h"

/*
 * Reserve space for new members and fan pages to be added.
 */
Facebook::Facebook()
{
	members.reserve(DB_INIT_SIZE);
	fanPages.reserve(DB_INIT_SIZE);
}

/*
 * when calling for default c'tor of each member, the destructed vectors calling for their items'
 * d'tors, which will free the memory of unwanted objects. so the objects will be freed multiple times
 * because they are saved in multiple instances across the project.
 */
/*
 * Free allocated memory of the members and fan pages arrays.
 */
Facebook::~Facebook()
{
    for(auto curr : members)
        delete curr;

    for(auto curr : fanPages)
        delete curr;
}


Facebook& Facebook::operator=(const Facebook& other) noexcept
{
    // Erase the existing members and fan pages.
    members.clear();
    fanPages.clear();

    // Get copies of members and fan pages from the other facebook.
    for (const auto& curr : other.members)
    {
        curr->addRefCounter();
        members.push_back(new Member(*curr));
    }
    for (const auto& curr : other.fanPages)
    {
        curr->addRefCounter();
        fanPages.push_back(new FanPage(*curr));
    }

    return *this;
}


Facebook& Facebook::operator=(Facebook&& other) noexcept
{
    // Erase the existing members and fan pages.
    members.clear();
    fanPages.clear();

    if (this != &other)
    {
        for(int i = 0; i < other.members.size(); i++)
        {
            members.push_back(other.members[i]);
            other.members[i] = nullptr;
        }
        for(int i = 0; i < other.fanPages.size(); i++)
        {
            fanPages.push_back(other.fanPages[i]);
            other.fanPages[i] = nullptr;
        }
    }
    return *this;
}


/*
 * Start the program.
 */
void Facebook::launch()
{
	cout << "Welcome to Facebook!" << endl;
    getDB(); // Get the database from txt file.

    int token = NONE;
	while (token != EXIT)
	{
		try
		{
			cout << endl;
			cout << "Please choose one of the following:" << endl;
			cout << "1 - Create a new member" << endl;
			cout << "2 - Create a new fan-page" << endl;
			cout << "3 - Add a new status" << endl;
			cout << "4 - Print all statuses of a member/fan-page" << endl;
			cout << "5 - Print the feed of a member" << endl;
			cout << "6 - Add friendship between two members" << endl;
			cout << "7 - Remove friendship between two members" << endl;
			cout << "8 - Add a member to a fan-page" << endl;
			cout << "9 - Remove a member from a fan-page" << endl;
			cout << "10 - Print all registered members and fan pages" << endl;
			cout << "11 - Print all friends of a member / all members of a fan-page" << endl;
			cout << "12 - Exit\n" << endl;
			cin >> token;
			doAction(token);
		}
		catch (const MemberException& e)
		{
			cout << e.what() << endl;
		}
		catch (const FanPageException& e)
		{
			cout << e.what() << endl;
		}
		catch (const FacebookException& e)
		{
			cout << e.what() << endl;
		}
		catch (const bad_alloc& e)
		{
			cout << e.what() << endl;
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Program finished... Goodbye!" << endl;
}


/*
 * Calls for the right function in the program.
 */
void Facebook::doAction(int token)
{
	switch (token) {
	case NEW_MEMBER:
		addMember();
		return;
	case NEW_FAN_PAGE:
		addFanPage();
		return;
	case NEW_STATUS:
		addStatus();
		return;
	case PRINT_STATUSES:
        printAllStatuses();
		return;
	case PRINT_FEED:
		printMemberFeed();
		return;
	case NEW_FRIENDSHIP:
		addFriendship();
		return;
	case REMOVE_FRIENDSHIP:
		removeFriendship();
		return;
	case ADD_TO_FAN_PAGE:
		addFanToPage();
		return;
	case REMOVE_FROM_FAN_PAGE:
		removeFanFromPage();
		return;
	case PRINT_ALL:
		printDatabase();
		return;
	case PRINT_ALL_FRIENDS_OR_FANS:
		printFriendsOrFans();
		return;
	case EXIT:
        exitFacebook();
		return;
	default:
		cout << "Invalid input!\n" << endl;
		return;
	}
}


/*
* Adds a new member to the facebook database.
*/
void Facebook::addMember()
{
	Date dob;
	string name;

	cout << "Please enter name of member: " << flush;
	cin.ignore();
	getline(cin, name);
	checkName(name, MEMBER);

	cout << "Please enter year of birth: " << flush;
	cin >> dob.year;

	cout << "Please enter month of birth: " << flush;
	cin >> dob.month;

	cout << "Please enter day of birth: " << flush;
	cin >> dob.day;

	members.push_back(new Member(name, dob));
	cout << "Action Completed Successfully!" << endl;
}

/*
	Adds a new fan page to the facebook database.
*/
void Facebook::addFanPage()
{
	string name;

	cout << "Enter name of FanPage: " << flush;
	cin.ignore();
	getline(cin, name);
	checkName(name, FAN_PAGE);

	fanPages.push_back(new FanPage(name));
	cout << "Action Completed Successfully!" << endl;
}

/*
 Checks if a name is already in use.
 Token 1 to search for a member, Token 2 to search for a fan page.
*/
void Facebook::checkName(const string& name, int token) const
{
	if (token == MEMBER) // Search for member.
	{
		for (Member* curr : members)
			if(curr->getName() == name)
				throw MemberException(NAME_TAKEN);
	}
	else // Search for fan page.
	{
		for (FanPage* curr : fanPages)
			if (curr->getName() == name)
				throw FanPageException(FP_NAME_TAKEN);
	}
}

/*
	Adds a new status to a member / fan page of choice.
*/
void Facebook::addStatus()
{
	int token = EMPTY;
	string name;

    cout << "For a Member/FanPage, please choose 1/2: " << flush;
	cin >> token;

	if (token == MEMBER) // Adds to Member.
	{
		cout << "Enter name of the member: " << flush;
		cin.ignore();
		getline(cin, name);

		for (Member* curr : members)
		{
			if (curr->getName() == name)
			{
				enterStatus(curr);
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		throw MemberException(MEMBER_NOT_FOUND);
	}

	else if (token == FAN_PAGE) // Adds to Fan Page.
	{
		cout << "Enter name of fan-page: " << flush;
		cin.ignore();
		getline(cin, name);

		for (FanPage* curr : fanPages)
		{
			if (curr->getName() == name)
			{
                enterStatus(curr);
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		throw FanPageException(FP_NOT_FOUND);
	}
	throw FacebookException(INVALID_TOKEN);
}


/*
	Print all statuses of a member / fan page of choice.
*/
void Facebook::printAllStatuses() const
{
	int token = NONE;
	string name;
	cout << "For a Member / FanPage, please choose 1 / 2: " << flush;
	cin >> token;

	if (token == MEMBER) // For Member.
	{
		cout << "Enter name of the member: " << flush;
		cin.ignore();
		getline(cin ,name);
		for (Member* curr : members)
		{
			if (curr->getName() == name)
			{
				curr->printStatuses();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		throw MemberException(MEMBER_NOT_FOUND);
	}

	else if (token == FAN_PAGE) // For Fan Page.
	{
		cout << "Enter name of fan-page: " << flush;
		cin.ignore();
		getline(cin , name);
		for (FanPage* curr : fanPages)
		{
			if (curr->getName() == name)
			{
				curr->printStatuses();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		throw FanPageException(FP_NOT_FOUND);
	}
	throw FacebookException(INVALID_TOKEN);
}


/*
	Prints feed of a member of choice.
*/
void Facebook::printMemberFeed() const
{
	string name;
	cout << "Enter name of the member: " << flush;
	cin.ignore();
	getline(cin ,name);

	for (Member* curr : members)
	{
		if (curr->getName() == name)
		{
			curr->printFeed();
			cout << "Action Completed Successfully!" << endl;
			return;
		}
	}
	throw MemberException(MEMBER_NOT_FOUND);
}


/*
	Checks for valid input (names of Members exist in database) if so adds friendship between said members.
*/
void Facebook::addFriendship()
{
	string name1;
	string name2;

	cout << "Enter name of the member #1: " << flush;
	cin.ignore();
	getline(cin, name1);
	cout << "Enter name of the member #2: " << flush;
	getline(cin, name2);

	if (name1 == name2)
		throw MemberException(SAME_MEMBER);

	Member* ptr1 = nullptr, * ptr2 = nullptr;
	for (Member* curr : members)
	{
		if (curr->getName() == name1)
			ptr1 = curr;
		if (curr->getName() == name2)
			ptr2 = curr;
	}

	if (ptr1 == nullptr || ptr2 == nullptr)
		throw MemberException(MEMBER_NOT_FOUND);

	*ptr1 += *ptr2;
	cout << "Action Completed Successfully!" << endl;
}


/*
	Checks for valid input (names of Members exist in database) if so removes the friendship of said members.
*/
void Facebook::removeFriendship()
{
	string name1;
	string name2;

	cout << "Enter name of the member #1: " << flush;
	cin.ignore();
	getline(cin, name1);
	cout << "Enter name of the member #2: " << flush;
	getline(cin, name2);

	if (name1 == name2)
		throw MemberException(SAME_MEMBER);

	Member* ptr1 = nullptr, * ptr2 = nullptr;
	for (Member* curr : members)
	{
		if (curr->getName() == name1)
			ptr1 = curr;
		if (curr->getName() == name2)
			ptr2 = curr;
	}

	if (ptr1 == nullptr || ptr2 == nullptr)
		throw MemberException(MEMBER_NOT_FOUND);


	ptr1->removeMember(ptr2);
	ptr2->removeMember(ptr1);
	cout << "Action Completed Successfully!" << endl;
}


/*
	Checks it input is valid (names of Fan Page and Member exist in database) if so adds the Member to the Fan Page.
*/
void Facebook::addFanToPage()
{	
	string nameFP;
	string nameM;

	Member* ptrM = nullptr;
	FanPage* ptrFP = nullptr;

	cout << "Enter name of the fan page: " << flush;
	cin.ignore();
	getline(cin ,nameFP);
	cout << "Enter name of the member: " << flush;
	getline(cin ,nameM);

	for (FanPage* curr : fanPages)
	{
		if (curr->getName() == nameFP)
		{
			ptrFP = curr;
			break;
		}
	}

	if (ptrFP == nullptr)
		throw FanPageException(FP_NOT_FOUND);

	for (Member* curr : members)
	{
		if (curr->getName() == nameM)
		{
			ptrM = curr;
			break;
		}
	}

	if (ptrM == nullptr)
		throw MemberException(MEMBER_NOT_FOUND);

	*ptrM += *ptrFP;
	cout << "Action Completed Successfully!" << endl;
}


/*
	Checks if input is valid (names of Fan Page and Member) if so removes the Member from the Fan Page. 
*/
void Facebook::removeFanFromPage()
{
	string nameFP;
	string nameM;

	Member* ptrM = nullptr;
	FanPage* ptrFP = nullptr;

	cout << "Enter name of the fan page: " << flush;
	cin.ignore();
	getline(cin, nameFP);
	cout << "Enter name of the member: " << flush;
	getline(cin, nameM);


	for (FanPage* curr : fanPages)
	{
		if (curr->getName() == nameFP)
		{
			ptrFP = curr;
			break;
		}
	}

	if (ptrFP == nullptr)
		throw FanPageException(FP_NOT_FOUND);

	for (Member* curr : members)
	{
		if (curr->getName() == nameM)
		{
			ptrM = curr;
			break;
		}
	}

	if (ptrM == nullptr)
		throw MemberException(MEMBER_NOT_FOUND);

	ptrM->LeaveFanPage(ptrFP);
	cout << "Action Completed Successfully!" << endl;
}


/*
	Prints all Members and Fan Pages that exist at the momnet.
*/
void Facebook::printDatabase() const
{
	int counter = 0;
	cout << "Members:\n" << endl;
	for (Member* curr : members)
	{
		cout << counter + 1 << " - " << curr->getName() << endl;
		counter++;
	}

	counter = 0;
	cout << "\nFan Pages:\n" << endl;
	for (FanPage* curr : fanPages)
	{
		cout << counter + 1 << " - " << curr->getName() << endl;
		counter++;
	}
	cout << "Action Completed Successfully!" << endl;
}


/*
	Checks if input is valid (Member/Fan Page exists) if so, print all friends/fans of member/fan page.
*/
void Facebook::printFriendsOrFans() const
{
	int token = NONE;
	string name;

	cout << "For a Member/FanPage, please choose 1/2: " << flush;
	cin >> token;

	if (token == MEMBER) // Member:
	{
		cout << "Enter name of the member: " << flush;
		cin.ignore();
		getline(cin, name);
		for (Member* curr : members)
		{
			if (curr->getName() == name)
			{
				curr->printMembers();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		throw MemberException(MEMBER_NOT_FOUND);
	}
	else if (token == FAN_PAGE) // Fan Page:
	{
		cout << "Enter name of fan-page: " << flush;
		cin.ignore();
		getline(cin, name);
		for (FanPage* curr : fanPages)
		{
			if (curr->getName() == name)
			{
				curr->printMembers();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		throw FanPageException(FP_NOT_FOUND);
	}
	throw FacebookException(INVALID_TOKEN);
}


/*
 * Close the program:
 * Write all the data to the database file.
 * Free memory of allocated memory for variables and objects.
 */
void Facebook::exitFacebook() const
{
    ofstream outFile(DATABASE_FILE_NAME, ios::trunc);

    for(auto member : members)
        outFile << ADD_MEMBER << " " << *member << flush;

    for(auto fanPage : fanPages)
        outFile << ADD_FAN_PAGE << " " << *fanPage << flush;

    for(int i = 0; i < members.size(); i++)
    {
        for(int j = 0; j < members[i]->getMemberArraySize(); j++)
            outFile << ADD_FRIENDSHIP << " " << i << " " << findIndMembers(members[i]->getMember(j)) << endl;

        for(int j = 0; j < members[i]->getFpArraySize(); j++)
            outFile << ADD_MEMBER_FAN_PAGE << " " << i << " " << findIndFanPages(members[i]->getFP(j)) << endl;

        for(int j = 0; j < members[i]->getStatusArraySize(); j++)
        {
            // We use dynamic cast to avoid slicing the child object (if it is a child object of Status).
            Status* st = members[i]->getStatus(j);
            outStatus(st, outFile, i, ADD_STATUS_MEMBER);
        }
    }

    for(int i = 0; i < fanPages.size(); i++)
        for(int j = 0; j < fanPages[i]->getStatusArraySize(); j++)
        {
            Status* st = fanPages[i]->getStatus(j);
            outStatus(st, outFile, i, ADD_STATUS_FAN_PAGE);
        }

    outFile.close();
}


/*
 * Find the index of a member in the members array.
 */
int Facebook::findIndMembers(const Member& member) const
{
    for(int i = 0; i < members.size(); i++)
        if(members[i] == &member)
            return i;
}


/*
 * Find the index of a fan page in the fan pages array.
 */
int Facebook::findIndFanPages(const FanPage& fp) const
{
    for(int i = 0; i < fanPages.size(); i++)
        if(fanPages[i] == &fp)
            return i;
}


/*
 * Get a status from a file, allocate memory for it and return a pointer to it.
 */
Status* Facebook::getStatus(ifstream& file)
{
    char command;
    string line1, line2;

    file >> command;

    switch(command) // Command checks the type of the status.
    {
        case ADD_TEXT_STATUS:
        {
            file >> command;
            getline(file, line1);
            getline(file, line2);
            return new Status(line2, line1 += "\n");
        }
        case ADD_IMAGE_STATUS:
        {
            file >> command;
            getline(file, line1);
            getline(file, line2);
            return new ImageStatus(line2, line1 += "\n");
        }
        case ADD_VIDEO_STATUS:
        {
            file >> command;
            getline(file, line1);
            getline(file, line2);
            return new VideoStatus(line2, line1 += "\n");
        }
    }
}


/*
	Gets and writes a status to curr.
*/
template <class T>
void Facebook::enterStatus(T& curr)
{
    int type;
    string content;

    cout << "Enter 1 for text, 2 for Image, 3 for Video: " << flush;
    cin >> type;
    cin.ignore();

    switch(type) // Token checks the type of the status to be received.
    {
        case TEXT:
        {
            cout << "Please enter a status: " << flush;
            getline(cin, content);
            Status* st = new Status(content);
            curr->writeStatus(st);
            break;
        }
        case IMAGE:
        {
            cout << "Please enter an image description: " << flush;
            getline(cin, content);
            Status* st = new ImageStatus(content);
            curr->writeStatus(st);
            break;
        }
        case VIDEO:
        {
            cout << "Please enter a video description: " << flush;
            getline(cin, content);
            Status* st = new VideoStatus(content);
            curr->writeStatus(st);
            break;
        }
        default:
            throw FacebookException(INVALID_TOKEN);
    }
}


/*
 * Gets the database from a text file saved under DATABASE_FILE_NAME name.
 * The file must be in the same directory of the program.
 */
void Facebook::getDB()
{
    ifstream inputFile(DATABASE_FILE_NAME);
    if (!inputFile) // if the database file doesn't exist (probably on the first run) - create a hardcoded database.
    {
        InitDB();// Adds requested hardcoded members and fanpages and the links needed.
        return;
    }

    char command;
    string curr, name;
    int ind1,ind2;
    Date dob;

    while(inputFile.peek() != EOF)
    {
        try
        {
            inputFile >> command;
            switch (command) // Command represents the type of function to use.
            {
                case ADD_MEMBER:
                {
                    inputFile >> name;
                    inputFile >> dob.year;
                    inputFile >> dob.month;
                    inputFile >> dob.day;
                    members.push_back(new Member(name, dob));
                    break;
                }
                case ADD_FAN_PAGE:
                {
                    inputFile >> name;
                    fanPages.push_back(new FanPage(name));
                    break;
                }
                case ADD_FRIENDSHIP:
                {
                    inputFile >> ind1;
                    inputFile >> ind2;
                    *members[ind1] += *members[ind2];
                    break;
                }
                case ADD_MEMBER_FAN_PAGE:
                {
                    inputFile >> ind1;
                    inputFile >> ind2;
                    *members[ind1] += *fanPages[ind2];
                    break;
                }
                case ADD_STATUS_MEMBER:
                {
                    inputFile >> ind1;
                    members[ind1]->writeStatus(getStatus(inputFile));
                    break;
                }
                case ADD_STATUS_FAN_PAGE:
                {
                    inputFile >> ind1;
                    fanPages[ind1]->writeStatus(getStatus(inputFile));
                    break;
                }
            }
        }
        catch(const MemberException& exception) // We don't need to handle it because we have duplicate friendships.
        { }
    }
    inputFile.close();
}


/*
 * Write status to out file, also writes if it's a status of member/fan page and the index in the members/fan pages array.
 */
void Facebook::outStatus(Status* st, ofstream& outFile, int ind, char token) const
{
    auto* tmp1 = dynamic_cast<ImageStatus*>(st); // Check if status received is an Image Status.
    auto* tmp2 = dynamic_cast<VideoStatus*>(st); // Check if status received is an Video Status.

    // Write to the out file the correct status format.
    if(tmp1 != nullptr)
        outFile << token << " " << ind << " " << *tmp1 << flush;  // Image Status.
    else if(tmp2 != nullptr)
        outFile << token << " " << ind << " " << *tmp2 << flush;  // Video Status.
    else // (the object wasn't a child of Status)
        outFile << token << " " << ind << " " << *st << flush;    // Text Status.
}


/*
	Hard coded database including members, fan pages, statuses and friendships, use for testing.
*/
void Facebook::InitDB()
{
    Date d;
    d.day = d.month = 1;
    d.year = 2000;

    Status* s11 = new Status("hello im user1");
    Status* s12 = new Status("nice to meet you!");

    Status* s21 = new Status("hello im user2");
    Status* s22 = new Status("whats up?!");

    Status* s31 = new Status("hello im user3");
    Status* s32 = new Status("bros yo");

    Status* s41 = new Status("fp1 fan page");
    Status* s42 = new Status("white rules");

    Status* s51 = new Status("fp2 fan page");
    Status* s52 = new Status("red is the best");

    Status* s61 = new Status("fp3 fan page");
    Status* s62 = new Status("blue supremacy");

    members.push_back(new Member("user1", d));
    members.push_back(new Member("user2", d));
    members.push_back(new Member("user3", d));

    //makes idan and lebo friends
    *members.at(0) += *members.at(1);

    //makes idan and oren friends
    *members.at(0) += *members.at(2);

    fanPages.push_back(new FanPage("fp1"));
    fanPages.push_back(new FanPage("fp2"));
    fanPages.push_back(new FanPage("fp3"));

    //idan joins fp1
    *members.at(0) += *fanPages.at(0);
    //lebo joins fp2
    *members.at(1) += *fanPages.at(1);
    //oren join fp3
    *members.at(2) += *fanPages.at(2);

    //adds statuses to user1
    members.at(0)->writeStatus(s11);
    members.at(0)->writeStatus(s12);

    //adds statuses to user2
    members.at(1)->writeStatus(s21);
    members.at(1)->writeStatus(s22);

    //adds statuses to user3
    members.at(2)->writeStatus(s31);
    members.at(2)->writeStatus(s32);

    //adds statuses to fp1
    fanPages.at(0)->writeStatus(s41);
    fanPages.at(0)->writeStatus(s42);

    //adds statuses to fp2
    fanPages.at(1)->writeStatus(s51);
    fanPages.at(1)->writeStatus(s52);

    //adds statuses to fp3
    fanPages.at(2)->writeStatus(s61);
    fanPages.at(2)->writeStatus(s62);
}
