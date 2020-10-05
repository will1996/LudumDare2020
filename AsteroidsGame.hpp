//
// Created by W on 10/4/20.
//

#ifndef LUDUMDARE2020_ASTEROIDSGAME_HPP
#define LUDUMDARE2020_ASTEROIDSGAME_HPP
#include "glm/glm.hpp"
#include "willow/rendering/wilo_vertex_types.hpp"
#include"Physics.hpp"
#include "Geometry.hpp"
#include<array>
#include "FrameTicker.hpp"
const static Geometry::Tri pmLeft{glm::vec2(-20, -20), glm::vec2(0, 0), glm::vec2(0, -10)};
const static Geometry::Tri pmRight{glm::vec2(0, -10), glm::vec2(0, 0), glm::vec2(20, -20)};
const static Geometry::Box pCollider{glm::vec2{-5,0},20,10 };


const static Geometry::Box laserBody{glm::vec2(-2,10),4,10};
const static Geometry::Box laserCollider{glm::vec2(-2,-10),4,10};

const static Geometry::Tri a0{glm::vec2(0,0),glm::vec2(10,20),glm::vec2(20,10)};
const static Geometry::Tri a1{glm::vec2(0,0),glm::vec2(-10,20),glm::vec2(10,20)};
const static Geometry::Tri a2{glm::vec2(0,0),glm::vec2(-20,10),glm::vec2(-10,20)};
const static Geometry::Tri a3{glm::vec2(0,0),glm::vec2(-20,-10),glm::vec2(-20,10)};
const static Geometry::Tri a4{glm::vec2(0,0),glm::vec2(-10,-20),glm::vec2(-20,-10)};
const static Geometry::Tri a5{glm::vec2(0,0),glm::vec2(10,-20),glm::vec2(-10,-20)};
const static Geometry::Tri a6{glm::vec2(0,0),glm::vec2(20,-10),glm::vec2(10,-20)};
const static Geometry::Tri a7{glm::vec2(0,0),glm::vec2(20,10),glm::vec2(20,-10)};
const static Geometry::Box asteroidCollider{glm::vec2(-20,-20),40,40};


class AsteroidsGame {
public:
    enum State {
       Startmenu, Playing, GameOver
    };
    struct Input{
        float dt;
        bool W;
        bool A;
        bool S;
        bool D;
        bool T;
        bool G;
        bool Space;
        float mouseX;
        float mouseY;
        Input():dt(0),W(false),A(false),S(false),D(false),T(false),G(false),Space(false),mouseX(0),mouseY(0){

        }
    };

    struct Frame{
        std::vector<wlo::Vertex3D> verts;
        std::vector<uint32_t > inds;
    };
    AsteroidsGame(float width, float height);
    void resize(float width, float height);
    Frame Tick(Input);

private:
    size_t idCounter;

    struct GameObject{
        size_t id;
    };
    friend class GameObject;

    struct Player :GameObject {
        Physics2D::Object phys;
        std::array<Geometry::Tri,2> model{pmLeft, pmRight};
        Geometry::Box collider{pCollider};
    };
    struct Asteroid :GameObject{
        Physics2D::Object phys;
        std::array<Geometry::Tri,8> model{a0,a1,a2,a3,a4,a5,a6,a7};
        Geometry::Box collider{asteroidCollider};
    };
    struct Bullet :GameObject{
        Physics2D::Object phys;
        std::array<Geometry::Box,1> model{laserBody};
        Geometry::Box collider{laserCollider};
    };
    Player player;



    std::map<size_t,Asteroid> asteroids;
    std::map<size_t,Bullet> bullets;



    State state;
    float width;
    float height;

    Geometry::Box getCollider(Player & p);
    Geometry::Box getCollider(Bullet & b);
    Geometry::Box getCollider(Asteroid & a);



    void constrain(Physics2D::Object & obj);
    void insertAndOffset(std::vector<uint32_t> &inds, const std::vector<uint32_t> &new_inds, size_t offset);
    void spawnBullet(glm::vec2 origin, float rotation);
    void spawnAsteroid(glm::vec2 origin);
    FrameTicker AsteroidSpawnTicker;
    std::vector<wlo::Vertex3D> getPlayerVerts();
    std::vector<wlo::Vertex3D> getAsteroidsVerts();
    std::vector<wlo::Vertex3D> getBulletsVerts();



};


#endif //LUDUMDARE2020_ASTEROIDSGAME_HPP
