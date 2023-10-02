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
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

#include "cuda_img.h"

__global__ void kernel_polovina(CudaImg image)
{
    int index_x = threadIdx.x + blockIdx.x * blockDim.x;
    int index_y = threadIdx.y + blockIdx.y * blockDim.y;

    if (index_x >= image.m_size.x)
        return;

    if (index_y >= image.m_size.y)
        return;

    image.at<uchar3>(index_y, index_x).x /= 2;
    image.at<uchar3>(index_y, index_x).y /= 2;
    image.at<uchar3>(index_y, index_x).z /= 2;
}

void cu_polovina(CudaImg image)
{
    cudaError_t l_cerr;

    int block_size = 32;
    dim3 blocks(((image.m_size.x + block_size - 1) / block_size), ((image.m_size.y + block_size - 1) / block_size));
    dim3 threads(block_size, block_size);

    kernel_polovina<<<blocks, threads>>>(image);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void kernel_bloky(CudaImg image, int x)
{
    int index_x = threadIdx.x + blockIdx.x * blockDim.x;
    int index_y = threadIdx.y + blockIdx.y * blockDim.y;

    if (index_x >= image.m_size.x)
        return;

    if (index_y >= image.m_size.y)
        return;

    int blok = (blockIdx.x + blockIdx.y + x) % 3;

    if (blok == 0)
    {
        image.at<uchar3>(index_y, index_x).z = 0;
        image.at<uchar3>(index_y, index_x).y = 0;
    }

    if (blok == 1)
    {
        image.at<uchar3>(index_y, index_x).z = 0;
        image.at<uchar3>(index_y, index_x).x = 0;
    }

    if (blok == 2)
    {
        image.at<uchar3>(index_y, index_x).y = 0;
        image.at<uchar3>(index_y, index_x).x = 0;
    }
}

void cu_bloky(CudaImg image, int x)
{
    cudaError_t l_cerr;

    int block_size = 32;
    dim3 blocks(((image.m_size.x + block_size - 1) / block_size), ((image.m_size.y + block_size - 1) / block_size));
    dim3 threads(block_size, block_size);

    kernel_bloky<<<blocks, threads>>>(image, x);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}