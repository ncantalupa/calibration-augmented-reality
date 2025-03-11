#include <opencv2/core/mat.hpp>
#include "imgProc.h"

int create_point_set(int x, int z, std::vector<cv::Vec3f>& point_set) {
    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < x; j++)
        {
            point_set.push_back(cv::Vec3f(static_cast<float>(j), 0.0f, static_cast<float>(i)));
        }
    }
    return 0;
}
