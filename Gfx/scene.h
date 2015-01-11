#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "log.h"
#include "object.h"

class Scene
{
public:
	Scene();

	/**
	 * @brief addObject adds an object to the scene which should be	on the heap
	 * @param o
	 */
	void addObject(Physix::Object* o);

	/**
	 * @brief advance --> go one step forward in the "worldsimulation"
	 */
	void advance();

	/**
	 * @brief setTimeFactor in simulation, fastforward/slow down
	 * @param factor
	 */
	void setTimeFactor(double factor) { if(factor > 0) __timeFactor = factor; }

	/**
	 * @brief getTimeFactor
	 * @return
	 */
	double getTimeFactor() const { return __timeFactor; }

private:
	/**
	 * @brief __objects saving all objects in the scene
	 */
	std::vector<std::shared_ptr<Physix::Object>>	__objects;

	/**
	 * @brief __timeFactor standard 1 --> this will fastforward/slow down, negativ is baaad, mkay
	 */
	double	__timeFactor = .5;



	Log		__logger;
};

#endif // SCENE_H
