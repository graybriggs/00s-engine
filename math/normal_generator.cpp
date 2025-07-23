
#include <glm/glm.hpp>

#include <vector>

std::vector<glm::vec3> generate_normals(const float* vertex_data) {

    std::size_t sz = sizeof(vertex_data);
    if (sz % 3 != 0) {
        // error - cannot perform calculation
        return std::vector<glm::vec3>();
    }
    int base = 0;
    std::vector<glm::vec3> points;
    for (int i = 0; i < sz; i += 3) {
        //points.push_back({vertex_data[i + base]
    }
    return std::vector<glm::vec3>();
}