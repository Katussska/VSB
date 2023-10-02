#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

#include "cuda_img.h"

__global__ void kernel_cp(CudaImg bg_image, CudaImg fg_image, int2 bg_pos, int2 pos, int2 pos2)
{
    int2 fg_index = {(int)threadIdx.x + blockIdx.x * blockDim.x, (int)threadIdx.y + blockIdx.y * blockDim.y};

    if (fg_index.x >= fg_image.m_size.x)
        return;

    if (fg_index.y >= fg_image.m_size.y)
        return;

    if (fg_index.x < pos.x || fg_index.x > pos2.x)
        return;

    if (fg_index.y < pos.y || fg_index.y > pos2.y)
        return;

    int2 bg_index = {fg_index.x + bg_pos.x, fg_index.y + bg_pos.y};

    if (bg_index.x < 0 || bg_index.x >= bg_image.m_size.x)
        return;

    if (bg_index.y < 0 || bg_index.y >= bg_image.m_size.y)
        return;

    bg_image.at<uchar3>(bg_index.x, bg_index.y) = fg_image.at<uchar3>(fg_index.x, fg_index.y);
}

void cu_cp(CudaImg bg_image, CudaImg fg_image, int2 bg_pos, int2 pos, int2 pos2)
{
    cudaError_t l_cerr;

    int block_size = 32;
    dim3 blocks(((fg_image.m_size.x + block_size - 1) / block_size), ((fg_image.m_size.y + block_size - 1) / block_size));
    dim3 threads(block_size, block_size);

    kernel_cp<<<blocks, threads>>>(bg_image, fg_image, bg_pos, pos, pos2);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void kernel_resize(CudaImg image, CudaImg copy)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < copy.m_size.x && y < copy.m_size.y)
    {
        float u = (float)x * image.m_size.x / copy.m_size.x;
        float v = (float)y * image.m_size.y / copy.m_size.y;

        int x1 = (int)floorf(u);
        int y1 = (int)floorf(v);
        int x2 = x1 + 1;
        int y2 = y1 + 1;

        float weight1 = (x2 - u) * (y2 - v);
        float weight2 = (u - x1) * (y2 - v);
        float weight3 = (x2 - u) * (v - y1);
        float weight4 = (u - x1) * (v - y1);

        copy.at<uchar3>(x, y).x = static_cast<uchar>(weight1 * image.at<uchar3>(x1, y1).x + weight2 * image.at<uchar3>(x1, y2).x + weight3 * image.at<uchar3>(x2, y1).x + weight4 * image.at<uchar3>(x2, y2).x);
        copy.at<uchar3>(x, y).y = static_cast<uchar>(weight1 * image.at<uchar3>(x1, y1).y + weight2 * image.at<uchar3>(x1, y2).y + weight3 * image.at<uchar3>(x2, y1).y + weight4 * image.at<uchar3>(x2, y2).y);
        copy.at<uchar3>(x, y).z = static_cast<uchar>(weight1 * image.at<uchar3>(x1, y1).z + weight2 * image.at<uchar3>(x1, y2).z + weight3 * image.at<uchar3>(x2, y1).z + weight4 * image.at<uchar3>(x2, y2).z);
    }
}

void cu_resize(CudaImg image, CudaImg copy)
{
    cudaError_t l_cerr;

    int block_size = 32;
    dim3 blocks(((copy.m_size.x + block_size - 1) / block_size), ((copy.m_size.y + block_size - 1) / block_size));
    dim3 threads(block_size, block_size);

    kernel_resize<<<blocks, threads>>>(image, copy);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void kernel_rotate(CudaImg image, CudaImg copy)
{
    int2 index = {(int)threadIdx.x + blockIdx.x * blockDim.x, (int)threadIdx.y + blockIdx.y * blockDim.y};

    if (index.x >= image.m_size.x)
        return;

    if (index.y >= image.m_size.y)
        return;

    copy.at<uchar3>(copy.m_size.y - index.y - 1, index.x) = image.at<uchar3>(index.x, index.y);
}

void cu_rotate(CudaImg image, CudaImg copy)
{
    cudaError_t l_cerr;

    int block_size = 32;
    dim3 blocks(((copy.m_size.x + block_size - 1) / block_size), ((copy.m_size.y + block_size - 1) / block_size));
    dim3 threads(block_size, block_size);

    kernel_rotate<<<blocks, threads>>>(image, copy);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}