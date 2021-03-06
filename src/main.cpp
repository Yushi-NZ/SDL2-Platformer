#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");

	// Entity entitiess[3] = {
	// 	Entity(0, 0, grassTexture),
	// 	Entity(30, 0, grassTexture),
	// 	Entity(30, 30, grassTexture)
	// };

	std::vector<Entity> entities = {Entity(Vector2f(0, 0), grassTexture),
									Entity(Vector2f(30, 0), grassTexture),
									Entity(Vector2f(30, 30), grassTexture),
									Entity(Vector2f(30, 60), grassTexture)};

	{
		Entity wilson(Vector2f(100, 50), grassTexture);

		entities.push_back(wilson);
	}


	bool gameRunning = true;

	SDL_Event event;

	const float deltaTime = 0.01f;
	float accumlator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while (gameRunning)
	{
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumlator += frameTime;

		while(accumlator >= deltaTime)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}

			accumlator -= deltaTime;
		}

		window.clear();
		
		for (Entity& e : entities)
		{
			window.render(e);
		}

		//std::cout << utils::hireTimeInSeconds() << std::endl;
		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}