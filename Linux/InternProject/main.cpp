#include <iostream>
#include "Login.h"
#include<opencv2/opencv.hpp>
#include <chrono>
#include <queue>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

int main()
{   init();
    bool ret=isLoggedIn();
    while(ret!=true)
    {
    ret=isLoggedIn();
    }
    cout<<auth_user<<" is logged in currently \n"<<endl;
    int choose;
    while(true)
    {
    cout<<"Choose Any of the following options \n";
    cout<<"1. To record a short 10 second video and apply Gaussian filter to the red Channel \n";
    cout<<"2. To Show the list of recorded videos for this account \n";
    cout<<"3. To Logout and exit \n";
    cin>>choose;

    if(choose==1)
    { //Making a unique filename for saving the video
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

        strftime (buffer,80,"Vid-%b%d_kl_%H%M%S.avi",timeinfo);
        string filen(buffer);
        string fullpath="ProjectData/"+auth_user+"/"+filen;
        VideoCapture cap(0);//video capture object
        // Check if camera opened successfully
        if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
        }
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        VideoWriter video0(fullpath,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));
        string otherpath=fullpath.substr(0,fullpath.length()-4)+"mod.avi";
        VideoWriter video1(otherpath,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));

        while(1){

        Mat frame,filteredGauss;
        // Capture frame-by-frame
        cap >> frame;
        // If the frame is empty, break immediately
        if (frame.empty())
        break;

        Mat dst=frame.clone();
        Mat bgr[3];
        split(dst,bgr);
        //Gaussian blur is applied on red channel only
        GaussianBlur(bgr[2],bgr[2],Size(5,5),0);
        merge(bgr,3,filteredGauss);
        //filter kernel can be changed
        video1.write(filteredGauss);
        video0.write(frame);
        //showing the result
        imshow( "Original", frame );imshow("Gaussian filtered",filteredGauss);

        char c = (char)waitKey(1);
        end = std::chrono::steady_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()>=7000)
        break;

        }
        // When everything done, release the video capture object
        cap.release();
        video0.release();
        video1.release();
        // Closes all the frames
        destroyAllWindows();
        cout<<"\n Video Saved Successfully \n";
    }
    else if(choose==2)
    {
    //
        cout<<"\n-----------------------------------\n";
        cout<<"   LIST OF VIDEOS FOR THIS ACCOUNT     \n";
        cout<<"\n-----------------------------------\n";
        string command = "cd ProjectData/"+auth_user+";ls -l";
        system(&command[0]);
        cout<<"\n-----------------------------------\n";
    }
    else
    {
    //
    auth_user="";
    cout<<"\n-----------------------------------------\n";
    cout<<"     ----LOGGED OUT SUCCESSFULLY---         \n";
    break;
    }
    }
    return 0;
}
