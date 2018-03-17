#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<fstream>
#include<cstdlib>
#include<string>
#include<conio.h>
#include<map>
#include<vector>
// RGB to CMYK conversion
void rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk) {
	// Allocate cmyk to store 4 componets
	for (int i = 0; i < 4; i++) {
		cmyk.push_back(cv::Mat(img.size(), CV_8UC1));
	}

	// Get rgb
	std::vector<cv::Mat> rgb;
	cv::split(img, rgb);

	// rgb to cmyk
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			float r = (int)rgb[2].at<uchar>(i, j) / 255.;
			float g = (int)rgb[1].at<uchar>(i, j) / 255.;
			float b = (int)rgb[0].at<uchar>(i, j) / 255.;
			float k = std::min(std::min(1 - r, 1 - g), 1 - b);

			cmyk[0].at<uchar>(i, j) = (1 - r - k) / (1 - k) * 255.;
			cmyk[1].at<uchar>(i, j) = (1 - g - k) / (1 - k) * 255.;
			cmyk[2].at<uchar>(i, j) = (1 - b - k) / (1 - k) * 255.;
			cmyk[3].at<uchar>(i, j) = k * 255.;
		}
	}
}

// Test rgb2cmyk function
int main(int argc, char** argv) {
	// TODO: change filename
	cv::Mat src = cv::imread("scan11.tif");
	std::vector<cv::Mat> dst;
	rgb2cmyk(src, dst);

	// Display results
	//cv::imshow("src", src);
	//cv::imwrite("doc2_c.tif", dst[0]);
	//cv::imwrite("doc2_m.tif", dst[1]);
	//cv::imwrite("doc2_y.tif", dst[2]);
	cv::imwrite("scan11_k.tif", dst[3]);

	cv::waitKey(0);
	return 0;
}
