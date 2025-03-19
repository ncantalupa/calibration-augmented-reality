#include <opencv2/core/mat.hpp>
#include <iostream>
#include <fstream>
#include "imgProc.h"
#include "csv_util/csv_util.h"
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

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
    for (int i = 0; i < cameraMatrix.rows; i++) {
        for (int j = 0; j < cameraMatrix.cols; j++) {
            file << cameraMatrix.at<double>(i, j) << " ";
        }
    }
    file << std::endl;
    for (int i = 0; i < distCoeffs.rows; i++) {
        for (int j = 0; j < distCoeffs.cols; j++) {
            file << distCoeffs.at<double>(i, j) << " ";
        }
    }
    file << std::endl;
    file.close();
    return 0;
}
int writeCameraCalibrationJSON(const char* filename, cv::Mat& cameraMatrix, cv::Mat& distCoeffs)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }
    file << "{" << std::endl;
    
    file << "  \"cameraMatrix\": [";
    for (int i = 0; i < cameraMatrix.rows; i++) {
        file << "[";
        for (int j = 0; j < cameraMatrix.cols; j++) {
            file << cameraMatrix.at<double>(i, j);
            if (j < cameraMatrix.cols - 1) {
                file << ", ";
            }
        }
        file << "]";
        if (i < cameraMatrix.rows - 1) {
            file << ", ";
        }
    }
    file << "]," << std::endl;
    
    file << "  \"distCoeffs\": [";
    for (int i = 0; i < distCoeffs.rows; i++) {
        file << "[";
        for (int j = 0; j < distCoeffs.cols; j++) {
            file << distCoeffs.at<double>(i, j);
            if (j < distCoeffs.cols - 1) {
                file << ", ";
            }
        }
        file << "]";
        if (i < distCoeffs.rows - 1) {
            file << ", ";
        }
    }
    file << "]" << std::endl;
    
    file << "}" << std::endl;
    
    file.close();
    return 0;
}

int writeRTvectors(const char* filename, std::vector<cv::Mat>& rvecs, std::vector<cv::Mat>& tvecs)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    file << "Rotation Vectors: [";
    for (size_t i = 0; i < rvecs.size(); i++) {
        file << "[";
        for (int row = 0; row < rvecs[i].rows; row++) {
            for (int col = 0; col < rvecs[i].cols; col++) {
                file << rvecs[i].at<double>(row, col);
                if (col < rvecs[i].cols - 1) {
                    file << ", ";
                }
            }
            if (row < rvecs[i].rows - 1) {
                file << "; ";
            }
        }
        file << "]";
        if (i < rvecs.size() - 1) {
            file << ", ";
        }
    }
    file << "]" << std::endl;

    file << "Translation Vectors: [";
    for (size_t i = 0; i < tvecs.size(); i++) {
        file << "[";
        for (int row = 0; row < tvecs[i].rows; row++) {
            for (int col = 0; col < tvecs[i].cols; col++) {
                file << tvecs[i].at<double>(row, col);
                if (col < tvecs[i].cols - 1) {
                    file << ", ";
                }
            }
            if (row < tvecs[i].rows - 1) {
                file << "; ";
            }
        }
        file << "]";
        if (i < tvecs.size() - 1) {
            file << ", ";
        }
    }
    file << "]";

    file.close();
    return 0;
}

int readCameraCalibration(const char* filename, cv::Mat& cameraMatrix, cv::Mat& distCoeffs)
{
     const int C_ROWS = 3, C_COLS = 3;
     const int D_ROWS = 5, D_COLS = 1;
 
     std::ifstream infile(filename);
     if (!infile.is_open()) {
         std::cerr << "Error opening file: " << filename << "\n";
         return -1;
     }
 
     std::string line;
 
     // Read the first line (camera matrix)
     if (!std::getline(infile, line)) {
         std::cerr << "Error reading camera matrix line.\n";
         return -1;
     }
     std::istringstream issCamera(line);
     cameraMatrix = cv::Mat(C_ROWS, C_COLS, CV_64F);
     for (int i = 0; i < C_ROWS; i++) {
         for (int j = 0; j < C_COLS; j++) {
             double value;
             if (!(issCamera >> value)) {
                 std::cerr << "Error reading camera matrix value at (" << i << ", " << j << ").\n";
                 return -1;
             }
             cameraMatrix.at<double>(i, j) = value;
         }
     }
 
     // Read the second line (distortion coefficients)
     if (!std::getline(infile, line)) {
         std::cerr << "Error reading distortion coefficients line.\n";
         return -1;
     }
     std::istringstream issDist(line);
     distCoeffs = cv::Mat(D_ROWS, D_COLS, CV_64F);
     for (int i = 0; i < D_ROWS; i++) {
         double value;
         if (!(issDist >> value)) {
             std::cerr << "Error reading distortion coefficient at index " << i << ".\n";
             return -1;
         }
         distCoeffs.at<double>(i, 0) = value;
     }
 
     return 0;
}

int readInPoints(char *filename, std::vector<std::vector<float>> &data)
{
    std::vector<char *> filenames;
    int error = read_image_data_csv(filename, filenames, data, 0);
    if (error) {
        std::cerr << "Error reading in points" << std::endl;
        return -1;
    }
    return 0;
}

int draw_sphere(cv::Mat& frame, const cv::Vec3d& rotation_vec, const cv::Vec3d& translation_vec, const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs, std::vector<cv::Point2f>& image_points)
{
    std::vector<std::vector<float>> points;
    readInPoints("../sphere_points.csv", points);

    std::vector<cv::Point3f> object_points;

    for (int i = 0; i < points.size(); i++)
    {
        object_points.push_back(cv::Point3f(points[i][0], points[i][1], points[i][2]));
    }
    cv::projectPoints(object_points, rotation_vec, translation_vec, cameraMatrix, distCoeffs, image_points);
    
    for (int i = 1; i < image_points.size(); i++)
    {
        cv::line(frame, image_points[i-1], image_points[i], cv::Scalar(i*(float(255/200)), 255-i*(float(255/200)), 0), 2);
    }
    return 0;

}

int draw_airplane(cv::Mat& frame, const cv::Vec3d& rotation_vec, const cv::Vec3d& translation_vec, const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs, std::vector<cv::Point2f>& image_points)
{
    std::vector<std::vector<float>> points;
    readInPoints("../airplane_points.csv", points);

    std::vector<cv::Point3f> object_points;

    for (int i = 0; i < points.size(); i++)
    {
        object_points.push_back(cv::Point3f(points[i][0], points[i][1], points[i][2]));
    }
    cv::projectPoints(object_points, rotation_vec, translation_vec, cameraMatrix, distCoeffs, image_points);

    for (int i = 1; i < image_points.size(); i++)
    {
        cv::line(frame, image_points[i-1], image_points[i], cv::Scalar(50, 50, 50), 5);
    }
    return 0;
}