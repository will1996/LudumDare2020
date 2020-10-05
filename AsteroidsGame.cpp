//
// Created by W on 10/4/20.
//

#include "AsteroidsGame.hpp"
#include"glm/gtx/matrix_transform_2d.hpp"
#include"glm/gtx/string_cast.hpp"
#include"glm/gtx/vector_angle.hpp"
#include<cstdlib>



AsteroidsGame::AsteroidsGame(float width, float height): width(width), height(height),AsteroidSpawnTicker(300),idCounter(0){
    player.id = idCounter++;
}

void AsteroidsGame::insertAndOffset(std::vector<uint32_t> &inds, const std::vector<uint32_t> &new_inds, size_t offset) {
    for(const auto & i : new_inds )
        inds.push_back(i+offset);
}

void insertAtEnd(std::vector<wlo::Vertex3D> &  verts, const std::vector<wlo::Vertex3D> & newVerts){
    for(const auto & v : newVerts)
        verts.push_back(v);
}

void AsteroidsGame::spawnBullet(glm::vec2 origin, float rotation){

        Bullet b;
        b.id = idCounter++;
        b.phys.position = origin;
        b.phys.rotation = rotation;

        b.phys = Physics2D::applyForce(Physics2D::Force(Physics2D::getHeading(b.phys),30),b.phys);
        bullets[b.id] = b;
}

void AsteroidsGame::spawnAsteroid(glm::vec2 origin) {
    Asteroid a;
    a.id = idCounter++;
    a.phys.position = origin;
    a.phys.rotation = rand()*360;
    a.phys = Physics2D::applyForce(Physics2D::Force(Physics2D::getHeading(a.phys),3),a.phys);
    asteroids[a.id] = a;
}


AsteroidsGame::Frame AsteroidsGame::Tick(AsteroidsGame::Input input) {
    Frame next;
//recieive input
    if(input.W){
        player.phys = Physics2D::applyForce(Physics2D::Force(Physics2D::getHeading(player.phys),.1),player.phys);
//        player.phys.position[1]+=1
    }
    if(input.S){
       player.phys =  Physics2D::applyForce(Physics2D::Force(Physics2D::getHeading(player.phys),-.1),player.phys);

 //       player.phys.position[1]-=1;
    }
    if(input.Space){
        std::cout<<"spawning bullet"<<std::endl;
        spawnBullet(player.phys.position,player.phys.rotation);
    }

    glm::vec2 center = glm::vec2(width/2,height/2);
    glm::vec2 mousePos =   glm::vec2(input.mouseX,input.mouseY) - center;
    player.phys.rotation = atan2(mousePos[1]-player.phys.position[1],mousePos[0]-player.phys.position[0])+90;

    if(AsteroidSpawnTicker.active())
       spawnAsteroid(glm::vec2(rand()*width/2-width,rand()*height/2-height));

     //update tickers
     AsteroidSpawnTicker.tick();


     //update physics
    player.phys = Physics2D::applyTime(1,player.phys);
    for(auto & [idx,bullet]: bullets)
    bullet.phys = Physics2D::applyTime(1,bullet.phys);
    for(auto & [idx,asteroid]: asteroids)
        asteroid.phys = Physics2D::applyTime(1,asteroid.phys);

    //fetch living ids
    std::vector<size_t> bulletIDs; bulletIDs.reserve(bullets.size());
    for(const auto & [id,bullet] :bullets)
        bulletIDs.push_back(id);

    std::vector<size_t> asteroidIDs; asteroidIDs.resize(asteroids.size());
    for(const auto & [id,asteroid] :asteroids)
        asteroidIDs.push_back(id);

    //handle collisions
    std::unordered_map<size_t,Geometry::Box> bulletColliders; bulletColliders.reserve(bullets.size());
    for(auto & [id,bullet] : bullets)
        bulletColliders[id] = getCollider(bullet);

    std::unordered_map<size_t,Geometry::Box> asteroidColliders; asteroidColliders.reserve(bullets.size());
    for(auto & [id,asteroid] : asteroids)
        asteroidColliders[id] = getCollider(asteroid);

    for(const auto & aid : asteroidIDs){
        for(const auto & bid : bulletIDs){
            if(Geometry::intersecting(asteroidColliders[aid],bulletColliders[bid])){
                asteroids.erase(aid);
                asteroidColliders.erase(aid);
                bullets.erase(bid);
                bulletColliders.erase(bid);
            }
        }
    }

    for(const auto & aid : asteroidIDs){
        if(asteroids.find(aid)!=asteroids.end())
        if(Geometry::intersecting(asteroidColliders[aid],getCollider(player))){
            state = GameOver;
        }
    }

    for(const auto & bid : bulletIDs){
        if(bullets.find(bid)!=bullets.end())
            if(Geometry::intersecting(bulletColliders[bid],getCollider(player))){
                state = GameOver;
                bullets.erase(bid);
                bulletColliders.erase(bid);
            }
    }






   //handle non-physical collisions
    constrain(player.phys);
    for(auto & [id,bullet]: bullets)
        constrain(bullet.phys);
    for(auto & [id,asteroid] : asteroids)
        constrain(asteroid.phys);

    insertAtEnd(next.verts,getPlayerVerts());
    insertAndOffset(next.inds, player.model[0].getInds(), 0);
    insertAndOffset(next.inds, player.model[1].getInds(), next.verts.size()/2);

    size_t offset = next.verts.size();
    insertAtEnd(next.verts,getBulletsVerts());
    for(auto & [idx,bullet] : bullets) {
        insertAndOffset(next.inds, bullet.model[0].getInds(), offset += 4);
    }
    insertAtEnd(next.verts,getAsteroidsVerts());
    for(auto & [idx,asteroid] : asteroids) {
        for (auto &tri : asteroid.model)
            insertAndOffset(next.inds, tri.getInds(), offset += 3);
    }

    return next;
}

