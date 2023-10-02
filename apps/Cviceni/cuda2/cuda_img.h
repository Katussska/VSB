#pragma once

#include <opencv2/core/mat.hpp>

// Structure definition for exchanging data between Host and Device
struct CudaImg
{
  uint3 m_size; // size of picture
  union
  {
    void *m_p_void;     // data of picture
    uchar1 *m_p_uchar1; // data of picture
    uchar3 *m_p_uchar3; // data of picture
    uchar4 *m_p_uchar4; // data of picture
  };

  CudaImg(cv::Mat image)
  {
    this->m_size.x = image.size().width;
    this->m_size.y = image.size().height;
    this->m_p_void = (void *)image.data;
  }

  template <typename T>
  __device__ T &at(int y, int x)
  {
    return *((T *)(this->m_p_void + (x + y * this->m_size.x) * sizeof(T)));
  }
};