
#include "Camera.h"

void Camera::SetPos(glm::vec3 pos)
{
    mPosition = pos;
    updateViewMatrix();
}

void Camera::SetDir(glm::vec3 dir)
{
    mDirection = glm::normalize(-dir);
    updateViewMatrix();
}

void Camera::updateViewMatrix()
{
    this->viewMat = glm::lookAt(mPosition, mDirection, glm::vec3(0,1,0));
}
