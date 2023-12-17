#include <iostream>
#include <vector>
#include <filesystem>
#include<opencv2/core/matx.hpp>

using namespace std;
using std::string;
using std::vector;
using cv::Vec;
using cv::Mat;

class p201_commonUtil
{
public :
	static bool getFileList(const string filePath, vector<string>& fileList);
	static void lotteNumberGenerator(Vec<uint8_t, 7>& lotteList);
	static bool generateRandomMatrix2D(Mat& buffer);
	static bool generateRandomMatrix3D(Mat& buffer);
	

};

