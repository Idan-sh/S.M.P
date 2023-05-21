#include "VideoStatus.h"

void VideoStatus::printStatus() const
{
    cout << "On " << timeOfUpload << "a video of " << content << endl;
    cout << "This video is in color" << endl;
}

ostream& operator<<(ostream& os, const VideoStatus& st)
{
    os << ADD_VIDEO_STATUS << " " << st.timeOfUpload << st.content << endl;
    return os;
}