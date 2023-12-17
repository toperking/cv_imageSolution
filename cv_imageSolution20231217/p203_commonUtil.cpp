
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

bool p203_commonUtil::mergeImage(const Mat& image1, const Mat& image2, Mat& emptyImage) {

    if (image1.empty() || image2.empty() || !emptyImage.empty()) { return false; }
    if (image1.channels() != 3 || image2.channels() != 3 || (image1.channels() !=  image2.channels())) { return false; }

    int size_image1 = image1.rows + image1.cols;
    int size_image2 = image2.rows + image2.cols;
    Mat tempImage;
    if (size_image1 >= size_image2) 
    {
        cout << "test1" << endl;
        emptyImage = Mat::zeros(image2.rows, image2.cols, CV_8UC3);
        resize(image1, tempImage, Size(image2.cols, image2.rows), 0, 0, INTER_LINEAR);
        addWeighted(tempImage, 1, image2, 1, 0, emptyImage);
    }else
    {
        emptyImage = Mat::zeros(image1.rows, image1.cols, CV_8UC3);
        resize(image2, tempImage, Size(image1.rows, image1.cols), 0, 0, INTER_LINEAR);
        addWeighted(image1, 1, tempImage, 1, 0, emptyImage);
    }

    return true;
}