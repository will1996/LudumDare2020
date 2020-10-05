//
// Created by W on 10/4/20.
//
#include "glm/gtx/matrix_transform_2d.hpp"
#include "Physics.hpp"
#include <sstream>
glm::vec2 Physics2D::getHeading(const Physics2D::Object & obj) {
    return glm::rotate(glm::mat3x3(1),obj.rotation)*glm::vec3(0,1,0);
}
const float DRAG = -.001;
Physics2D::Object Physics2D::applyTime(float dt, const Physics2D::Object &obj) {
    Physics2D::Object newObj(obj);
    newObj.acceleration +=newObj.acceleration*DRAG;
    newObj.velocity = obj.acceleration * dt;
    newObj.position = obj.position + newObj.velocity * dt;

    newObj.rotAccel +=newObj.rotAccel*DRAG;
    newObj.rotVel = obj.rotAccel*dt;
    newObj.rotation = obj.rotation+obj.rotVel*dt;
    return newObj;
}

Physics2D::Object Physics2D::applyForce(const Physics2D::Force &F, const Physics2D::Object &obj) {
    Physics2D::Object newObj(obj);
    newObj.acceleration += F.vec/obj.mass;
    return newObj;
}




std::ostream &operator<<(std::ostream &os, const Physics2D::Object &obj) {
    os<<"Physics2D Object{\nPos: ["    << obj.position[0] <<","<<obj.position[1]<<"] \n"
    <<"Vel: ["<<obj.velocity[0]<<","<<obj.velocity[1]<<"] \n"
    <<"Accel: ["<<obj.acceleration[0]<<","<<obj.acceleration[1]<<"] \n}";
    return os;
}

Physics2D::Object Physics2D::applyTorque(float t, const Physics2D::Object & other) {
    Physics2D::Object obj(other);
    obj.rotAccel +=glm::radians(t)/obj.mass;
    return obj;
}
