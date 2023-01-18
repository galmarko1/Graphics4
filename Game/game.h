#pragma once
#include "scene.h"

class Game : public Scene
{
public:

    Game();
    Game(float angle,float relationWH,float near, float far);
    void Init();
    void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
    void ControlPointUpdate();
    void WhenRotate();
    void WhenTranslate();
    void Motion();
    ~Game(void);
    void CreateBezi(int numOfSegments);
    void CubeAnimation(glm::vec4 toMove, glm::vec3 toRotate, float angle);
    void CubeAnimationMoveOnly(glm::vec4 toMove);
    void UpdateBezi();
    void MouseProccessing(int button);

    Bezier1D *bezi;
    int segmentAnimation = 0;
    float tAnimation = 0;
    bool animation = false;
    int moveDirection = 1;
    float epsilon = 0.001f;
    bool cState = false;
};

