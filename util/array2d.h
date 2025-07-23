#pragma once

#include <vector>

template<class T>
class Array2D {
public:

    Array2D() = default;
    Array2D(int width, int height);
    Array2D(int width, int height, T datum);

    void resize(int w, int h);
    std::size_t size() const;
    std::size_t dimension_size() const;

    void insert(int x, int y, T value);
    void fill_all(T value);
    T get_at(int x, int y) const;

    void print() const;
    
private:
    int width;
    int height;
    std::vector<T> data;
};

template class Array2D<float>;
template class Array2D<double>;
template class Array2D<int>;