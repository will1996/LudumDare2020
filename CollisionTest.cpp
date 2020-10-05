//
// Created by W on 10/5/20.
//
#include"Geometry.hpp"
int main(){

   Geometry::Box reference (glm::vec2(0,-10),10,10);



   Geometry::Box non_colliding (glm::vec2(10,10),5,5);
   Geometry::Box non_colliding_top (glm::vec2(5,-20),5,5);
    Geometry::Box non_colliding_bottom (glm::vec2(5,5),5,5);
    Geometry::Box non_colliding_left (glm::vec2(-20,-5),5,5);
    Geometry::Box non_colliding_right (glm::vec2(20,-5),5,5);

    Geometry::Box non_colliding_top_right (glm::vec2(20,-20),5,5);
    Geometry::Box non_colliding_bottom_right (glm::vec2(20,20),5,5);
    Geometry::Box non_colliding_top_left (glm::vec2(-20,-20),5,5);
    Geometry::Box non_colliding_bottom_left (glm::vec2(-20,20),5,5);



   Geometry::Box contained (glm::vec2(3,-3),2,2);

   Geometry::Box botomLeft (glm::vec2(-5,-5),10,10);

   Geometry::Box topLeft (glm::vec2(-5,15),10,10);

   Geometry::Box bottomRight (glm::vec2(5,5),10,10);

   Geometry::Box topRight (glm::vec2(5,15),10,10);


   assert(!Geometry::intersecting(reference,non_colliding)&&!Geometry::intersecting(non_colliding,reference));
   assert(!Geometry::intersecting(reference,non_colliding_right)&&!Geometry::intersecting(non_colliding_right,reference));
   assert(!Geometry::intersecting(reference,non_colliding_left)&&!Geometry::intersecting(non_colliding_left,reference));
   assert(!Geometry::intersecting(reference,non_colliding_top_left)&&!Geometry::intersecting(non_colliding_top_left,reference));
   assert(!Geometry::intersecting(reference,non_colliding_top_right)&&!Geometry::intersecting(non_colliding_top_right,reference));
   assert(!Geometry::intersecting(reference,non_colliding_bottom_left)&&!Geometry::intersecting(non_colliding_bottom_left,reference));
    assert(!Geometry::intersecting(reference,non_colliding_bottom_right)&&!Geometry::intersecting(non_colliding_bottom_right,reference));

    assert(Geometry::intersecting(contained,reference));
    assert(Geometry::intersecting(reference,contained));
    assert(Geometry::intersecting(reference,botomLeft));
    assert(Geometry::intersecting(botomLeft,reference));
    assert(Geometry::intersecting(reference,topLeft));
    assert(Geometry::intersecting(topLeft,reference));
    assert(Geometry::intersecting(reference,bottomRight));
    assert(Geometry::intersecting(bottomRight,reference));
    assert(Geometry::intersecting(reference,topRight));
    assert(Geometry::intersecting(topRight,reference));


}