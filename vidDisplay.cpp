/*
Nick Cantalupa and Sean Duffy
Code for video feed from Bruce Maxwell
CS5330 Computer Vision
03/14/2025

Display a video feed

*/

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

    cv::Mat frame;                  // OpenCV image object
    cv::Mat gray;                   // Grayscale Image for finding corners
    cv::Mat foundCornersImg;        // Image with corners drawn on it
    std::vector<cv::Point2f> corner_set;          // Vector of corners found
    std::vector<cv::Point2f> foundCornersCoords;  // Vector of corners found, for saving last found set
    int x = 9;
    int z = 6;
    cv::Size patternsize(x, z);    // Size of the chessboard pattern
    std::vector<cv::Vec3f> point_set;       // Vector of 3D points
	std::vector<std::vector<cv::Vec3f> > point_list;        // List of 3D points
	std::vector<std::vector<cv::Point2f> > corner_list;     // List of the corners found in each image

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

        // Find the chessboard corners
        bool patternfound = findChessboardCorners(gray, patternsize, corner_set,
            cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE
            + cv::CALIB_CB_FAST_CHECK);
        
        // If corners are found, refine the corner locations, then store the locations for calibration
        if(patternfound) {
            cornerSubPix(gray, corner_set, cv::Size(11, 11), cv::Size(-1, -1),
            cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));
            drawChessboardCorners(frame, patternsize, cv::Mat(corner_set), patternfound);
            foundCornersImg = frame.clone();
            foundCornersCoords = corner_set;
            std::cout << "Corners Found: " << corner_set.size()<< " First Corner: " <<  corner_set[0] << std::endl;
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
            cv::imwrite("../screenshots/" + timestamp + ".jpg", foundCornersImg);
            corner_list.push_back(foundCornersCoords);
            create_point_set(x,z, point_set);
            point_list.push_back(point_set);
            std::cout << "Corners list: " << corner_list.size() << std::endl;
            printf("Image saved\n");
        }

    }

    delete capDev;
    return (0);
}
