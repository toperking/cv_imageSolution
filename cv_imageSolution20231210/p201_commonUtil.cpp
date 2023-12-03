#include "p201_commonUtil.h"
#include <filesystem>
#include<ctime>
#include<unordered_set>
#include <opencv2/opencv.hpp>

using namespace std::filesystem;
using namespace cv;



bool p201_commonUtil::getFileList(const string filePath, vector<string>& fileList) {
	bool ret = false;
	try {
		directory_iterator fileNameSet = directory_iterator(filePath);
		for (directory_entry curr_item : fileNameSet) {
			if (curr_item.is_regular_file()) {
				fileList.push_back(curr_item.path().string());
			}
		}
		ret = true;
	}
	catch (exception e) {
		cerr << e.what() << endl;
	}
	return ret;
}

void p201_commonUtil::lotteNumberGenerator(Vec<uint8_t, 7>& lotteList) {
	unordered_set<uint8_t> ::const_iterator it;
	unordered_set<uint8_t> lotteSet = unordered_set<uint8_t>();
	RNG prng = RNG(static_cast<uint64_t>(time(nullptr)));
	int jt = 0;
	while (lotteSet.size() < lotteList.channels) {
		lotteSet.insert(prng.uniform(1, 50));
	}
	for (it = lotteSet.begin(); it != lotteSet.end(); ++it) {
		if (jt < lotteList.channels) {
			lotteList[jt++] = *it;
		}
		else {
			break;
		
		}
	}
	return;
}

bool p201_commonUtil::generateRandomMatrix2D(Mat& buffer) {
	if ((buffer.channels() > 1) || (buffer.depth() != CV_64F)){
		return false;
	}
	int i = 0;
	int j = 0;
	RNG prng = RNG(static_cast<uint64_t>(time(nullptr)));

	for (i = 0; i != buffer.rows; ++i) {
		for (j = 0; j != buffer.cols; ++j) {
			buffer.at<double>(i, j) = floor(prng.uniform(0.0, 256.0));
		}
	}
	return true;
}

bool p201_commonUtil::generateRandomMatrix3D(Mat& buffer)
{
	int depth = buffer.channels();
	if ((buffer.channels() != 3) || (buffer.depth() != CV_64F))
	{
		return false;
	}

	int i = 0;
	int j = 0;
	int k = 0;
	RNG prng = RNG(static_cast<uint64_t>(time(nullptr)));

	MatIterator_< Vec<double, 3> > it = buffer.begin< Vec<double, 3> >();

	for (it = buffer.begin< Vec<double, 3> >(); it != buffer.end< Vec<double, 3> >(); ++it)
	{
		for (k = 0; k != depth; ++k)
		{
			(*it)[k] = floor(prng.uniform(0.0, 256.0));
		}
	}

	return true;
}

