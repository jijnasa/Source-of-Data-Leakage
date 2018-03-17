#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>

#include<iostream>
#include<vector>
#include<conio.h>           // may have to modify this line if not using Windows
using namespace std;
using namespace cv;
///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	cv::Mat im_rgb;        // input image
						   //cv::Mat imgGrayscale;       // grayscale of input image
						   //cv::Mat imgBlurred;         // intermediate blured image
						   //cv::Mat imgCanny;           // Canny edge image
	cv::Mat im_gray;
	im_rgb = cv::imread("scan11.tif");          // open image

	if (im_rgb.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n\n";     // show error message on command line
		_getch();                                               // may have to modify this line if not using Windows
		return(0);                                              // and exit program
	}



	//cout << "Width : " << im_rgb.cols << endl;
	//cout << "Height: " << im_rgb.rows << endl;
	cv::cvtColor(im_rgb, im_gray, CV_RGB2GRAY);
	cv::Mat img_bw;
	//cv::threshold(im_gray, img_bw, 220.0, 255.0, THRESH_BINARY);
	cv::threshold(im_gray, img_bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	//adaptiveThreshold(im_gray, img_bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 2);
	cv::imwrite("scan11_binary.tif", img_bw);
	return 0;
}
