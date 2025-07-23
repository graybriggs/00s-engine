
#include "array2d.h"

#include <iostream>

template<class T>
Array2D<T>::Array2D(int w, int h) {
    width = w;
    height = h;
    data.resize(width * height);
    fill_all(0);
}

template<class T>
Array2D<T>::Array2D(int w, int h, T datum) {
    width = w;
    height = h;
    data.resize(width * height);
    fill_all(datum);
}

template<class T>
void Array2D<T>::resize(int w, int h) {
    width = w;
    height = h;
    data.resize(width * height);
    fill_all(0);
}

template<class T>
std::size_t Array2D<T>::size() const {
    return static_cast<std::size_t>(width * height);
}

template<class T>
std::size_t Array2D<T>::dimension_size() const {
    return static_cast<std::size_t>(width);
}

template<class T>
void Array2D<T>::insert(int x, int y, T value) {
    data[y * width + x] = value;
}

template<class T>
void Array2D<T>::fill_all(T value) {
    for (int i = 0; i < size(); ++i) {
        data[i] = value;
    }
}

template<class T>
T Array2D<T>::get_at(int x, int y) const {
    return data[y * width + x];
}

template<class T>
void Array2D<T>::print() const {

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << get_at(x, y) << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}