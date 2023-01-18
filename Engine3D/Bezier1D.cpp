#include "Bezier1D.h"
#include "MeshConstructor.h"

using glm::vec4;

Bezier1D::Bezier1D(int segNum, int res, int mode, int viewport) : Shape(MeshConstructor::SimpleShapes::Axis, mode) {
    segmentsNum = segNum;
    resT = res;
    segments.push_back(glm::mat4(vec4(0, 0, 0, 0), vec4(0, 0.2, 0, 0), vec4(0.2, 0.4, 0, 0), vec4(0.4, 0.4, 0, 0)));
    segments.push_back(glm::mat4(vec4(0.4, 0.4, 0, 0), vec4(0.6, 0.4, 0, 0), vec4(0.8, 0.2, 0, 0), vec4(0.8, 0, 0, 0)));
    mesh = new MeshConstructor(GetLine(), false);

}


IndexedModel Bezier1D::GetLine() const {
    IndexedModel model;

    for (int segment = 0; segment < segmentsNum; segment++) {
        float t = 0;
        for (int i = 0; i < resT; i++, t += 1.0f / (resT - 1.0f)) {
            model.positions.push_back(glm::vec3(GetPointOnCurve(segment, t)));
            model.indices.push_back(segment * resT + i);
            model.colors.push_back(glm::vec3(0, 1, 0));
        }
    }

    return model;
}

