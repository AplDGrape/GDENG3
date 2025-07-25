#pragma once
#include "Camera.h"
#include "EngineTime.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();

	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getSceneCameraViewMatrix();
private:
	SceneCameraHandler();
	
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;

	Camera* sceneCamera;

	~SceneCameraHandler();
};