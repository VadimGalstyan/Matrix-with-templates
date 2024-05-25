#include "matrix.h"
#include <fstream>

int stringToInteger(const std::string& str)
{
    int value = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        value = value * 10 + (str[i] - '0');
    }
    
    return value;
}

double stringToDouble(const std::string& str)
{
    double result = 0.0;
    double sign = 1.0;
    int i = 0;

    if (str[i] == '-') {
        sign = -1.0;
        ++i;
    } else if (str[i] == '+') {
        ++i;
    }

    while (i < str.size() && std::isdigit(str[i])) {
        result = result * 10.0 + (str[i] - '0');
        ++i;
    }

    if (i < str.size() && str[i] == ',') {
        ++i;
        double fraction = 1.0;
        while (i < str.size() && std::isdigit(str[i])) {
            fraction *= 0.1;
            result += (str[i] - '0') * fraction;
            ++i;
        }
    }

    return result * sign;
}

int main()
{
    srand(0);
    std::ofstream fout;
    fout.open("matrix1.txt");

    Matrix<int> matrix1(4,4);
    matrix1.matrixInit();
    matrix1.print();

    if (fout.is_open())
    {
        int rows = matrix1.getRow();
        int cols = matrix1.getColumn();

        for(int i =0;i < rows;++i)
        {
            for(int j = 0;j < cols;++j)
            {
                fout << matrix1[i][j] << std::endl;;
            }
        }
        fout.close();
    }
    
    Matrix<int> matrix2(4,4);
    matrix2.matrixInit();
    matrix2.print();

    fout.open("matrix2.txt");
    
    if (fout.is_open())
    {
        int rows = matrix2.getRow();
        int cols = matrix2.getColumn();

        for(int i =0;i < rows;++i)
        {
            for(int j = 0;j < cols;++j)
            {
                fout << matrix2[i][j] << std::endl;
            }
        }

        fout.close();
    }
    
    std::fstream fin1;
    std::fstream fin2;

    fin1.open("matrix1.txt");
    fin2.open("matrix2.txt");

    fout.open("sum.txt");

    if (matrix1.getRow() == matrix2.getRow() && matrix1.getColumn() == matrix2.getColumn())
    {
        int rows = matrix2.getRow();
        int cols = matrix2.getColumn();

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                std::string str1;
                std::string str2;

                getline(fin1,str1);
                getline(fin2,str2);

                int x = stringToInteger(str1) + stringToInteger(str2);
                fout << x << " ";
            }
            fout << std::endl;
        } 
    }
    
    fin1.close();
    fin2.close();
    fout.close();


    return 0;
}