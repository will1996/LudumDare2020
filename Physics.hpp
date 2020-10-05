//
// Created by W on 10/4/20.
//

#ifndef LUDUMDARE2020_PHYSICS_HPP
#define LUDUMDARE2020_PHYSICS_HPP
#include "glm/glm.hpp"
#include<string>
#include<iostream>
#include"Geometry.hpp"

class Physics2D {
public:
    class Object{
    public:
        glm::vec2 position;
        float rotation;
        Object():position(0,0),velocity(0,0),acceleration(0,0),mass(1),rotation(0),rotAccel(0),rotVel(0){

        }

        Object(const Object & other):
        mass(other.mass),
        position(other.position),
        velocity(other.velocity),
        acceleration(other.acceleration),
        rotation(other.rotation),
        rotVel(other.rotVel) ,
        rotAccel(other.rotAccel)
        {}
    private:
        float rotVel;
        float rotAccel;
        friend class Physics2D;
        glm::vec2 velocity;
        friend std::ostream& operator<<(std::ostream& os, const Physics2D::Object& dt);
        glm::vec2 acceleration;
        float mass = 1;
    };

    class Force{
        friend class Physics2D;
    public:
        Force(){};
        Force(glm::vec2 ivec): vec(ivec){};
        Force(glm::vec2 ivec,float mag): vec(glm::normalize(ivec)*mag){};
    private:
        glm::vec2 vec;
    };




    static glm::vec2 getHeading(const Object& );
    static Object applyTime(float dt, const Object &obj);
    static Object applyForce(const Force & ,const Object&);
    static Object applyTorque(float t, const Object & );

};
std::ostream& operator<<(std::ostream& os, const Physics2D::Object& dt);


#endif //LUDUMDARE2020_PHYSICS_HPP
