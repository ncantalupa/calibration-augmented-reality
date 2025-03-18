/*
Nick Cantalupa and Sean Duffy
02/11/2025

Image processing functions

*/

#ifndef IMGPROC_H
#define IMGPROC_H
#include <opencv2/core.hpp>

int create_point_set(int x, int z, std::vector<cv::Vec3f>& point_set);
int writeCameraCalibration (const char* filename, cv::Mat& cameraMatrix, cv::Mat& distCoeffs);
#endif //IMGPROC_H