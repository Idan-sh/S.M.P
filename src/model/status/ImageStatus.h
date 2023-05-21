#ifndef SMP_IMAGESTATUS_H
#define SMP_IMAGESTATUS_H

#include "Status.h"
#include "src/Includes.h"

class ImageStatus : public Status {

public:
    explicit ImageStatus(const string& c) : Status(c) { ref_counter = new int(1); };
    ImageStatus(const string& c, const string& _timeOfUpload) : Status(c, _timeOfUpload) { ref_counter = new int(1); };
    ~ImageStatus() override = default;

    friend ostream& operator<<(ostream& os, const ImageStatus& st);

    void printStatus() const override;
};


#endif // SMP_IMAGESTATUS_H
