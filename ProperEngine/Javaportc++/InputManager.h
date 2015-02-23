#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

using namespace glm;
class InputManager
{
public:
	InputManager(void);
	~InputManager(void);
	void update();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
	bool wasKeyDown(unsigned int keyID) ;
	void setMouseCoords(float x,float y);
	vec2 getMouseCoords() const {return _mousecoords;};

private:
	std::unordered_map<unsigned int,bool> _keyMap;
	std::unordered_map<unsigned int,bool> _previousKeyMap;
	vec2 _mousecoords;
};
