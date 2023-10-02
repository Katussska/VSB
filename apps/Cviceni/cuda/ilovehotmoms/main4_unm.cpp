// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava, 2020/11
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage with unified memory.
//
// Image transformation from RGB to BW schema.
// Image manipulation is performed by OpenCV library.
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>

#include "uni_mem_allocator.h"
#include "cuda_img.h"

namespace cv
{
}

void cu_polovina(CudaImg image);
void cu_bloky(CudaImg image, int x);

int main(int t_numarg, char **t_arg)
{
    // Uniform Memory allocator for Mat
    UniformAllocator allocator;
    cv::Mat::setDefaultAllocator(&allocator);

    if (t_numarg < 2)
    {
        printf("Enter picture filename!\n");
        return 1;
    }

    cv::Mat cv_image = cv::imread(t_arg[1], cv::IMREAD_COLOR);

    CudaImg image(cv_image);

    cv::imshow("kokot1", cv_image);

    cu_polovina(image);

    cv::imshow("kokot2", cv_image);

    cv::Mat cv_image2 = cv::imread(t_arg[1], cv::IMREAD_COLOR);

    CudaImg image2(cv_image2);

    cu_bloky(image2, 0);

    cv::imshow("kokot4", cv_image2);

    cv::Mat cv_image3 = cv::imread(t_arg[1], cv::IMREAD_COLOR);

    CudaImg image3(cv_image3);

    cu_bloky(image3, 1);

    cv::imshow("kokot5", cv_image3);

    cv::Mat cv_image4 = cv::imread(t_arg[1], cv::IMREAD_COLOR);

    CudaImg image4(cv_image4);

    cu_bloky(image4, 2);

    cv::imshow("kokot6", cv_image4);

    cv::waitKey(0);
}
