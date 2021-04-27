#include "Engine/Core/EngineCore.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) 
{
	EngineCore::GetInstance()->SetGameInterface(new Game1());

	if (!EngineCore::GetInstance()->OnCreate("engine", 800, 800)) {
		std::cout << "engine failed to init" << std::endl;
		return 0;
	}

	EngineCore::GetInstance()->Run();
	return 0;
}