/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"


class Game {
public:
	Game() {
		// set up the window
		InitWindow(1024, 800, "Raylib CPP");
	}

	void init_game() {
		
	}

	void run() {
		init_game();

		// game loop
		while (!WindowShouldClose())
		{
			// drawing
			BeginDrawing();
			ClearBackground(BLACK);

			DrawText("Hello Raylib UTF Game Group", 200,200,20,WHITE);
			
			EndDrawing();
		}

		// cleanup
		CloseWindow();
	}
};

int main () {
	Game game;
	game.run();
	return 0;
}