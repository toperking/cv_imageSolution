// cv_imageProject.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "p201_commonUtil.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    unsigned int index = 0;
    cout << "The version of openCV detected:\t" << CV_VERSION << endl;
    cout << "Please assignn the index of test case:\t";
    cin >> index;

    cout << "The selected test case index = " << index << endl;

    switch (index)
    {
    case 0:
    {
        string testImagePath("");
        Mat testImage;
        cout << "Please assign the test image to be shown:\t";
        cin >> testImagePath;
        cout << "The selected test imagePath = " << testImagePath << endl;

        try
        {
            testImage = imread(testImagePath);
            imshow("Selected file image", testImage);
            waitKey(0);
            destroyAllWindows();
        }
        catch (exception e)
        {
            cerr << "Exception get:\t" << e.what() << endl;
        }

        break;
    }
    case 1:
    {
        string testDir("");
        cout << "Please assign the path:\t";
        cin >> testDir;
        bool ret = false;
        vector<string> fileList = vector<string>();
        ret = p201_commonUtil::getFileList(testDir, fileList);
        if (ret) {
            vector<string>::const_iterator it;
            for (it = fileList.begin(); it != fileList.end(); ++it) {
                cout << *it << endl;
            }
            cout << "Done. Totally:" << fileList.size() << " file FOUND." << endl;
        }
        break;
    }
    case 2:
    {
        int i = 0;
        Vec<uint8_t, 7> lotteVector = Vec<uint8_t,7>::zeros();
        p201_commonUtil::lotteNumberGenerator(lotteVector);
        cout << "the selected random number:\t";
        for (i = 0; i != lotteVector.channels; i++) {
            cout << static_cast<uint32_t>(lotteVector[i]) << "\t";
        }
        cout << endl;
        break;
    }
    case 3:
    {
        bool resualt = false;
        int i = 0;
        int j = 0;
        int rows = 0;
        int cols = 0;
        Mat radomImage;
        cout << "Please assign the row size for random image:\t";
        cin >> rows;
        cout << "Please assgin the colum size for random image:\t";
        cin >> cols;
        radomImage = Mat(rows, cols, CV_64FC1);
        resualt = p201_commonUtil::generateRandomMatrix2D(radomImage);
        if (!resualt) {
            cerr << "The matrix can only be the 2D Array with CV_64_F." << endl;
        }
        else {
            cout << "The randonly generated matrix:" << endl;
            for (i = 0; i != radomImage.rows; ++i) {
                for (j = 0; j != radomImage.cols; ++j) {
                    cout << static_cast<uint16_t>(radomImage.at<double>(i, j)) << "\t";
                }
                cout << endl;
            }
            cout << "The  generated of identity  matrix:" << endl;
            Mat unitMatrix = radomImage * radomImage.inv();
            for (i = 0; i != unitMatrix.rows; ++i) {
                for (j = 0; j != unitMatrix.cols; ++j) {
                    cout << static_cast<uint16_t>(round(unitMatrix.at<double>(i,j))) << "\t";
                }
                cout << endl;
            }
        }
        break;
    }
    default:
        break;
    }

    return 0;
}

