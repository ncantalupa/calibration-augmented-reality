#include <opencv2/core/mat.hpp>
#include <iostream>
#include <fstream>
#include "imgProc.h"

int create_point_set(int x, int z, std::vector<cv::Vec3f>& point_set) {
    point_set.clear(); 
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < x; j++) {
            point_set.push_back(cv::Vec3f(static_cast<float>(j), static_cast<float>(i), 0.0f));
        }
    }
    return 0;
}
int writeCameraCalibration(const char* filename, cv::Mat& cameraMatrix, cv::Mat& distCoeffs) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }
    
    file << "Camera Matrix: [";
    for (int i = 0; i < cameraMatrix.rows; i++) {
        for (int j = 0; j < cameraMatrix.cols; j++) {
            file << cameraMatrix.at<double>(i, j);
            if (j < cameraMatrix.cols - 1)
                file << ", ";
        }
        if (i < cameraMatrix.rows - 1)
            file << "; ";
    }
    file << "]" << std::endl;
    
    file << "Distortion Coefficients: [";
    for (int i = 0; i < distCoeffs.rows; i++) {
        for (int j = 0; j < distCoeffs.cols; j++) {
            file << distCoeffs.at<double>(i, j);
            if (j < distCoeffs.cols - 1)
                file << ", ";
        }
        if (i < distCoeffs.rows - 1)
            file << "; ";
    }
    file << "]";
    
    file.close();
    return 0;
}
