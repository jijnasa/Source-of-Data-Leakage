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
using namespace std;
using namespace cv;
int main()
{
	//vector< vector<int> > bin_matrix;
	vector<int> bin_array;

	ifstream myReadFile;
	myReadFile.open("test1.txt");

	ofstream ofile("output5.txt");
	Mat im_rgb = cv::imread("fifth.png");          // open image
	//cv::Mat imshow(im_rgb);
	//cout << "hello";
	Mat im_gray;
	if (im_rgb.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n";     // show error message on command line
		return 0;                                          // may have to modify this line if not using Windows
														   //return(0);                                              // and exit program
	}
	im_rgb.convertTo(im_rgb, CV_8UC1);
	int bin, binary;
	cv::cvtColor(im_rgb, im_gray, CV_RGB2GRAY);
	int arr[294];
	//int arra[21][21];

	int height = im_gray.rows;
	int width = im_gray.cols;
	cv::Size smallSize(7, 7);
	//namedWindow("smallImages ", CV_WINDOW_AUTOSIZE);
	int n = 1;
	//char str[40];
	int big_count = 0;
	Mat B = im_gray.clone();
	cv::Mat smallImages;
	//strcpy(str, "smallImages");
	for (int y = 0; y < im_gray.rows; y += smallSize.height)
	{
		for (int x = 0; x < im_gray.cols; x += smallSize.width)
		{
			big_count = big_count + 1;
			cv::Rect rect = cv::Rect(x, y, smallSize.width, smallSize.height);
			cv::Mat new_smallimage = cv::Mat(im_gray, rect);
			if (big_count == 2 || big_count == 4 || big_count == 5 || big_count == 6 || big_count == 8 || big_count == 9)
			{
				for (int i = 0; i < new_smallimage.rows; i++)
				{
					//vector<int> temp;
					for (int j = 0; j < new_smallimage.cols; j++)
					{
						bin = (int(new_smallimage.at<uchar>(i, j)));
						binary = (bin == 0) ? 1 : 0;
						//temp.push_back(binary);
						bin_array.push_back(binary);
					}
					//bin_matrix.push_back(temp);
					//cout << "\n";
				}
			}
			if (big_count == 1)
				smallImages.push_back(cv::Mat(im_gray, rect));


		}
	}
	//smallImages.convertTo(smallImages, CV_32F);

	/*for (int i = 0; i < bin_matrix.size(); i++)
	{
	for (int j = 0; j < bin_matrix[i].size(); j++)
	{
	cout << bin_matrix[i][j];
	}
	cout << "\n";
	}*/
	for (int i = 0; i < bin_array.size(); i++)
	{
	cout << bin_array[i] ;
	}
	
	int p, c,count;
	p = 0;
	count = 0;
	char output;
	if (myReadFile.is_open()) {
		while (myReadFile) {

			myReadFile.get(output);
			if ((int)output == 97 || (int)output == 65 || (int)output == 69 || (int)output == 103)
			{
				if (p<bin_array.size() && bin_array[p] == 1)
				{
					//cout << "Change" << "\t";
					if ((int)output == 97)
					{
						ofile << (char)37;
						//cout << "changed a";
						count++;
					}
					else if ((int)output == 65)
					{
						ofile << (char)59;
						//cout << "changed A";
						count++;
					}
					else if ((int)output == 69)
					{
						ofile << (char)56;
						//cout << "changed E";
						count++;
					}
					else if ((int)output == 103)
					{
						ofile << (char)44;
						//cout << "changed g";
						count++;
					}
					p++;

				}
				else if (p<bin_array.size() && bin_array[p] == 0)
				{
					//cout << "Don't Change";
					ofile << output;
					p++;

				}
				else
				{
					ofile << output;

				}
			}
			else
			{
				ofile << output;
			}
		}
		cout << "\n" << p << "\n";
		cout << "\n" << count << "\n";
	}
	myReadFile.close();
	ofile.close();
	ifstream ifile;
	ifile.open("output5.txt");
	char out;
	int m;
	m = 0;
	//mamnipulate the ASCII value of the character so as to replace it with same character or modified character 
	if (ifile.is_open()) {
		while (ifile) {
			//cout << "\nhello";
			ifile.get(out);

			//cout << (int)out;
			if (m<bin_array.size() && ((int)out == 97 || (int)out == 65 || (int)out == 69 || (int)out == 103))
			{

				arr[m] = 0;
				m++;

			}
			else if (m < bin_array.size() && ((int)out == 37 || (int)out == 59 || (int)out == 56 || (int)out == 44))
			{

				arr[m] = 1;

				m++;
			}

		}
	}
	for (int i = 0; i < 294; i++)
	{
		cout << arr[i];
	}
	
	//cout << bin_array.size();
	//m = 0;
	Mat output1(21, 21, CV_8UC1);
	output1.setTo(0);
	smallImages.copyTo(output1(cv::Rect(0, 0, 7, 7)));
	smallImages.copyTo(output1(cv::Rect(0, 14, 7, 7)));
	smallImages.copyTo(output1(cv::Rect(14, 0, 7, 7)));
	/*for (int i = 0; i < 21; i++)
	{
	for (int j = 0; j < 21; j++)
	{
	arra[i][j] = arr[m];
	cout << arra[i][j];
	m++;
	}
	cout << "\n";
	}*/
	m = 0;
	for (int i = 0; i <7; i++)
	{
		for (int j = 7; j < 14; j++)
		{
			if (arr[m] == 1)
			{
				output1.at<uchar>(i, j) = 0;
				m++;
			}
			else
			{
				output1.at<uchar>(i, j) = 255;
				m++;

			}



		}

	}
	for (int i = 7; i <14; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (arr[m] == 1)
			{
				output1.at<uchar>(i, j) = 0;
				m++;
			}
			else
			{
				output1.at<uchar>(i, j) = 255;
				m++;

			}



		}

	}
	for (int i = 7; i <14; i++)
	{
		for (int j = 7; j < 14; j++)
		{
			if (arr[m] == 1)
			{
				output1.at<uchar>(i, j) = 0;
				m++;
			}
			else
			{
				output1.at<uchar>(i, j) = 255;
				m++;

			}



		}

	}
	for (int i = 7; i <14; i++)
	{
		for (int j = 14; j < 21; j++)
		{
			if (arr[m] == 1)
			{
				output1.at<uchar>(i, j) = 0;
				m++;
			}
			else
			{
				output1.at<uchar>(i, j) = 255;
				m++;

			}



		}

	}
	for (int i = 14; i <21; i++)
	{
		for (int j = 7; j < 14; j++)
		{
			if (arr[m] == 1)
			{
				output1.at<uchar>(i, j) = 0;
				m++;
			}
			else
			{
				output1.at<uchar>(i, j) = 255;
				m++;

			}



		}

	}
	for (int i = 14; i <21; i++)
	{
		for (int j = 14; j < 21; j++)
		{
			if (arr[m] == 1)
			{
				output1.at<uchar>(i, j) = 0;
				m++;
			}
			else
			{
				output1.at<uchar>(i, j) = 255;
				m++;

			}



		}

	}
	imwrite("output5.png", output1);
	cin.get();
	return 0;
}
