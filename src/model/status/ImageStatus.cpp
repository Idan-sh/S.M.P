#include "ImageStatus.h"

void ImageStatus::printStatus() const
{
    cout << "On " << timeOfUpload << "a picture of " << content << endl;
    cout << "This Image is in color" << endl;
}

ostream& operator<<(ostream& os, const ImageStatus& st)
{
    os << ADD_IMAGE_STATUS << " " << st.timeOfUpload << st.content << endl;
    return os;
}