std::vector<wlo::Vertex3D> AsteroidsGame::getPlayerVerts() {
    std::vector<wlo::Vertex3D> finalVerts;
    for(auto & model: player.model)
    for(auto & vert : model.getVerts()){
        glm::mat3x3 translation = glm::translate(glm::mat3x3(1),player.phys.position);
        glm::mat3x3 rotation = glm::rotate(glm::mat3x3(1),player.phys.rotation);
        glm::vec3 finalPosition = translation*rotation*glm::vec3(vert.position[0],vert.position[1],1);
        finalPosition[2] = 0.0f;
        finalVerts.push_back({finalPosition,vert.color});
        //std::cout<<glm::to_string(finalPosition)<<std::endl;
        }
    return finalVerts;
}


std::vector<wlo::Vertex3D> AsteroidsGame::getAsteroidsVerts() {
    std::vector<wlo::Vertex3D> finalVerts;
    for (auto &[idx,asteroid] :asteroids) {
            for (auto tri : asteroid.model)
                for (auto &vert : tri.getVerts()) {
                    glm::mat3x3 translation = glm::translate(glm::mat3x3(1), asteroid.phys.position);
                    glm::mat3x3 rotation = glm::rotate(glm::mat3x3(1), asteroid.phys.rotation);
                    glm::vec3 finalPosition = translation * rotation * glm::vec3(vert.position[0], vert.position[1], 1);
                    finalPosition[2] = 0.0f;
                    finalVerts.push_back({finalPosition, {1.0, .9, 1}});
                }
    }

    return finalVerts;
}


std::vector<wlo::Vertex3D> AsteroidsGame::getBulletsVerts() {
    std::vector<wlo::Vertex3D> finalVerts;
    for (auto &[idx,bullet] : bullets) {
        for (auto &vert : bullet.model[0].getVerts()) {
            glm::mat3x3 translation = glm::translate(glm::mat3x3(1), bullet.phys.position);
            glm::mat3x3 rotation = glm::rotate(glm::mat3x3(1), bullet.phys.rotation);
            glm::vec3 finalPosition = translation * rotation * glm::vec3(vert.position[0], vert.position[1], 1);
            finalPosition[2] = 0.0f;
            finalVerts.push_back({finalPosition, {1.0, 0, 0}});
        }
    }

    return finalVerts;
}

void AsteroidsGame::resize(float width, float height) {
    this->width = width;
    this->height = height;

}


void AsteroidsGame::constrain(Physics2D::Object &obj) {
    if(obj.position[0]>width/2)
        obj.position[0] = -width/2+1;
    if(obj.position[0]<-width/2)
        obj.position[0] = width/2-1;
    if(obj.position[1]>height/2)
        obj.position[1] = -height/2+1;
    if(obj.position[1]<-height/2)
        obj.position[1] = height/2-1;
}


Geometry::Box AsteroidsGame::getCollider(AsteroidsGame::Player &p) {
    glm::vec2 point = p.collider.getPoints()[0];
    glm::mat3x3 translation = glm::translate(glm::mat3x3(1), p.phys.position);
    glm::vec3 finalPosition = translation *  glm::vec3(point[0], point[1], 1);
    return Geometry::Box(glm::vec2(finalPosition[0],finalPosition[1]),p.collider.width,p.collider.height);
}

Geometry::Box AsteroidsGame::getCollider(AsteroidsGame::Bullet &b) {
    glm::vec2 point = b.collider.getPoints()[0];
    glm::mat3x3 translation = glm::translate(glm::mat3x3(1), b.phys.position);
    glm::vec3 finalPosition = translation *  glm::vec3(point[0], point[1], 1);
    return Geometry::Box(glm::vec2(finalPosition[0],finalPosition[1]),b.collider.width,b.collider.height);

}

Geometry::Box AsteroidsGame::getCollider(AsteroidsGame::Asteroid &a) {
    glm::vec2 point = a.collider.getPoints()[0];
    glm::mat3x3 translation = glm::translate(glm::mat3x3(1), a.phys.position);
    glm::vec3 finalPosition = translation *  glm::vec3(point[0], point[1], 1);
    return Geometry::Box(glm::vec2(finalPosition[0],finalPosition[1]),a.collider.width,a.collider.height);
}




