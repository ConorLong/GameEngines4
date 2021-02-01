#include "Engine/Core/EngineCore.h"


int main(int argc, char* argv[]) 
{
	if (!EngineCore::GetInstance()->OnCreate("engine", 800, 600)) {
		std::cout << "engine failed to init" << std::endl;
		return 0;
	}

	EngineCore::GetInstance()->Run();
	return 0;
}