void Bezier1D::UpdateMesh() {
    mesh = new MeshConstructor(GetLine(), false);
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


glm::vec4 Bezier1D::GetControlPoint(int segment, int indx) const {
    if (segment < segmentsNum)
        return segments[segment][indx];
    return segments[segmentsNum - 1][3];
}

glm::vec4 Bezier1D::GetPointOnCurve(int segment, float t) const {
    vec4 p3 = segments[segment][3];
    vec4 p2 = segments[segment][2];
    vec4 p1 = segments[segment][1];
    vec4 p0 = segments[segment][0];

    float c3 = pow(t, 3);
    float c2 = 3 * pow(t, 2) * (1 - t);
    float c1 = 3 * pow(1 - t, 2) * t;
    float c0 = pow(1 - t, 3);

    return c3 * p3 + c2 * p2 + c1 * p1 + c0 * p0;
}

glm::vec3 Bezier1D::GetVelosity(int segment, int t) {
    return glm::vec3();
}

void Bezier1D::SplitSegment(int segment, int t) {
}

void Bezier1D::AddSegment(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3) {
    segmentsNum += 1;
    glm::vec4 p0 = segments[segments.size() - 2][3];
    segments.push_back(glm::mat4(p0, p1, p2, p3));
    std::swap(segments[segments.size() - 1], segments[segments.size() - 2]);
    for (int i = 0; i < 4; i++) {
        segments.back()[i] = segments.back()[i] + glm::vec4(0.6, 0.0, 0.0, 0.0);
    }
}

void Bezier1D::ChangeSegment(int segIndx, glm::vec4 p1, glm::vec4 p2, glm::vec4 p3) {
    glm::vec4 p0 = segments[segIndx - 1][3];
    segments[segIndx] = glm::mat4(p0, p1, p2, p3);
}

float Bezier1D::MoveControlPoint(int segment, int index, float dx, float dy, bool cState) {
    if (!cState || index == 0 || index == 3) {
        vec4 pickedPoint = GetControlPoint(segment, index);
        pickedPoint += vec4(dx, dy, 0, 0);
        segments[segment][index] = pickedPoint;
        switch (index) {
            case 0:
                if (segment != 0) {
                    segments[segment - 1][2] += vec4(dx, dy, 0, 0);
                    segments[segment - 1][3] += vec4(dx, dy, 0, 0);
                }
                segments[segment][1] += vec4(dx, dy, 0, 0);
                break;

            case 3:
                if (segment != segmentsNum - 1) {
                    segments[segment + 1][1] += vec4(dx, dy, 0, 0);
                    segments[segment + 1][0] += vec4(dx, dy, 0, 0);
                }
                segments[segment][2] += vec4(dx, dy, 0, 0);
                break;
        }
    }
    else{
        //p1 or p2 on Cstate
        float dist = glm::distance(dx, dy);
        vec4 dir;
        if(index == 1)
            dir = glm::normalize(GetControlPoint(segment, 1) - GetControlPoint(segment, 0));
        else
            dir = glm::normalize(GetControlPoint(segment, 2) - GetControlPoint(segment, 3));

        vec4 moveDir = (GetControlPoint(segment, index), GetControlPoint(segment, index) + vec4(dx, dy, 0, 0));
        float dot = glm::dot(glm::vec2(dir), glm::vec2(dx, dy));
        segments[segment][index] += dot >= 0 ? dist * dir : -1 * dist * dir;

    }
    //        case 1:
    //            if(cState && segment != 0){
    //                vec4 oldP1 = pickedPoint - vec4(dx, dy, 0, 0) ;
    //                vec4 p0 = GetControlPoint(segment, 0);
    //                vec4 p2 = GetControlPoint(segment -1, 2);
    ////                float angle = glm::dot(glm::normalize(pickedPoint - p0), glm::normalize((oldP1 - p0)));
    ////
    //
    //                int section; // current section
    //
    //// Calculate the dot product of the vectors p1-p3 and p1-p2
    //                float dot = glm::dot(p0 - pickedPoint, p2 - pickedPoint);
    //
    //// Calculate the lengths of the vectors p1-p3 and p1-p2
    ////                float len1 = length(p0 - pickedPoint);
    ////                float len2 = length(p2 - pickedPoint);
    //
    //// Calculate the angle using the dot product and vector lengths
    ////                float angle = acos(dot / (len1 * len2));
    //                float angle = acos(glm::normalize(dot));
    //
    //// Calculate the distance between p1 and p3
    //                float dist = glm::distance(pickedPoint, p0);
    //
    //// Update the position of p2 to preserve the angle with p1 and p3
    //                p2.x = pickedPoint.x + dist * cos(angle);
    //                p2.y = pickedPoint.y + dist * sin(angle);
    //
    ////                float a = glm::distance(pickedPoint, p0);
    ////                float squareA = pow(a, 2);
    ////                float b = glm::distance(oldP1, p0);
    ////                float squareB = pow(b, 2);
    ////                float squareC = pow(glm::distance(oldP1, pickedPoint), 2);
    ////                float angle = glm::radians(acos(squareA + squareB - squareC) / ( 2 * a * b));
    ////                float dist = glm::distance(p0, p2);
    ////
    //                segments[segment - 1][2].x = p2.x;
    //                segments[segment - 1][2].y = p2.y;

    //            }
    //            break;
    //        case 2:
    //
    //
    //            break;

    return 0;
}

void Bezier1D::CurveUpdate(int pointIndx, float dx, float dy, bool preserveC1) {
}

void Bezier1D::ResetCurve(int segNum) {

}

glm::vec4 Bezier1D::GetTangentOnCurve(int segment, float t) const {
    vec4 p3 = segments[segment][3];
    vec4 p2 = segments[segment][2];
    vec4 p1 = segments[segment][1];
    vec4 p0 = segments[segment][0];

    float c0 = 3 * (1 - t) * (1 - t);
    float c1 = 3 * 2 * t * (1 - t);
    float c2 = 3 * t * t;

    vec4 v =  c0 * (p1 - p0) + c1 * (p2 - p1) + c2 * (p3 - p2);
    return glm::normalize(v);

    // TODO remove?
    /*float c2 = 3 * t * t;
    float c1 = 2 * t - 3 * t * t;
    float c0 = 1 - t - t + t * t;

    return c2 * (p3 - p2) + c1 * (p2 - p1) + c0 * (p1 - p0);*/
}

Bezier1D::~Bezier1D(void) {

}