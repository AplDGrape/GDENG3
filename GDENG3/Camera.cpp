#include "Camera.h"
#include <iostream>

Camera::Camera(String name):AGameObject(name, AGameObject::CAMERA)
{
	this->setPosition(0.0f, 2.0f, -2.0f);
	//this->cameraFront = Vector3D(0.0f, 0.0f, -1.0f);
	//this->cameraUp = Vector3D(0.0f, 1.0f, 0.0f);
	InputSystem::getInstance()->addListener(this);
	this->updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();

	Matrix4x4 temp;

	// Apply pitch (X) and yaw (Y) rotation
	temp.setIdentity();
	temp.setRotationX(pitch);
	worldCam = worldCam.multiplyTo(temp);

	temp.setIdentity();
	temp.setRotationY(yaw);
	worldCam = worldCam.multiplyTo(temp);

	// Apply position
	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyTo(temp);

	// Invert to get view matrix
	worldCam.getInverse();
	this->LocalMatrix = worldCam;
}

void Camera::defaultmode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		z += rate;
	
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::AerialMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::DownWardMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		y -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		y += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::RightViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::LeftViewMode(float rate, float x, float y, float z)
{
	if (InputSystem::getInstance()->isKeyDown('W')) {
		x -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		x += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		z -= rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		z += rate;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::update(float deltaTime)
{
	float speed = 5.0f * deltaTime;

	// Get orientation-based vectors
	Matrix4x4 rot;
	rot.setIdentity();

	Matrix4x4 temp;
	temp.setIdentity();
	temp.setRotationX(pitch);
	rot = rot.multiplyTo(temp);

	temp.setIdentity();
	temp.setRotationY(yaw);
	rot = rot.multiplyTo(temp);

	Vector3D forward = rot.getZDirection() * -1.0f; // Forward is -Z
	Vector3D right = rot.getXDirection();           // Right is +X
	Vector3D up = Vector3D(0, 1, 0);                // World up

	Vector3D pos = this->getLocalPosition();

	// Movement
	if (InputSystem::getInstance()->isKeyDown('W')) pos = pos - forward * speed;
	if (InputSystem::getInstance()->isKeyDown('S')) pos = pos + forward * speed;
	if (InputSystem::getInstance()->isKeyDown('A')) pos = pos - right * speed;
	if (InputSystem::getInstance()->isKeyDown('D')) pos = pos + right * speed;
	if (InputSystem::getInstance()->isKeyDown(VK_SPACE)) pos = pos + up * speed;
	if (InputSystem::getInstance()->isKeyDown(VK_CONTROL)) pos = pos - up * speed;

	this->setPosition(pos);
	this->updateViewMatrix();
}

void Camera::draw(int width, int height)
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->LocalMatrix;
}



void Camera::onKeyDown(int key)
{
	
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& deltaMousePos)
{
	if (RightMouseDown)
	{
		float sensitivity = 0.002f;
		yaw += deltaMousePos.m_x * sensitivity;
		pitch += deltaMousePos.m_y * sensitivity;

		// Clamp pitch to avoid flipping
		if (pitch > 1.5f) pitch = 1.5f;
		if (pitch < -1.5f) pitch = -1.5f;
	}
}

void Camera::onLeftMouseDown(const Point& mousePosition)
{
}

void Camera::onLeftMouseUp(const Point& mousePosition)
{
}

void Camera::onRightMouseDown(const Point& mousePosition)
{
	this->RightMouseDown = true;
}

void Camera::onRightMouseUp(const Point& mousePosition)
{
	this->RightMouseDown = false;
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}
