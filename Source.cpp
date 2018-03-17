#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, const char* argv[])
{
	Mat img = imread("jigi.png");
	Mat saltpepper_noise = Mat::zeros(img.rows, img.cols, CV_8U);
	randu(saltpepper_noise, 0, 255);

	Mat black = saltpepper_noise < 30;
	Mat white = saltpepper_noise > 225;

	Mat saltpepper_img = img.clone();
	saltpepper_img.setTo(255, white);
	saltpepper_img.setTo(0, black);
	imwrite("adding_whitenoise.png", saltpepper_img);
	waitKey();
	return 0;
}