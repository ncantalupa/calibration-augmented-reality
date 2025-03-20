/*
Nick Cantalupa and Sean Duffy
Code for video feed from Bruce Maxwell
CS5330 Computer Vision
03/14/2025

Display a video feed with Harris corners

*/

#include <fstream>
#include <opencv2/opencv.hpp>
#include "imgProc.h"

constexpr bool IPHONE_HANDOFF = true; // If true, video feed from phone will be used if available
constexpr int FRAME_RATE = 60;

int main(int argc, char* argv[])
{
    // open the video device
    auto* capDev = new cv::VideoCapture(static_cast<int>(!IPHONE_HANDOFF));

    if (!capDev->isOpened())
    {
        printf("Unable to open video device\n");
        return (-1);
    }

    cv::Mat frame; // OpenCV image object


    for (;;)
    {
        *capDev >> frame; // get a new frame from the camera, treat as a stream

        if (frame.empty())
        {
            int attempts = 0;
            attempts += 1;
            if (attempts < 3)
            {
                continue;
            }
            else
            {
                printf("Frame is empty\n");
                break;
            }
        }


        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Mat dst = cv::Mat::zeros( frame.size(), CV_32FC1 ); // Matrix to store the Harris detector responses
        // Best params were blockSize = 3, ksize = 3, k = 0.04
        cv::cornerHarris( gray, dst, 3, 3, 0.04 );

        for( int i = 0; i < frame.rows ; i++ )
        {
            for( int j = 0; j < frame.cols; j++ )
            {
                if( dst.at<float>(i, j) > 0.0001 )
                {
                    // If the likelihood of a corner is above the threshold above, circle it
                    circle( frame, cv::Point(j,i), 5,  cv::Scalar(0, 0, 255), 2, 8, 0 );
                }
            }
        }

        cv::imshow("Harris Corners", frame);

        // see if there is a waiting keystroke
        constexpr int waitTime = 1000 / FRAME_RATE;
        const char key = static_cast<char>(cv::waitKey(waitTime));

        if (key == 'q')
        {
            break;
        }

    }

    delete capDev;
    return (0);
}
