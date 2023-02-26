#ifndef SMP_STATUS_H
#define SMP_STATUS_H
#include "Includes.h"

class Status {
protected:
	string content;
	string timeOfUpload;

    int* ref_counter;

public:
	explicit Status(const string& c);
    Status(const string& c, const string& _timeOfUpload) : content(c), timeOfUpload(_timeOfUpload) { ref_counter = new int(1); };
    virtual ~Status();

    Status(const Status& other) { *this = other; };                 // cpy c'tor
	Status(Status&& other) noexcept { *this = std::move(other); };  // move c'tor
	Status& operator=(const Status& other);                         // cpy operator
	Status& operator=(Status&& other) noexcept;                     // move operator

	bool operator==(const Status& other);
	bool operator!=(const Status& other);

    friend ostream& operator<<(ostream& os, const Status& st);

    void addRefCounter();
    void subtractRefCounter();

    virtual void printStatus() const;
};

#endif // SMP_STATUS_H