#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <omp.h>

namespace lab1
{
  class matrix
  {
  public:
    matrix() = default;

    matrix(int rowsCount, int colsCount)
        : data_(new int *[rowsCount]),
          rows_(rowsCount),
          cols_(colsCount)
    {
      for (int i = 0; i < rows_; i++)
      {
        data_[i] = new int[cols_];
      }
    }

    matrix(const matrix &mat)
        : data_(new int *[mat.rows_]),
          rows_(mat.rows_),
          cols_(mat.cols_)
    {
      for (int i = 0; i < rows_; i++)
      {
        data_[i] = new int[cols_];
      }

      for (int i = 0; i < rows_; i++)
      {
        for (int j = 0; j < cols_; j++)
        {
          data_[i][j] = mat.data_[i][j];
        }
      }
    }

    matrix(matrix &&mat)
        : data_(mat.data_),
          rows_(mat.rows_),
          cols_(mat.cols_)
    {
      mat.data_ = nullptr;
      mat.rows_ = 0;
      mat.cols_ = 0;
    }

    ~matrix()
    {
      if (data_)
      {
        for (int i = 0; i < rows_; i++)
        {
          if (data_[i])
          {
            delete[] data_[i];
          }
        }
      }
    }

    matrix &operator=(const matrix &mat) = delete;
    matrix &operator=(matrix &&mat) = delete;

    inline int *operator[](int rowIndex)
    {
      if (0 <= rowIndex && rowIndex < rows_)
      {
        return data_[rowIndex];
      }

      return nullptr;
    }

    inline const int *operator[](int rowIndex) const
    {
      if (0 <= rowIndex && rowIndex < rows_)
      {
        return data_[rowIndex];
      }

      return nullptr;
    }

    inline operator bool()
    {
      if (!data_)
      {
        return false;
      }

      for (int i = 0; i < rows_; i++)
      {
        if (!data_[i])
        {
          return false;
        }
      }

      return true;
    }

    inline int **data()
    {
      return data_;
    }

    inline const int *const *data() const
    {
      return data_;
    }

    inline int rows() const
    {
      return rows_;
    }

    inline int cols()
    {
      return cols_;
    }

    matrix operator*(const matrix &mat)
    {
      if (cols_ != mat.rows_)
      {
        return matrix();
      }

      matrix result(rows_, mat.cols_);

      for (int i = 0; i < rows_; i++)
      {
        for (int j = 0; j < mat.cols_; j++)
        {
          result[i][j] = 0;
          for (int k = 0; k < cols_; k++)
          {
            result[i][j] += (data_[i][k] * mat.data_[k][j]);
          }
        }
      }

      return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const matrix &mat)
    {
      if (!mat.data_)
      {
        return os;
      }

      for (int i = 0; i < mat.rows_; i++)
      {
        for (int j = 0; j < mat.cols_; j++)
        {
          if (!mat.data_[i])
          {
            return os;
          }

          os << mat.data_[i][j] << ' ';
        }
        os << std::endl;
      }

      return os;
    }

    static matrix parallel_multiplication(const matrix &matrix1, const matrix &matrix2, int thread_num)
    {
      matrix result(matrix1.rows_, matrix2.cols_);
      int i, j, k;
      omp_set_num_threads(thread_num);

      #pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k) collapse(2)
      for (i = 0; i < matrix1.rows_; i++)
      {
        for (j = 0; j < matrix2.cols_; j++)
        {
          result.data_[i][j] = 0;

          for (k = 0; k < matrix1.cols_; k++)
          {
            result.data_[i][j] += (matrix1.data_[i][k] * matrix2.data_[k][j]);
          }
        }
      }

      return result;
    }

  private:
    int **data_ = nullptr;
    int rows_{0};
    int cols_{0};
  };
}

#endif