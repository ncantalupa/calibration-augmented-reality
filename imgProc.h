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
int readCameraCalibration(const char* filename, cv::Mat& cameraMatrix, cv::Mat& distCoeffs);
int writeRTvectors(const char* filename, std::vector<cv::Mat>& rvecs, std::vector<cv::Mat>& tvecs);
int draw_object(cv::Mat frame, const cv::Vec3d& rotation_vec, const cv::Vec3d& translation_vec, const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs, const std::vector<cv::Point2f> image_points);

#endif //IMGPROC_H