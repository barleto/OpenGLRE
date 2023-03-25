#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 dir)
		: mPosition(pos), mDirection(glm::normalize(-dir)) {
		updateViewMatrix();
	};
	glm::mat4 getViewMatrix() const { return viewMat; };
	void SetPos(glm::vec3 pos);
	glm::vec3 GetPos() const { return mPosition; };
	void SetDir(glm::vec3 dir);
	glm::vec3 GetDir() const { return mDirection; };
private:
	void updateViewMatrix();
	glm::vec3 mPosition;
	glm::vec3 mDirection;
	glm::mat4 viewMat = glm::mat4(1.0);
};
