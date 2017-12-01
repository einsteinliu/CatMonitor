#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>
using namespace std;
using namespace cv;

struct HDTimer
{
    struct timeval start_t;
    struct timeval stop_t;
    void start()
    {
        gettimeofday(&start_t,0);
    }
    void stop()
    {
        gettimeofday(&stop_t,0);
    }
    double elapsed_ms()
    {
        return (stop_t.tv_sec - start_t.tv_sec)*1000.0 + (stop_t.tv_usec - start_t.tv_usec)/1000.0;
    }
};

int main()
{          
    HDTimer timer;
    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
    cap.set(CV_CAP_PROP_FPS, 30);
    if (!cap.isOpened())
    {
        cout << "Camera can not be openned...";
        return 0;
    }

    Mat camImg,grayImg;
    Ptr<BackgroundSubtractorMOG2> mog = createBackgroundSubtractorMOG2(30, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);

    Mat mmask = Mat::zeros(720,1280,0);
    timer.start();

    while (true)
    {

        cap >> camImg;
        timer.stop();
        cout<<timer.elapsed_ms()<<endl;
        timer.start();

        Mat redu_camImg = Mat::zeros(camImg.size(),camImg.type());
        cvtColor(camImg, grayImg, COLOR_BGR2GRAY);

        Mat gray_teil = grayImg(Rect(Point(0,0),Point(300,300)));
        Mat mmask_teil = mmask(Rect(Point(0,0),Point(300,300)));
        mog->apply(gray_teil, mmask_teil,0.01);

        imshow("hehe",mmask);
        waitKey(20);

        //medianBlur(mmask, mmask, 3);
//        Point TL(9999, 9999);
//        Point BR(0, 0);

//        for (int x = 0; x < mmask.cols; x++)
//        {
//            for (int y = 0; y < mmask.rows; y++)
//            {
//                if (mmask.at<uchar>(y, x))
//                {
//                    if (x < TL.x)
//                        TL.x = x;
//                    if (y < TL.y)
//                        TL.y = y;
//                    if (x > BR.x)
//                        BR.x = x;
//                    if (y > BR.y)
//                        BR.y = y;
//                }
//            }
//        }
//        Rect ROI(TL, BR);
//        if ((ROI.width < 9000) && (ROI.height < 9000))
//        {
//            mmask(Rect(TL, BR)).setTo(1);
//            camImg.copyTo(redu_camImg, mmask);
//            //camImg(Rect(TL, BR)).copyTo(redu_camImg);
//            rectangle(redu_camImg, TL, BR, Scalar(0, 255, 0));
//        }

//        imshow("webcam", redu_camImg);
//        //imshow("Webcam", camImg);
//        if (waitKey(30) >= 0)
//        {
//            imwrite("diudiu.png", camImg);
//            break;
//        }
    }
}
