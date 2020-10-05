//
// Created by W on 10/4/20.
//

#include "Geometry.hpp"
static const int LineWidthPixels = 4;

wlo::Vertex3D vertFromPoint(glm::vec2 p){
    return wlo::Vertex3D{glm::vec3(p[0],p[1],0),glm::vec3(1.0,1.0,1.0)};
}
wlo::Vertex3D vertFromPoint(glm::vec2 p,glm::vec3 color){
    return wlo::Vertex3D{glm::vec3(p[0],p[1],0),color};
}

Geometry::Box::Box(glm::vec2 topLeft, float width, float height) {
    this->width =width;
    this->height =width;
    points.push_back(topLeft);
    points.push_back(topLeft+glm::vec2(width,0));
    points.push_back(topLeft+glm::vec2(width,height));
    points.push_back(topLeft+glm::vec2(0,height));
    std::vector<uint32_t> indices{2,1,0,0,3,2};
    inds.insert(inds.end(),indices.begin(),indices.end());
    for(const auto & p :points)
        verts.push_back(vertFromPoint(p));
}

const std::vector<wlo::Vertex3D> &Geometry::Box::getVerts() {
    return verts;
}

const std::vector<uint32_t> &Geometry::Box::getInds() {
    return inds;
}

Geometry::Box::Box() {
        for(int i =0; i < 4; i++)
            points.push_back( glm::vec2(0,0));

        inds = {0,0,0,0,0,0};

        for(const auto & point : points){
           verts.push_back(vertFromPoint(point,{0,0,0}));
        }
};


Geometry::Line::Line(glm::vec2 start, glm::vec2 end) {
    glm::vec2 path = end-start;
    //TODO
}

const std::vector<wlo::Vertex3D> &Geometry::Line::getVerts() {
    return verts;
}

const std::vector<uint32_t> &Geometry::Line::getInds() {
    return inds;
};


Geometry::Tri::Tri(glm::vec2 t0, glm::vec2 t1, glm::vec2 t2) {
   points.push_back(t0);
    points.push_back(t1);
    points.push_back(t2);
    inds.push_back(0);
    inds.push_back(1);
    inds.push_back(2);
    for(const auto & p:points)
        verts.push_back(vertFromPoint(p));
}

const std::vector<wlo::Vertex3D> &Geometry::Tri::getVerts() {
    return verts;
}

const std::vector<uint32_t> &Geometry::Tri::getInds() {
    return inds;
}

bool overlapping(float xmin1, float xmax1, float xmin2, float xmax2){
    return( xmax1 >= xmin2) && (xmax2 >= xmin1) ;
}

bool Geometry::intersecting(Geometry::Box b1, Geometry::Box b2) {
    float tl1x = b1.points[0][0];
    float tl1y = b1.points[0][1];

    float tl2x = b2.points[0][0];
    float tl2y = b2.points[0][1];
    bool retval =  overlapping(tl1x,tl1x+b1.width,tl2x,tl2x+b2.width)&&overlapping(tl1y,tl1y+b1.height,tl2y,tl2y+b2.height);
    return retval;
}
