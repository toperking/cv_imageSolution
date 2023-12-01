// cv_imageProject.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <opencv2/opencv.hpp>

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

    default:
        break;
    }

    return 0;
}

