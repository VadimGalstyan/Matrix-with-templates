#ifndef __MATRIX__
#define __MATRIX__

#include <iostream>

template <typename T> 
class Matrix
{
public:
	Matrix(const int& row,const int& col);
	Matrix(const Matrix& obj);
	Matrix& operator=(const Matrix& obj);
    Matrix(Matrix&& obj) noexcept;
	Matrix& operator=(Matrix&& obj) noexcept;
    ~Matrix();

public:
    class RowProxy 
    {
    public:
        RowProxy(T* const r);
        T& operator[](const int& index);

    private:
        T* row = nullptr;
    };

    RowProxy operator[](const int& index) const;

public:
    void inMatrix();
    void printSize()const;
	void print() const;
	void matrixInit();

    int getRow() const;
    int getColumn() const;

private:
	int rows = 0;
	int cols = 0;
	T** ptr;
};

#endif //__MATRIX__



///////////////////////////////////////////////
//////////////IMPLEMENTATION///////////////////
///////////////////////////////////////////////



template <typename T>Matrix<T>::Matrix(const int& row,const int& col) : rows(row),cols(col)
{
    ptr = new T*[rows];
    for(int i = 0;i < rows;++i)
    {
        ptr[i] = new T[cols];
    }
}

template <typename T>Matrix<T>::Matrix(const Matrix& obj)
{
    rows = obj.rows;
    cols = obj.cols;

    ptr = new T*[rows];
    for(int i = 0;i < rows;++i)
    {
        ptr[i] = new T[cols];
    }

    for(int i =0;i < rows;++i)
    {
        for(int j = 0;j < cols;++j)
        {
            ptr[i][j] = obj.ptr[i][j];
        }
    }
}

template <typename T> Matrix<T>&  Matrix<T>::operator=(const Matrix& obj)
{
    if(this != &obj)
    {
        if(rows != obj.rows || cols != obj.cols)
        {
            for(int i = 0;i < rows;++i)
            {  
            delete [] ptr[i];
            }
            delete[] ptr;
        }
                    
            rows = obj.rows;
            cols = obj.cols;

            ptr = new T*[rows];
            for(int i = 0;i < rows;++i)
            {
                ptr[i] = new T[cols];
            }

            for(int i =0;i < rows;++i)
            {
                for(int j = 0;j < cols;++j)
                {
                    ptr[i][j] = obj.ptr[i][j];
                }
            }
    }

    return *this;
}


template <typename T> Matrix<T>::Matrix(Matrix&& obj) noexcept : rows(obj.rows),cols(obj.cols),ptr(obj.ptr)
{
    obj.ptr = nullptr;
    obj.cols = 0;
    obj.rows = 0;
}

template <typename T> Matrix<T>& Matrix<T>::operator=(Matrix&& obj) noexcept
{

if(this != &obj)
{
    for(int i = 0;i < rows;++i)
    {
        delete [] ptr[i];
    }
        delete[] ptr;

    rows = obj.rows;
    cols = obj.cols;
    ptr = obj.ptr;

    obj.ptr = nullptr;
    obj.cols = 0;
    obj.rows = 0;

}

return *this;
}

template <typename T>Matrix<T>::~Matrix()
{
    for(int i = 0;i < rows;++i)
    {
        delete [] ptr[i];
        ptr[i] = nullptr;
    }
    delete[] ptr;
    ptr = nullptr;
}

template <typename T> typename Matrix<T>::RowProxy Matrix<T>::operator[](const int& index) const
{
    return RowProxy(ptr[index]);
}

template <typename T> void Matrix<T>::printSize()const
{
    std::cout<<"Rows: "<<rows<<std::endl;
    std::cout<<"Cols: "<<cols<<std::endl;

}

template <typename T> void Matrix<T>::print() const
{
    for(int i =0;i < rows;++i)
    {
        for(int j = 0;j < cols;++j)
        {
        std::cout<<ptr[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

template <typename T> void Matrix<T>::matrixInit()
{

    for(int i =0;i < rows;++i)
    {
        for(int j = 0;j < cols;++j)
        {
            ptr[i][j] = rand() % 10;
        }
    }
}

template <typename T> void Matrix<T>::inMatrix()
{
    for(int i =0;i < rows;++i)
    {
        for(int j = 0;j < cols;++j)
        {
            std::cin>>ptr[i][j];
        }
    }
}

template <typename T> int Matrix<T>::getRow() const
{
    return rows;
}
 
template <typename T> int Matrix<T>::getColumn() const
{
    return cols;
}


//RowProxy
template <typename T> Matrix<T>::RowProxy::RowProxy(T* const r) : row(r) {}

template <typename T> T& Matrix<T>::RowProxy::operator[](const int& index) {
    return row[index];
}
