#include "scene.h"
#include <chrono>
#include <thread>

Scene::Scene() :
	__logger {LogLevel::debug}
{
}

void Scene::addObject(Physix::Object* o)
{
	__objects.push_back(std::shared_ptr<Physix::Object>(o));
}

void Scene::advance()
{
	// first run of advance?
	static bool initial = true;

	// when was the last call of advance for good simulation
	static std::chrono::time_point<std::chrono::system_clock> last;

	if(initial)
	{
		last = std::chrono::system_clock::now();
		__logger.debug("Starting with advancing");

		initial = false;
	}

	for(auto object : __objects)
	{
		double g = -9.81;

		//__logger.debug(std::to_string(g));
		// collision
		// accelerations
		object->accelerate(Physix::Vector3D {0.0, 0.0, g});

		double reibung_z = 0.02 * object->velocity().z() * object->velocity().z();
		__logger.debug(std::to_string(reibung_z));

		object->accelerate(Physix::Vector3D { 0.0, 0.0, reibung_z});

		//__logger << object->acceleration();
		__logger.debug(std::to_string(object->acceleration().z()));
		__logger.debug(std::to_string(object->velocity().z()));
		__logger.debug(std::to_string(object->position().z()));
		__logger.debug(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>
									  (std::chrono::system_clock::now() - last).count()));
	}

	for(auto object : __objects)
	{
		// convert from milliseconds to seconds
		double dt = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last).count() / 1000.;

		object->update(__timeFactor * dt);

		//__logger << *object;
	}

	last = std::chrono::system_clock::now();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
