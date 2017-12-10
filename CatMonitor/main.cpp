#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <thread>
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
#define USE_T
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
    int history = 20;
    Ptr<BackgroundSubtractorMOG2> mog = createBackgroundSubtractorMOG2(history, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);

    vector<Ptr<BackgroundSubtractorMOG2>> mogs;
    vector<Rect> rects;
    for (int i = 0; i < 4; i++)
    {
        mogs.push_back(createBackgroundSubtractorMOG2(history, 16.0, false));
    }
    rects.push_back(Rect(0, 0, 640, 360));
    rects.push_back(Rect(0, 360, 640, 360));
    rects.push_back(Rect(640, 0, 640, 360));
    rects.push_back(Rect(640, 360, 640, 360));

    Mat mmask = Mat::zeros(720,1280,CV_8UC1);
    Mat mmasks[4];
    Mat mmask0, mmask1, mmask2, mmask3;
    Mat grayImg0, grayImg1, grayImg2, grayImg3;
    Ptr<BackgroundSubtractorMOG2> mog0 = createBackgroundSubtractorMOG2(history, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
    Ptr<BackgroundSubtractorMOG2> mog1 = createBackgroundSubtractorMOG2(history, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
    Ptr<BackgroundSubtractorMOG2> mog2 = createBackgroundSubtractorMOG2(history, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
    Ptr<BackgroundSubtractorMOG2> mog3 = createBackgroundSubtractorMOG2(history, 16.0, false);//new BackgroundSubtractorMOG(3, 4, 0.8);
    thread threads[4];

    ofstream fp;
    fp.open("log.txt");
    //Mat mmask = Mat::zeros(720,1280,0);
    timer.start();

    vector<Mat> full_history;
    int history_length = 10;

    //for(int k=0;k<100;k++)
    unsigned long long round = 0;
    int saving = 0;
    int folder = 0;
    cap >> camImg;
    while(true)
    {

        cap >> camImg;
//        imshow("hehe",camImg);
//        if(waitKey(20))
//        {
//            continue;
//        }
//        else
//            continue;
        Mat redu_camImg = Mat::zeros(camImg.size(),camImg.type());
        if((full_history.size()==history_length)&&(saving==0))
            full_history.erase(full_history.begin());

        full_history.push_back(camImg.clone());
//        cout<<saving<<","<<full_history.size()<<endl;

//        cout<<saving<<","<<full_history.size()<<endl;
//        if(saving!=0)
//            saving--;
//        if(full_history.size()==20)
//        {
//            for(int i=0;i<full_history.size();i++)
//                imwrite(std::to_string(i)+".jpg",full_history[i]);
//            cout<<"all file saved\n";
//            full_history.erase(full_history.begin(),full_history.begin()+11);
//        }

        round++;

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

        timer.stop();
        fp << timer.elapsed_ms() << "\n";
        timer.start();

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
        timer.stop();
        fp << timer.elapsed_ms() << "\n";
        timer.start();
        mog->apply(grayImg, mmask,0.01);
        medianBlur(mmask, mmask, 5);
#endif


        if((cv::sum(mmask)[0]>0)&&(round>20))
        {
            saving = 1;
//            mmask(Rect(TL, BR)).setTo(1);
//            camImg.copyTo(redu_camImg, mmask);
//            //camImg(Rect(TL, BR)).copyTo(redu_camImg);
//            rectangle(redu_camImg, TL, BR, Scalar(0, 255, 0));
        }
        else if(saving == 1)
        {
            for(int i=0;i<full_history.size();i++)
               imwrite(std::to_string(i)+".jpg",full_history[i]);
            cout<<"all file saved\n";
            full_history.clear();
            saving = 0;
        }

        //imshow("webcam", redu_camImg);
        imshow("mask",mmask);
        if (waitKey(30) >= 0)
        {
            imwrite("diudiu.png", camImg);
            break;
        }
    }
}
