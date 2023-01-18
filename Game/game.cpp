#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

static void printMat(const glm::mat4 mat) {
    std::cout << " matrix:" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            std::cout << mat[j][i] << " ";
        std::cout << std::endl;
    }
}

Game::Game() : Scene() {
}

Game::Game(float angle, float relationWH, float near1, float far1) : Scene(angle, relationWH, near1, far1) {
}

void Game::CreateBezi(int numOfSegments) {
    float distanceBetweenPoints = 0.2f;
    int j = 0;
    if (!shapes.empty()) {
        int segNum = bezi->segmentsNum;
        MoveCamera(0, xTranslate, -0.15 * (bezi->segmentsNum - 2));
    }
    bezi = new Bezier1D(2, 10, LINE_STRIP);

    glm::vec4 firstPointOfEndCurve = bezi->GetControlPoint(1, 0);

    for (int i = 0; i < numOfSegments - 2; i++) {
        bezi->AddSegment(firstPointOfEndCurve + glm::vec4(distanceBetweenPoints * (j + 1), 0, 0, 0),
                         firstPointOfEndCurve + glm::vec4(distanceBetweenPoints * (j + 2), 0, 0, 0),
                         firstPointOfEndCurve + glm::vec4(distanceBetweenPoints * (j + 3), 0, 0, 0));
        j += 3;
        MoveCamera(0, xTranslate, 0.15);
    }
    bezi->UpdateMesh();
    shapes.clear();

    for (int i = 0; i < bezi->segmentsNum; i++) {
        for (int j = 0; j < 4; j++) {
            AddShape(Octahedron, -1, TRIANGLES);
            SetShapeTex(i * 4 + j, 0);
            shapes.back()->MyTranslate(glm::vec3(bezi->GetControlPoint(i, j)), 0);
            shapes.back()->MyScale(glm::vec3(0.05));
        }
    }
    shapes.push_back(bezi);
    AddShape(Cube, -1, TRIANGLES);
    SetShapeTex(shapes.size() - 1, 0);
    shapes.back()->MyTranslate(glm::vec3(bezi->GetControlPoint(0, 0)), 0);
    shapes.back()->MyScale(glm::vec3(0.1, 0.1, 0.1));
}

void Game::UpdateBezi() {
    bezi->UpdateMesh();
    shapes.clear();

    for (int i = 0; i < bezi->segmentsNum; i++) {
        for (int j = 0; j < 4; j++) {
            AddShape(Octahedron, -1, TRIANGLES);
            SetShapeTex(i * 4 + j, 0);
            shapes.back()->MyTranslate(glm::vec3(bezi->GetControlPoint(i, j)), 0);
            shapes.back()->MyScale(glm::vec3(0.05));
        }
    }
    shapes.push_back(bezi);
    AddShape(Cube, -1, TRIANGLES);
    SetShapeTex(shapes.size() - 1, 0);
    shapes.back()->MyTranslate(glm::vec3(bezi->GetControlPoint(0, 0)), 0);
    shapes.back()->MyScale(glm::vec3(0.1, 0.1, 0.1));
}

void Game::CubeAnimation(glm::vec4 toMove, vec3 toRotate, float angle) {
    shapes.back()->MyTranslate(vec3(toMove), 0);
    shapes.back()->MyRotate(0.075 * angle, toRotate, 0);
}

void Game::CubeAnimationMoveOnly(glm::vec4 toMove) {
    shapes.back()->MyTranslate(vec3(toMove), 0);
}

