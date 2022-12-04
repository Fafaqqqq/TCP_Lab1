#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include <chrono>
#include <fstream>

#include "matrix.h"

using namespace std;

static int to_int(const std::string &str)
{
  std::istringstream sin(str);
  int res;

  sin >> res;

  return res;
}

static std::vector<lab1::matrix> matrix_generator(int argc, char **argv)
{
  std::vector<lab1::matrix> result;

  if (1 == argc)
  {
    return result;
  }

  for (int i = 1; i < argc; ++i)
  {
    if (std::string(argv[i]) == "--matrix")
    {
      int rows = to_int(argv[++i]);
      int cols = to_int(argv[++i]);

      lab1::matrix mat(rows, cols);

      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          mat[i][j] = rand() % 11;
        }
      }

      // std::cout << mat << std::endl
      //           << std::endl;

      result.push_back(std::move(mat));
    }
  }

  return result;
}

void printMatrix(int **matrix, int n, int m)
{
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < m; j++)
    {
        std::cout << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

int main(int argc, char** argv)
{
  srand(time(NULL));

  auto mat_v = matrix_generator(argc, argv);

  std::ofstream fout;
  std::string filename;
  int thread_num;

  for (int i = 0; i < argc; i++)
  {
    if (std::string(argv[i]) == "--file")
    {
      fout.open(argv[++i], std::ios::app);
      filename = argv[i];
    }

    if (std::string(argv[i]) == "--threads")
    {
      thread_num = atoi(argv[++i]);
    }
  }
  
  // Не паралелльно вычисление
  {
    auto begin = std::chrono::steady_clock::now();
  
    auto res = mat_v[0] * mat_v[1];

    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    printf("[NP]: time -> %ldms\n", elapsed_ms.count());
  }

  // Паралелльное вычисление
  {
    auto begin = std::chrono::steady_clock::now();
  
    auto res1 = lab1::matrix::parallel_multiplication(mat_v[0], mat_v[1], thread_num);

    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    printf("[P]: time -> %ldms\n\n", elapsed_ms.count());
  }

  return 0;
}