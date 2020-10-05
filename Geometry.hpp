//
// Created by W on 10/4/20.
//

#ifndef LUDUMDARE2020_GEOMETRY_HPP
#define LUDUMDARE2020_GEOMETRY_HPP
#include"glm/glm.hpp"
#include"willow/rendering/wilo_vertex_types.hpp"
class Geometry {

public:

    class Base{
        friend class Geometry;
    public:
        virtual const std::vector<wlo::Vertex3D>& getVerts() = 0;
        virtual const std::vector<uint32_t>& getInds() = 0;
        const std::vector<glm::vec2>& getPoints(){
                return points;
        }
    protected:
        std::vector<glm::vec2> points;
        std::vector<wlo::Vertex3D> verts;
        std::vector<uint32_t> inds;
    };


    class Line:public Base{
        friend class Geometry;
    public:
        const std::vector<wlo::Vertex3D>& getVerts() override;
        const std::vector<uint32_t>& getInds() override;
        Line(glm::vec2 start, glm::vec2 end);
    };

    class Tri:public Base {
        friend class Geometry;
    public:
        const std::vector<wlo::Vertex3D>& getVerts() override;
        const std::vector<uint32_t>& getInds() override;
        Tri(glm::vec2 t0, glm::vec2 t1, glm::vec2 t2);
    };

    class Box :public Base {
        friend class Geometry;
    public:
        Box();
        float width;
        float height;
       const std::vector<wlo::Vertex3D>& getVerts() override;
       const std::vector<uint32_t>& getInds() override;
       Box(glm::vec2 topLeft,float width, float height);
    };

    static bool contains(Box b1, glm::vec2 point);
    static bool intersecting(Box b1, Box b2);




};


#endif //LUDUMDARE2020_GEOMETRY_HPP
