/*
Nick Cantalupa and Sean Duffy
Code for video feed from Bruce Maxwell
CS5330 Computer Vision
03/14/2025

Display a video feed

*/

#include <opencv2/opencv.hpp>

constexpr bool IPHONE_HANDOFF = true; // If true, video feed from phone will be used if available
constexpr int FRAME_RATE = 24;

int main(int argc, char* argv[])
{
    // open the video device
    auto* capDev = new cv::VideoCapture(static_cast<int>(!IPHONE_HANDOFF));

    if (!capDev->isOpened())
    {
        printf("Unable to open video device\n");
        return (-1);
    }

    cv::Mat frame;

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
            } else
            {
                printf("Frame is empty\n");
                break;
            }
        }

        cv::imshow("AR Video", frame);

        // see if there is a waiting keystroke
        constexpr int waitTime = 1000 / FRAME_RATE;
        const char key = static_cast<char>(cv::waitKey(waitTime)); // TODO revert parameter to waitTime

        if (key == 'q')
        {
            break;
        }

        if (key == 's') // Save images of each step
        {
            std::string timestamp = std::to_string(std::time(nullptr));;
            cv::imwrite("../screenshots/" + timestamp + "_raw.jpg", frame);
            printf("Image saved\n");
        }

    }

    delete capDev;
    return (0);
}
