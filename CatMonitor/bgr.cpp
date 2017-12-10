#include <opencv2\opencv.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include "HDTimer.h"
using namespace std;
using namespace cv;
//#define USE_T
int main()
{
	HDTimer timer;
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	if (!cap.isOpened())
	{
		cout << "Camera can not be openned...";
		return 0;
	}
	
	Mat camImg,grayImg;
	Ptr<BackgroundSubtractorMOG2> mog = createBackgroundSubtractorMOG2(30, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
	
	vector<Ptr<BackgroundSubtractorMOG2>> mogs;
	vector<Rect> rects;
	for (int i = 0; i < 4; i++)
	{
		mogs.push_back(createBackgroundSubtractorMOG2(30, 16.0, false));		
	}
	rects.push_back(Rect(0, 0, 640, 360));
	rects.push_back(Rect(0, 360, 640, 360));
	rects.push_back(Rect(640, 0, 640, 360));
	rects.push_back(Rect(640, 360, 640, 360));

	Mat mmask = Mat::zeros(720,1280,CV_8UC1);
	Mat mmasks[4];
	Mat mmask0, mmask1, mmask2, mmask3;
	Mat grayImg0, grayImg1, grayImg2, grayImg3;
	Ptr<BackgroundSubtractorMOG2> mog0 = createBackgroundSubtractorMOG2(30, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
	Ptr<BackgroundSubtractorMOG2> mog1 = createBackgroundSubtractorMOG2(30, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
	Ptr<BackgroundSubtractorMOG2> mog2 = createBackgroundSubtractorMOG2(30, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
	Ptr<BackgroundSubtractorMOG2> mog3 = createBackgroundSubtractorMOG2(30, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
	thread threads[4];

	timer.Start();
	
	while (true)
	{	
		
		cap >> camImg;
		//Mat redu_camImg = Mat::zeros(camImg.size(),camImg.type());
		cvtColor(camImg, grayImg, COLOR_BGR2GRAY);

#ifdef USE_T
		grayImg0 = grayImg(rects[0]);
		mmask0 = mmask(rects[0]);
		grayImg1 = grayImg(rects[1]);
		mmask1 = mmask(rects[1]);
		grayImg2 = grayImg(rects[2]);
		mmask2 = mmask(rects[2]);
		grayImg3 = grayImg(rects[3]);
		mmask3 = mmask(rects[3]);
		
		timer.Stop();
		cout << timer.Elapsed() << "\n";
		timer.Start();
		
		threads[0] = thread([&]() {
			mog0->apply(grayImg0, mmask0, 0.01);
			medianBlur(mmask0, mmask0, 5);
		});
	
		threads[1] = thread([&]() {
			mog1->apply(grayImg1, mmask1, 0.01);
			medianBlur(mmask1, mmask1, 5);
		});

		threads[2] = thread([&]() {
			mog2->apply(grayImg2, mmask2, 0.01);
			medianBlur(mmask2, mmask2, 5);
		});

		threads[3] = thread([&]() {
			mog3->apply(grayImg3, mmask3, 0.01);
			medianBlur(mmask3, mmask3, 5);
		});
		

		for (int index = 0; index < 4; index++)
		{
			threads[index].join();
		}		
#else
		timer.Stop();
		cout << timer.Elapsed() << "\n";
		timer.Start();
		mog->apply(grayImg, mmask,0.01);
		medianBlur(mmask, mmask, 5);
#endif
		

		Point TL(9999, 9999);
		Point BR(0, 0);
		
		//for (int x = 0; x < mmask.cols; x++)
		//{
		//	for (int y = 0; y < mmask.rows; y++)
		//	{
		//		if (mmask.at<uchar>(y, x))
		//		{
		//			if (x < TL.x)
		//				TL.x = x;
		//			if (y < TL.y)
		//				TL.y = y;
		//			if (x > BR.x)
		//				BR.x = x;
		//			if (y > BR.y)
		//				BR.y = y;
		//		}
		//	}
		//}
		//Rect ROI(TL, BR);
		//if ((ROI.width < 9000) && (ROI.height < 9000))
		//{
		//	mmask(Rect(TL, BR)).setTo(1);
		//	camImg.copyTo(redu_camImg, mmask);
		//	//camImg(Rect(TL, BR)).copyTo(redu_camImg);
		//	rectangle(redu_camImg, TL, BR, Scalar(0, 255, 0));
		//}		

		//imshow("webcam", redu_camImg);
		//imshow("Webcam", mmask);
		//if (waitKey(30) >= 0)
		//{
		//	imwrite("diudiu.png", camImg);
		//	break;
		//}
	}
}