// cv_imageSolution20231224.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "p201_commonUtil.h"
#include "p203_commonUtil.h"
#include "p204_commonUtil.h"

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
        Vec<uint8_t, 7> lotteVector = Vec<uint8_t, 7>::zeros();
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
                    cout << static_cast<uint16_t>(round(unitMatrix.at<double>(i, j))) << "\t";
                }
                cout << endl;
            }
        }
        break;
    }
    case 4:
    {
        bool result = false;
        int i = 0;
        int j = 0;
        int k = 0;
        int rows = 0;
        int cols = 0;
        Mat randomImage, scaledImage;
        cout << "Please assign the row size for random image:\t";
        cin >> rows;
        cout << "Please assign the column size for random image:\t";
        cin >> cols;

        randomImage = Mat(rows, cols, CV_64FC3);
        result = p201_commonUtil::generateRandomMatrix3D(randomImage);

        if (!result)
        {
            cerr << "The matrix can only be the 3D array with depth = 3. Now domension size = " << randomImage.channels() << endl;
        }
        else
        {
            randomImage.convertTo(scaledImage, CV_8U, 0.5, 1);

            for (i = 0; i != randomImage.rows; ++i)
            {
                for (j = 0; j != randomImage.cols; ++j)
                {
                    cout << "{";
                    for (k = 0; k != randomImage.channels(); ++k)
                    {
                        cout << randomImage.at< Vec<double, 3> >(i, j)[k] << " -> ";
                        cout << static_cast<uint16_t>(scaledImage.at< Vec<uint8_t, 3> >(i, j)[k]) << ", ";
                    }
                    cout << "}\t";
                }
                cout << endl;
            }
        }
        break;
    }
    case 5:
    {
        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                int key;
                cout << "The Info of image:\theight = " << image_buffer.rows;
                cout << ", width = " << image_buffer.cols;
                cout << ", depth = " << image_buffer.channels();
                cout << ", dataType = " << image_buffer.depth() << "." << endl;
                imshow("Sample image", image_buffer);

                key = waitKey(0);
                if (key == 27)
                {
                    destroyAllWindows();
                }
            }
        }
        break;
    }
    case 6:
    {
        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                string targetPath;
                cout << "Please assign the dir/path storing the cropped images, ended with \"\\\":\t";
                cin >> targetPath;

                int seg_line = static_cast<int>(image_buffer.cols / 2);
                time_t nowTime = time(nullptr);
                Mat image_buffer_left = image_buffer.colRange(0, seg_line);
                Mat image_buffer_right = image_buffer.colRange(seg_line, image_buffer.cols);

                string fileName_left = string(targetPath) + string("image_") + to_string(nowTime) + string("_left.jpg");
                string fileName_right = string(targetPath) + string("image_") + to_string(nowTime) + string("_right.jpg");

                vector<int> jpeg_compression_options;
                jpeg_compression_options.push_back(IMWRITE_JPEG_QUALITY);
                jpeg_compression_options.push_back(90);
                jpeg_compression_options.push_back(IMWRITE_JPEG_OPTIMIZE);
                jpeg_compression_options.push_back(1);

                imwrite(fileName_left, image_buffer_left, jpeg_compression_options);
                imwrite(fileName_right, image_buffer_right, jpeg_compression_options);

                cout << "Image cropping done to " << fileName_left << " and " << fileName_right << "." << endl;
            }
        }

        break;
    }
    case 7:
    {
        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                uint8_t range;
                vector<Mat> channels;
                vector<Mat> fixed_channels;
                Mat image_buffer_updated;
                cout << "The ratio of blue-ray decreased (0 ~ 100):\t";
                cin >> range;
                range = 100 - (range % 100);

                split(image_buffer, channels);

                imshow("Original image", image_buffer);
                imshow("Blue-ray channel image", channels[0]);
                imshow("Green-ray channel image", channels[1]);
                imshow("Red-ray channel image", channels[2]);

                MatIterator_<uint8_t> it = channels[0].begin<uint8_t>();

                for (it = channels[0].begin<uint8_t>(); it != channels[0].end<uint8_t>(); ++it)
                {
                    *it = static_cast<uint8_t>(static_cast<double>(*it) * static_cast<double>(range) / 100.0);
                }

                fixed_channels.push_back(channels[0]);
                fixed_channels.push_back(channels[1]);
                fixed_channels.push_back(channels[2]);

                merge(fixed_channels, image_buffer_updated);

                imshow("Blue-ray reduced image", image_buffer_updated);

                waitKey(0);
                destroyAllWindows();
            }
        }
        break;
    }

    case 8:
    {
        int key, height = 0, width = 0;
        int total_sections = 17;
        cout << "Please assgin the width of test image:\t";
        cin >> width;
        if (width % total_sections != 0) {
            cerr << "The width of test image MUST BR the multiple of " << total_sections << endl;
            return 0;
        }
        cout << "Please assgin the Hight of Test image:\t";
        cin >> height;
        uint8_t current_b = 0, current_g = 255;
        Mat yellow_array = Mat(height, width, CV_8UC3, Scalar(current_b, current_g, 255));
        imshow("Blank Yellow", yellow_array);
        key = waitKey(0);
        if (key == 27) {
            destroyAllWindows();
            return 0;
        }
        {
            int column_section = 1;
            int delta = 16;
            bool lastTime = false;
            destroyAllWindows();
            while ((current_b < 255) && (current_g > 0))
            {
                int row_index = 0, column_index = 0;
                if (lastTime) break;
                if (current_b > 255 - delta) {
                    current_b = 255;
                    lastTime = true;
                }
                else {
                    current_b += delta;
                }
                if (current_g < delta) {
                    current_g = 0;
                    lastTime = true;
                }
                else {
                    current_g -= delta;
                }
#ifdef _DEBUG
                cout << "column_section = " << column_section << endl;
#endif // DEBUG
                for (row_index = 0; row_index != yellow_array.rows; ++row_index) {
                    int column_start = static_cast<int>(column_section * yellow_array.cols / total_sections);
                    int column_end = static_cast<int>((column_section + 1) * yellow_array.cols / total_sections);
#ifdef _DEBUG
                    if (row_index == 0) cout << "column_start = " << column_start << ", column_end = " << column_end << endl;
#endif // DEBUG
                    for (column_index = column_start; column_index != column_end; ++column_index) {
                        yellow_array.at<Vec<uint8_t, 3>>(row_index, column_index)[0] = current_b;
                        yellow_array.at<Vec<uint8_t, 3>>(row_index, column_index)[1] = current_g;
                    }
                }
                column_section++;
            }
            imshow("Hue evolution = " + to_string(total_sections), yellow_array);
            waitKey(0);
            destroyAllWindows();
        }
        break;
    }
    case 9:
    {
        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                int32_t transp;
                vector<Mat> channels;
                vector<Mat> fixed_channels;
                string exportPath, exportDir;
                Mat transparency_channel;
                Mat image_buffer_updated;
                cout << "The ratio of Transparency (0 ~ 255):\t";
                cin >> transp;

                if ((transp < 0) || (transp > 255))
                {
                    cerr << "THe value is not valid:\t" << transp << "." << endl;
                }
                else
                {
                    split(image_buffer, channels);
                    transparency_channel = Mat(image_buffer.rows, image_buffer.cols, CV_8UC1, Scalar(transp));

                    fixed_channels.push_back(channels[0]);
                    fixed_channels.push_back(channels[1]);
                    fixed_channels.push_back(channels[2]);
                    fixed_channels.push_back(transparency_channel);

                    merge(fixed_channels, image_buffer_updated);

                    cout << "Please assign the directory for exporting the image file (end with \\):\t";
                    cin >> exportDir;
                    exportPath = exportDir + "Test_" + to_string(transp) + ".png";
                    imwrite(exportPath, image_buffer_updated);
                    cout << "Exporting the transparent image file to " << exportPath << " DONE." << endl;
                }
            }
        }
        break;
    }

    case 10:
    {
        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                Mat grayscaleImage = Mat::zeros(image_buffer.rows, image_buffer.cols, CV_8UC1);
                bool result = p203_commonUtil::bgrToGray(image_buffer, grayscaleImage);

                if (!result)
                {
                    cerr << "Grayscale image generation failed for " << fileName << endl;
                }
                else
                {
                    imshow("Grayscale of " + fileName, grayscaleImage);
                    waitKey(0);
                    destroyAllWindows();
                }
            }
        }
        break;
    }

    case 11:
    {
        string fileName;
        cout << "Please assign the full path of 1st image file to be read:\t";
        cin >> fileName;

        string gileName;
        cout << "Please assign the full path of 2nd image file to be read:\t";
        cin >> gileName;

        if ((!haveImageReader(fileName)) || (!haveImageReader(gileName)))
        {
            cerr << "At least one file is not parsable for openCV. Bye" << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);
            Mat jmage_buffer = imread(gileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()) || (jmage_buffer.data == nullptr) || (jmage_buffer.empty()))
            {
                cerr << "At least one file is not readable for openCV. Bye" << endl;
            }
            else
            {
                Mat mergedImage;
                bool ret = p203_commonUtil::mergeImage(image_buffer, jmage_buffer, mergedImage);

                if (!ret)
                {
                    cerr << "Merging image failed for " << fileName << " and " << gileName << endl;
                }
                else
                {
                    imshow("Merged Image", mergedImage);
                    waitKey(0);
                    destroyAllWindows();
                }
            }
        }
        break;
    }
    case 12:
    {
        string filename; 
        cout << "Please assign the  full path of image file to be read:\t";
        cin >> filename;
        if (!haveImageReader(filename)) {
            cerr << "The file is not parsable for openCV:\t" << filename << endl;
        }
        else {
            Mat image_buffer = imread(filename);
            if (image_buffer.data == nullptr || image_buffer.empty()) {
                cerr << "The file is not readable for openCV:\t" << filename << endl;
            }
            else {
                Mat negativeImage;
                bitwise_not(image_buffer, negativeImage);
                imshow("Negative Image", negativeImage);
                waitKey(0);
                destroyAllWindows();
            }
        }
        break;
    }
    case 13:
    {
        uint16_t  r = 0, g = 0, b = 0, i = 0, j = 0;
        const int cols = 1, rows = 1;
        Mat pixel, hsv_array;
        cout << "Please assign the degree of Red(0~255):  \t";
        cin >> r;
        cout << "Please assign the degree of Green(0~255):\t";
        cin >> g;
        cout << "Please assign the degree of Bule(0~255):\t";
        cin >> b;
        
        pixel = Mat(rows, cols, CV_8UC3, Scalar(b, g, r));
        cvtColor(pixel, hsv_array, COLOR_BGR2HSV_FULL);
        cout << "The info of HSV image: depth = " << hsv_array.depth() << ", channel size = " << hsv_array.channels() << endl;
        for (i = 0; i != hsv_array.rows; ++i) {
            for (j = 0; j != hsv_array.cols; ++j) {
                cout << "pixel item:\t{H = " << static_cast<uint16_t>(hsv_array.at<Vec<uint8_t, 3>>(i, j)[0]) * 360 / 256;
                cout << ", S = " << static_cast<double>(hsv_array.at<Vec<uint8_t, 3>>(i, j)[1]+1) / 256.0  * 100.0;
                cout << "%, V = " << static_cast<double>(hsv_array.at<Vec<uint8_t, 3>>(i, j)[2]+1) / 256.0 * 100.0 << "%}," << endl;;
            }
        }
        break;
    }
    case 14:
    {
        string filename;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> filename;
        if (!haveImageReader(filename)) {
            cerr << "The file is not parsable for openCV:\t" << filename << endl;
        }
        else {
            Mat image_buffer = imread(filename);
            if (image_buffer.data == nullptr || image_buffer.empty()) {
                cerr << "The file is not readable for openCV:\t" << filename << endl;
            }
            else {
                Mat grayscaleImage;
                cvtColor(image_buffer, grayscaleImage, COLOR_BGR2GRAY);
                cout << "The info grayscaled image: depth = " << grayscaleImage.depth() << ", channel size = " << grayscaleImage.channels() << endl;
                imshow("Grayscale of " + filename, grayscaleImage);
                waitKey(0);
                destroyAllWindows();
            }
            
        }
        break;
    }
    case 15: 
    {
        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                uint32_t angle;
                Mat rotated_image;
                cout << "Please assign the angle to be rotated counter-wise (90, 270, 180 otherwise):\t";
                cin >> angle;
                switch (angle)
                {
                case 90:
                    rotate(image_buffer, rotated_image, ROTATE_90_CLOCKWISE);
                    break;
                case 270:
                    rotate(image_buffer, rotated_image, ROTATE_90_COUNTERCLOCKWISE);
                    break;
                default:
                    rotate(image_buffer, rotated_image, ROTATE_180);
                    break;
                }
                imshow("Rotated image", rotated_image);
                waitKey(0);
                destroyAllWindows();
            }
        }
        break;
   
    }
    case 16:
    {
        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                vector< Point_<float> > srcEdge = vector< Point_<float> >();
                vector< Point_<float> > dstEdge = vector< Point_<float> >();
                Mat mappingMatrix, calibrated_buffer;
                time_t nowTime = time(nullptr);
                string targetPath, fileName_calibrated;
                cout << "Please assign the dir/path storing the calibrated images, ended with \"\\\":\t";
                cin >> targetPath;

                fileName_calibrated = string(targetPath) + string("calibrated_") + to_string(nowTime) + string(".jpg");

                if ((image_buffer.cols != (P204_DEFAULT_CARLABEL_SIZE_WIDTH)) || (image_buffer.rows != P204_DEFAULT_CARLABEL_SIZE_HEIGHT))
                {
                    resize(image_buffer, image_buffer, Size(P204_DEFAULT_CARLABEL_SIZE_WIDTH, P204_DEFAULT_CARLABEL_SIZE_HEIGHT));
                }

                srcEdge.push_back(Point_<float>(30.0, 95.0));
                srcEdge.push_back(Point_<float>(86.0, 311.0));
                srcEdge.push_back(Point_<float>(450.0, 175.0));
                srcEdge.push_back(Point_<float>(426.0, 11.0));
                dstEdge.push_back(Point_<float>(56.0, 50.0));
                dstEdge.push_back(Point_<float>(56.0, 273.0));
                dstEdge.push_back(Point_<float>(444.0, 273.0));
                dstEdge.push_back(Point_<float>(444.0, 50.0));
                mappingMatrix = getPerspectiveTransform(srcEdge, dstEdge);
                warpPerspective(image_buffer, calibrated_buffer, mappingMatrix, Size(image_buffer.cols, image_buffer.rows));
                imshow("Skewed image: " + fileName, image_buffer);
                waitKey(0);
                imshow("Calibrated image of " + fileName, calibrated_buffer);
                waitKey(0);
                destroyAllWindows();
                imwrite(fileName_calibrated, calibrated_buffer);
                cout << "Exporting the Calibrated image file to " << fileName_calibrated << " DONE." << endl;
            }
        }
        break;
    }
    case 17: 
    {

        string fileName;
        cout << "Please assign the full path of image file to be read:\t";
        cin >> fileName;

        if (!haveImageReader(fileName))
        {
            cerr << "The file is not parsable for openCV:\t" << fileName << endl;
        }
        else
        {
            Mat image_buffer = imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty()))
            {
                cerr << "The file is not readable for openCV:\t" << fileName << endl;
            }
            else
            {
                int i = 0, j = 0;
                Mat cropped_buffer, grayscale_buffer, boolean_buffer;
                time_t nowTime = time(nullptr);
                string targetPath, fileName_boolean;
                cout << "Please assign the dir/path storing the cropped images, ended with \"\\\":\t";
                cin >> targetPath;

                fileName_boolean = string(targetPath) + string("boolean_") + to_string(nowTime) + string(".jpg");

                if ((image_buffer.cols !=
                    P204_DEFAULT_CARLABEL_SIZE_WIDTH) || (image_buffer.rows != P204_DEFAULT_CARLABEL_SIZE_HEIGHT))
                {
                    resize(image_buffer, image_buffer, Size(P204_DEFAULT_CARLABEL_SIZE_WIDTH, P204_DEFAULT_CARLABEL_SIZE_HEIGHT));
                }
                cropped_buffer = image_buffer.colRange(56, 444).rowRange(50, 273);
                cvtColor(cropped_buffer, grayscale_buffer, COLOR_BGR2GRAY);
                boolean_buffer = Mat::zeros(cropped_buffer.rows, cropped_buffer.cols, CV_8UC1);
                for (i = 0; i  != grayscale_buffer.rows; ++i) {
                    for (j = 0; j != grayscale_buffer.cols; ++j) {
                        if (grayscale_buffer.at<uint8_t>(i, j) <= 128) {
                            boolean_buffer.at<uint8_t>(i, j) = 255;
                        }
                        else {
                            boolean_buffer.at<uint8_t>(i, j) = 0;
                        }
                    }
                }
                imshow("GrayScale image", grayscale_buffer);
                waitKey(0);
                imshow("Booleam image", boolean_buffer);
                waitKey(0);
                destroyAllWindows();
                imwrite(fileName_boolean, boolean_buffer);
                cout << "Exporting the booleam image file to" << fileName_boolean << " DONE." << endl;
            }
        }

        
    }
    default:
        break;
    }
    return 0;
}


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
