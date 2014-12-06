#include "scene.h"
#include <iostream>



int main()
{
	//logger << "Fuck this shit\n";
	Scene test;
	Log logger;

	test.addObject(new Physix::Object);

	while(true)
		test.advance();
		//std::cout << "Hallo" << std::endl;

	//logger << "What is this shit\n";
	return 0;
}
