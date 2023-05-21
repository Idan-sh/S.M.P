#ifndef SMP_VIDEOSTATUS_H
#define SMP_VIDEOSTATUS_H

#include "Status.h"

class VideoStatus : public Status {

public:
    explicit VideoStatus(const string& c) : Status(c) { ref_counter = new int(1); };
    VideoStatus(const string& c, const string& _timeOfUpload) : Status(c, _timeOfUpload) { ref_counter = new int(1); };
    ~VideoStatus() = default;

    friend ostream& operator<<(ostream& os, const VideoStatus& st);

    void printStatus() const override;
};


#endif // SMP_VIDEOSTATUS_H
