/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "tetris.h"
#include "game_state.h"

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Tetris");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	int num = rand() % sizeof(BLOCKS);
	initialize_game_state();
	// set_current_block(*BLOCKS[num]);

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	int main_block[3][3];
	// memcpy(main_block, BLOCKA, sizeof(BLOCKA));
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		// printf("Game State: %d\n", get_game_state());
		switch (get_game_state())
		{

		case GAME_PLAY:
			play_game();
			break;
		case MAIN_MENU:
			display_menu();
			break;
		case HIGH_SCORES:
			display_high_scores();
			break;
		case EXIT_GAME:
			exit(0);
			break;
		case PAUSE_MENU:
			display_pause_menu();
			break;
		default:
			break;
		}
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
