#pragma once

#include "file_io.h"


#include <exception>
#include <fstream>
#include <string>
#include <vector>

template<class T>
void write_binary(const std::string& filename, const std::vector<T>& data) {
    
    std::ofstream ofs(filename, std::ios::binary);
    if (ofs.is_open()) {
        ofs.write(reinterpret_cast<const char*>(data.data()), std::size(data) * sizeof(T));
    }
    else {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    ofs.close();
}

template<class T>
std::vector<T> read_binary(const std::string& filename) {

    std::ifstream ifs(filename.c_str(), std::ios::binary);

    if (!ifs) {
        //throw std::ios_base::failure("Failed to open file: " + filename);
        throw std::runtime_error("Failed to open file: " + filename);
    }

    ifs.seekg(0, std::ios::end);
    std::size_t size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);


    if (size % sizeof(T) != 0) {
        throw std::runtime_error("The file is not aligned to type T");
    }

    std::vector<T> buffer(size / sizeof(T));

    ifs.read(reinterpret_cast<char*>(buffer.data()), size);

    ifs.close();

    return buffer;
}
