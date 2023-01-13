#include "Bezier1D.h"
#include "MeshConstructor.h"
using glm::vec4;
Bezier1D::Bezier1D(int segNum,int res,int mode, int viewport) : Shape(MeshConstructor::SimpleShapes::Axis,mode)
{
    segmentsNum = segNum;
    resT = res;
    segments.push_back(glm::mat4(vec4(0,0,0,0),vec4 (0,0.5,0,0), vec4(0.5,1, 0,0), vec4(1,1,0,0)));
    segments.push_back(glm::mat4(vec4(1,1,0,0),vec4 (1.5,1,0,0), vec4(2,0.5, 0,0), vec4(2,0,0,0)));
    mesh = new MeshConstructor(GetLine(),false);

}



IndexedModel Bezier1D::GetLine() const
{
    IndexedModel model;

    LineVertex axisVertices[] =
            {
//                    LineVertex(glm::vec3(1,0,0),glm::vec3(1,0,0)),
//                    LineVertex(glm::vec3(-1,0,0),glm::vec3(1,0,0)),
//                    LineVertex(glm::vec3(0,1,0),glm::vec3(0,1,0)),
//                    LineVertex(glm::vec3(0,-1,0),glm::vec3(0,1,0)),
//                    LineVertex(glm::vec3(0,0,1),glm::vec3(0,0,1)),
//                    LineVertex(glm::vec3(0,0,-1),glm::vec3(0,0,1)),
                    LineVertex(glm::vec3(0,0,0),glm::vec3(1,0,0)),
                    LineVertex(glm::vec3(0,0.5,0),glm::vec3(1,0,0)),
                    LineVertex(glm::vec3(0.5,1,0),glm::vec3(0,1,0)),
                    LineVertex(glm::vec3(1,1,0),glm::vec3(0,1,0)),
                    LineVertex(glm::vec3(1,1,0),glm::vec3(0,0,1)),
                    LineVertex(glm::vec3(1.5,1,0),glm::vec3(0,0,1)),
                    LineVertex(glm::vec3(2,0.5,0),glm::vec3(0,0,1)),
                    LineVertex(glm::vec3(2,0,0),glm::vec3(0,0,1)),
            };


    unsigned int axisIndices[] =
            {
                    0,1,
                    2,3,
                    4,5,
                    6,7
//                    4,5
            };

    for(unsigned int i = 0; i < 6; i++)
    {
        model.positions.push_back(*axisVertices[i].GetPos());
        model.colors.push_back(*axisVertices[i].GetColor());

    }
    for(unsigned int i = 0; i < 6; i++)
        model.indices.push_back(axisIndices[i]);

    return model;
}
//void Bezier1D::Draw( const std::vector<Shader*> shaders, const std::vector<Texture*> textures,bool isPicking){
//    if(texID>=0)
//        textures[texID]->Bind(0);
//    if(isPicking)
//        shaders[0]->Bind();
//    else
//        shaders[shaderID]->Bind();
//    mesh->Bind();
//    /*if(isCopy)
//        glDrawArrays(GL_TRIANGLES, 0, indicesNum);
//    else*/
//    glDrawElements(mode,mesh->GetIndicesNum(), GL_UNSIGNED_INT, 0);
//    mesh->Unbind();
//}


glm::vec4 Bezier1D::GetControlPoint(int segment, int indx) const
{
    if (segment < segmentsNum)
        return segments[segment][indx];
    return segments[segmentsNum - 1][3];
}

glm::vec4 Bezier1D::GetPointOnCurve(int segment, int t)
{
    return glm::vec4();
}

glm::vec3 Bezier1D::GetVelosity(int segment, int t)
{
    return glm::vec3();
}

void Bezier1D::SplitSegment(int segment, int t)
{
}

void Bezier1D::AddSegment(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3)
{
    glm::vec4 p0 = segments.back()[3];
    segments.push_back(glm::mat4(p0, p1, p2, p3));
}

void Bezier1D::ChangeSegment(int segIndx,glm::vec4 p1, glm::vec4 p2, glm::vec4 p3)
{
    glm::vec4 p0 = segments[segIndx-1][3];
    segments[segIndx] = glm::mat4(p0, p1, p2, p3);
}

float Bezier1D::MoveControlPoint(int segment, int indx, float dx,float dy,bool preserveC1)
{
    return 0; //not suppose to reach here
}

void Bezier1D::CurveUpdate(int pointIndx, float dx, float dy, bool preserveC1)
{
}

void Bezier1D::ResetCurve(int segNum)
{

}

Bezier1D::~Bezier1D(void)
{

}