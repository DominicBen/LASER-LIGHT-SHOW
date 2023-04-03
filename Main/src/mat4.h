#pragma once
#include <vector>
#include <Arduino.h>
#include <vec.h>
#include <transform.h>

class Mat4
{
public:
    // default constructor, initializes matrix to identity
    Mat4() : m_data(4, std::vector<float>(4, 0))
    {
        m_data[0][0] = 1;
        m_data[1][1] = 1;
        m_data[2][2] = 1;
        m_data[3][3] = 1;
    }

    // constructor that takes a 4x4 array of floats
    Mat4(const std::vector<std::vector<float>> &data) : m_data(data) {}

    // matrix addition operator
    Mat4 operator+(const Mat4 &other) const
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
            }
        }
        return result;
    }

    // matrix subtraction operator
    Mat4 operator-(const Mat4 &other) const
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.m_data[i][j] = m_data[i][j] - other.m_data[i][j];
            }
        }
        return result;
    }

    // matrix multiplication operator
    Mat4 operator*(const Mat4 &other) const
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float dot_prod = 0;
                for (int k = 0; k < 4; k++)
                {
                    dot_prod += m_data[i][k] * other.m_data[k][j];
                }
                result.m_data[i][j] = dot_prod;
            }
        }
        return result;
    }

    // scalar multiplication operator
    Mat4 operator*(float scalar) const
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.m_data[i][j] = m_data[i][j] * scalar;
            }
        }
        return result;
    }

    // matrix transposition function
    Mat4 transpose() const
    {
        Mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.m_data[i][j] = m_data[j][i];
            }
        }
        return result;
    }

    // matrix inversion function
    Mat4 inverse() const
    {
        // TODO: implement matrix inversion
        return Mat4();
    }

    // access operator for individual elements of the matrix
    float &operator()(int row, int col)
    {
        return m_data[row][col];
    }

    // const access operator for individual elements of the matrix
    const float &operator()(int row, int col) const
    {
        return m_data[row][col];
    }
    void print() const
    {
        Serial.println("=====================");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                Serial.print(m_data[i][j]);
                Serial.print("\t");
            }
            Serial.println();
        }
        Serial.println("=====================");
    }
    Mat4 rotate(const Vec3 &theta, Vec2 origin)
    {
        float cosX = cos(theta.x);
        float sinX = sin(theta.x);
        float cosY = cos(theta.y);
        float sinY = sin(theta.y);
        float cosZ = cos(theta.z);
        float sinZ = sin(theta.z);

        Mat4 rotationMatrixX = Mat4({{1, 0, 0, 0},
                                     {0, cosX, -sinX, 0},
                                     {0, sinX, cosX, 0},
                                     {0, 0, 0, 1}});

        Mat4 rotationMatrixY = Mat4({{cosY, 0, sinY, 0},
                                     {0, 1, 0, 0},
                                     {-sinY, 0, cosY, 0},
                                     {0, 0, 0, 1}});

        Mat4 rotationMatrixZ = Mat4({{cosZ, -sinZ, 0, 0},
                                     {sinZ, cosZ, 0, 0},
                                     {0, 0, 1, 0},
                                     {0, 0, 0, 1}});
        Mat4 translationMatrix = Mat4({{1, 0, 0, origin.x},
                                       {0, 1, 0, origin.y},
                                       {0, 0, 1, 0},
                                       {0, 0, 0, 1}});
        Mat4 originMatrix = Mat4({{1, 0, 0, -origin.x},
                                  {0, 1, 0, -origin.y},
                                  {0, 0, 1, 0},
                                  {0, 0, 0, 1}});

        Mat4 matrix = originMatrix * *this;
        matrix = rotationMatrixZ * (rotationMatrixY * (rotationMatrixX * matrix));
        matrix = translationMatrix * matrix;
        return matrix;
    }

private:
    std::vector<std::vector<float>> m_data;
};