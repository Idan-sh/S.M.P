#include "Status.h"

Status::Status(const string& c) : content(c)
{
	// current date and time on the current system
	time_t now = time(nullptr);
	// convert now to string form
	string date_time = ctime(&now);
	timeOfUpload = date_time;

    ref_counter = new int(1);
}


ostream& operator<<(ostream& os, const Status& st)
{
    os << ADD_TEXT_STATUS << " " << st.timeOfUpload << st.content << endl;
    return os;
}


/*
	For cpy c'tor
*/
Status& Status::operator=(const Status& other)
{
	content = other.content;
	timeOfUpload = other.timeOfUpload;
    ref_counter = other.ref_counter;

	return *this;
}

/*
	For move c'tor
*/
Status& Status::operator=(Status&& other) noexcept
{
	if (this != &other)
	{
		content = other.content;
		timeOfUpload = other.timeOfUpload;
        ref_counter = other.ref_counter;
		other.content = EMPTY_STRING;
		other.timeOfUpload = EMPTY_STRING;
        other.ref_counter = nullptr;
	}

	return *this;
}

/*
	Compares between two Statuses' contents
*/
bool Status::operator==(const Status& other)
{
	if (content == other.content)
		return true;
	return false;
}


bool Status::operator!=(const Status& other)
{
	if (content != other.content)
		return true;
	return false;
}


/*
	Print status.
*/
void Status::printStatus() const
{
	cout << "On " << timeOfUpload << content << endl;
    cout << "This status is in black and white." << endl;
}

Status::~Status()
{
}

void Status::subtractRefCounter()
{
    if(!(*--ref_counter))
    {
        delete ref_counter;
        delete this;
    }
};

void Status::addRefCounter()
{
    ++(*ref_counter);
}
