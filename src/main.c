#include "game.h"
#include "cleanup.h"
/**
 * main - Entry point of the game
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	GameState state;

	initialize_game(&state);
	run_game(&state);
	cleanup_all(&state);
	return (0);
}
