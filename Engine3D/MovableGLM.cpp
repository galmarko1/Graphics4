#include "MovableGLM.h"
#include <stdio.h>
#include "../res/includes/glm/gtc/matrix_transform.hpp"
#include "../res/includes/glm/gtc/quaternion.hpp"


static void printMat(const glm::mat4 mat)
{
    printf(" matrix: \n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%f ", mat[j][i]);
        printf("\n");
    }
}

MovableGLM::MovableGLM()
{
    ZeroTrans();
}

glm::mat4 MovableGLM::MakeTrans(const glm::mat4 &prevTransformations) const
{
    return prevTransformations * MakeTrans();
}

glm::mat4 MovableGLM::MakeTrans() const
{
    return   trans * rot * scl  ;
}

void MovableGLM::MyTranslate(glm::vec3 delta,int mode)
{
    trans = glm::translate(trans,delta);
}

void  MovableGLM::MyRotateDir(const glm::vec3& dir)
{
    glm::vec3 up = glm::vec3(rot * glm::vec4(0, 1, 0, 0));
    glm::vec3 axis = glm::cross(up, dir);
    float angle = acos(glm::dot(glm::normalize(up), glm::normalize(dir)));
    if (glm::length(axis) <= 0.01f)
    {
        angle = 0;
        axis = glm::vec3(1);
    }
    rot = glm::rotate(rot, angle, axis);
}

void  MovableGLM::MyRotate(float angle,const glm::vec3 &vec,int mode)
{
    rot = glm::rotate(rot,angle,vec);
//    rot = rot * glm::rotate(glm::mat4(1), angle, vec);
}

void  MovableGLM::MyScale(glm::vec3 scale)
{
    scl = glm::scale(scl,scale);
}

void MovableGLM::ZeroTrans()
{
    trans = glm::mat4(1);
    rot = glm::mat4(1);
    scl = glm::mat4(1);
}