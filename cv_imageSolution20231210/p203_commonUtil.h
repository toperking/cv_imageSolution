#pragma once
#include <iostream>
#include <vector>
#include <filesystem>

#include <opencv2/opencv.hpp>

using namespace std;
using std::string;
using std::vector;

using namespace cv;

class p203_commonUtil
{
public:
    static bool bgrToGray(const Mat& bgrImage, Mat& grayImage);
};