void Game::Init() {

    AddShader("../res/shaders/pickingShader");
    AddShader("../res/shaders/basicShader");

    AddTexture("../res/textures/box0.bmp", false);

    CreateBezi(3);

    pickedShape = 0;

    MoveCamera(0, zTranslate, 10);
    MoveCamera(0, xTranslate, 0.5);
    pickedShape = -1;

    //ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Game::MouseProccessing(int button)
{
    if (pickedShape == shapes.size() - 1)
    {
        pickedShape = 0;
    }

     if (!animation && pickedShape >= 0 && pickedShape < shapes.size() - 2) {

        int segment = pickedShape / 4;
        int index = pickedShape % 4;


        float angle = 3.14f / 180.0f * GetAngle(0);
        float z = GetFar(0) + picked_depth * (GetNear(0) - GetFar(0));

        float currX = 2 * tan(angle) * ((xPicked * GetFar(0)) / (800 * z)) * GetNear(0);
        float currY = 2 * tan(angle) * ((yPicked * GetFar(0)) / (800 * z)) * GetNear(0);

        float x = xrel + xPicked;
        float y = yrel + yPicked;

        float currX2 = 2 * tan(angle) * ((x * GetFar(0))/ (800 * z)) * GetNear(0);
        float currY2 = 2 * tan(angle) * ((y * GetFar(0))/ (800 * z)) * GetNear(0);

        xPicked = x;
        yPicked = y;
        float xMove = (currX - currX2) / 3.0f;
        float yMove = (currY - currY2) / 3.0f;
        vec4 dx = vec4(xMove, 0, 0, 1), dy = vec4(0, yMove, 0, 1);

        if (button == 1) // Right Click
        {
            bezi->MoveControlPoint(segment, index, dx.x, -dy.y, cState);
            UpdateBezi();
        }
        else{ //left click
            //move p2 of old segment to the line of p0 & p1
            if(index == 0 && segment != 0){
                vec4 p2 = bezi->GetControlPoint(segment - 1, 2);
                vec4 p1 = bezi->GetControlPoint(segment, index + 1);
                vec4 p0 = bezi->GetControlPoint(segment, index);

                glm::vec4 dir = glm::normalize(p1 - p0);
                float distance = glm::distance(p0, p2);
                vec4 newP2 = p0 + (dir * distance);
                bezi->MoveControlPoint(segment - 1, 2, (newP2.x - p2.x), (newP2.y - p2.y), cState);
                UpdateBezi();
            }
            else if(index == 1)
            {
                vec4 p1 = bezi->GetControlPoint(segment, 1);
                vec4 p0 = bezi->GetControlPoint(segment, 0);
                float angle = atan2(p1.y - p0.y, p1.x - p0.x) + (2.0f * 3.1415f / 180.0f);
                float R = sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2));
                vec4 newPos = p0 + R * vec4(cos(angle), sin(angle), 0, 0);
                bezi->segments[segment][index] = newPos;

                // rotate prev p2 in the same angle
                if (cState && segment > 0)
                {
                    vec4 p2 = bezi->GetControlPoint(segment - 1, 2);
                    float angle = atan2(p2.y - p0.y, p2.x - p0.x) + (2.0f * 3.1415f / 180.0f);
                    float R = sqrt(pow(p2.x - p0.x, 2) + pow(p2.y - p0.y, 2));
                    vec4 newPos = p0 + R * vec4(cos(angle), sin(angle), 0, 0);
                    bezi->segments[segment - 1][2] = newPos;
                }

                UpdateBezi();
            }
            else if (index == 2)
            {
                vec4 p2 = bezi->GetControlPoint(segment, 2);
                vec4 p3 = bezi->GetControlPoint(segment, 3);
                float angle = atan2(p2.y - p3.y, p2.x - p3.x) + (2.0f * 3.1415f / 180.0f);
                float R = sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2));
                bezi->segments[segment][index] = p3 + R * vec4(cos(angle), sin(angle), 0, 0);;

                // rotate next p1 in the same angle
                if (cState && segment < bezi->segmentsNum - 1)
                {
                    vec4 p1 = bezi->GetControlPoint(segment + 1, 1);
                    float angle = atan2(p1.y - p3.y, p1.x - p3.x) + (2.0f * 3.1415f / 180.0f);
                    float R = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));
                    bezi->segments[segment + 1][1] = p3 + R * vec4(cos(angle), sin(angle), 0, 0);;
                }

                UpdateBezi();
            }
            else if(index == 3 && segment != bezi->segmentsNum - 1){
                vec4 p2 = bezi->GetControlPoint(segment, 2);
                vec4 p1 = bezi->GetControlPoint(segment + 1, 1);
                vec4 p0 = bezi->GetControlPoint(segment, index);

                glm::vec4 dir = -glm::normalize(p1 - p0);
                float distance = glm::distance(p0, p2);
                vec4 newP2 = p0 + (dir * distance);
                bezi->MoveControlPoint(segment, 2, (newP2.x - p2.x), (newP2.y - p2.y), cState);
                UpdateBezi();
            }
        }
    }
}

void Game::Update(const glm::mat4 &MVP, const glm::mat4 &Model, const int shaderIndx) {
    Shader *s = shaders[shaderIndx];
    int r = ((pickedShape + 1) & 0x000000FF) >> 0;
    int g = ((pickedShape + 1) & 0x0000FF00) >> 8;
    int b = ((pickedShape + 1) & 0x00FF0000) >> 16;
    s->Bind();
    s->SetUniformMat4f("MVP", MVP);
    s->SetUniformMat4f("Normal", Model);
    s->SetUniform4f("lightDirection", 0.0f, 0.0f, -1.0f, 0.0f);
    if (shaderIndx == 0)
        s->SetUniform4f("lightColor", r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    else
        s->SetUniform4f("lightColor", 0.7f, 0.8f, 0.1f, 1.0f);
    s->Unbind();
}

void Game::WhenRotate() {
}

void Game::WhenTranslate() {
}

void Game::Motion() {
    if (animation) {
        vec4 currentPoint = bezi->GetPointOnCurve(segmentAnimation, tAnimation);
        vec4 tangent = bezi->GetTangentOnCurve(segmentAnimation, tAnimation);
        tAnimation += moveDirection * epsilon;
        vec4 nextPoint = bezi->GetPointOnCurve(segmentAnimation, tAnimation);


        shapes.back()->MyTranslate(vec3(nextPoint - currentPoint), 0);
        shapes.back()->MyRotateDir(vec3(tangent));

        if (tAnimation >= 1) {
            segmentAnimation++;
            if (segmentAnimation == bezi->segmentsNum) {
                moveDirection *= -1;
                tAnimation = 1;
                segmentAnimation--;
            } else {
                tAnimation = 0;
            }
        } else if (tAnimation <= 0) {
            segmentAnimation--;
            if (segmentAnimation < 0) {
                animation = false;
                tAnimation = 0;
                segmentAnimation = 0;
                moveDirection *= -1;
            } else {
                tAnimation = 1;
            }
        }
    }
}

Game::~Game(void) {
}
