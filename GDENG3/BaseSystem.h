#pragma once
#include "PhysicsSystem.h"

class PhysicsSystem;

class BaseSystem
{
public:
	typedef std::string String;

	static BaseSystem* getInstance();

	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysicsSystem();

private:
	BaseSystem();
	
	BaseSystem(BaseSystem const&) {};				// Copy constructor is private
	BaseSystem& operator=(BaseSystem const&) {};	// Assignment operator is private
	static BaseSystem* sharedInstance;

	PhysicsSystem* physicsSystem;

	~BaseSystem();
};