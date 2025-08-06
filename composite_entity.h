#pragma once

#include "entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>



//class CompositeEntity : public Entity {

class CompositeEntity {
public:
    
    //CompositeEntity(const RMesh* m, const Material mat, Texture tex, EntityType et);
    CompositeEntity();
    //~CompositeEntity() = default;

    void set_model_matrix(const glm::mat4& m);

    void add_child(Entity* child);
    const std::vector<Entity*>& get_children() const;
    // const glm::mat4& get_model_matrix() const override;

    //const std::vector<CompositeEntity*>& get_children() const;
    const glm::mat4& get_model_matrix() const;

    // void scale(glm::vec3 factor);
    // void translate(glm::vec3 units);
    // void rotate(float angle, glm::vec3 axis);


private:
    glm::mat4 model;
    std::vector<Entity*> children;
};