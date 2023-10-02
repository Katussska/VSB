#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>

#include "uni_mem_allocator.h"
#include "cuda_img.h"

namespace cv
{
}

void cu_cp(CudaImg bg_image, CudaImg fg_image, int2 bg_pos, int2 pos, int2 pos2);
void cu_resize(CudaImg image, CudaImg copy);
void cu_rotate(CudaImg image, CudaImg copy);

int main(int t_numarg, char **t_arg)
{
    // Uniform Memory allocator for Mat
    UniformAllocator allocator;
    cv::Mat::setDefaultAllocator(&allocator);

    cv::Mat cv_image = cv::imread(t_arg[1], cv::IMREAD_COLOR);
    CudaImg image(cv_image);

    cv::Mat cv_image2 = cv::imread(t_arg[2], cv::IMREAD_COLOR);
    CudaImg image2(cv_image2);

    cu_cp(image, image2, {(int)image.m_size.x / 2, (int)image.m_size.y / 2}, {0, 0}, {100, 100});

    cv::imshow("prvni", cv_image);

    cv::Size prvnisize = cv_image.size();
    prvnisize.width *= 0.2;
    prvnisize.height *= 0.2;

    cv::Mat cv_prvni(prvnisize, CV_8UC3);
    CudaImg prvni(cv_prvni);

    cu_resize(image, prvni);

    cv::imshow("druhy", cv_prvni);

    cv::Mat cv_treti(cv_prvni.size(), CV_8UC3);
    CudaImg treti(cv_treti);

    cu_rotate(prvni, treti);

    cv::imshow("ctvrty", cv_treti);

    cv::waitKey(0);
}
