/*
Nick Cantalupa and Sean Duffy
Code for video feed from Bruce Maxwell
CS5330 Computer Vision
03/14/2025

Display a video feed

*/

#include <opencv2/opencv.hpp>

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

    cv::Mat frame;
    cv::Mat gray;
    std::vector<cv::Point2f> corners;
    cv::Size patternsize(9,6);
    std::vector<cv::Vec3f> point_set;
	std::vector<std::vector<cv::Vec3f> > point_list;
	std::vector<std::vector<cv::Point2f> > corner_list;

    for (;;)
    {
        *capDev >> frame; // get a new frame from the camera, treat as a stream
        // make gray the grayscale version of frame
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

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

        bool patternfound = findChessboardCorners(gray, patternsize, corners,
            cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE
            + cv::CALIB_CB_FAST_CHECK);
        if(patternfound) {
            cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1),
            cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));
          drawChessboardCorners(frame, patternsize, cv::Mat(corners), patternfound);
          std::cout << "Corners Found: " << corners.size()<< " First Corner: " <<  corners[0] << std::endl;
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
