
#include "p203_commonUtil.h"

bool p203_commonUtil::bgrToGray(const Mat & bgrImage, Mat & grayImage)
{
    int height = 0, width = 0;

    if ((bgrImage.empty()) || (bgrImage.channels() != 3) || (bgrImage.depth() != CV_8U))
    {
        return false;
    }

    if ((grayImage.empty()) || (grayImage.channels() != 1) || (grayImage.depth() != CV_8U))
    {
        return false;
    }

    if ((bgrImage.rows != grayImage.rows) || (bgrImage.cols != grayImage.cols))
    {
        return false;
    }

    for (height = 0; height != grayImage.rows; ++height)
    {
        for (width = 0; width != grayImage.cols; ++width)
        {
            double current_b = static_cast<double>(bgrImage.at<Vec<uint8_t, 3>>(height, width)[0]);
            double current_g = static_cast<double>(bgrImage.at<Vec<uint8_t, 3>>(height, width)[1]);
            double current_r = static_cast<double>(bgrImage.at<Vec<uint8_t, 3>>(height, width)[2]);
            double grayScale = 0.299 * current_r + 0.587 * current_g + 0.114 * current_b;
            grayImage.at<uint8_t>(height, width) = static_cast<uint8_t>(floor(grayScale));
        }
    }

    return true;
}