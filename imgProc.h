/*
Nick Cantalupa and Sean Duffy
02/11/2025

Image processing functions

*/

#ifndef IMGPROC_H
#define IMGPROC_H
#include <opencv2/core.hpp>

int create_point_set(int x, int z, std::vector<cv::Vec3f>& point_set);
#endif //IMGPROC_H