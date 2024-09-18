#include "raycasting.h"
#include "draw_walls.h"
#include <math.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "draw_sky.h"
#include "draw_floor.h"

#define TEXTURE_PATH1 "resources/textures/wall1.png"
#define TEXTURE_PATH2 "resources/textures/wall2.png"
#define TILE_SIZE 100

/**
 * load_texture - Loads a texture from a given path and creates an SDL texture.
 * @player: Pointer to the Player structure containing the renderer.
 * @path: Path to the texture file.
 *
 * Return: Pointer to the created SDL texture.
 */
static SDL_Texture *load_texture(Player *player, const char *path)
{
	SDL_Surface *surface = IMG_Load(path);

	if (!surface)
	{
		fprintf(stderr, "Failed to load texture: %s\n", IMG_GetError());
		exit(1);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(player->renderer,
	 surface);
	SDL_FreeSurface(surface);

	if (!texture)
	{
		fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
		exit(1);
	}

	return (texture);
}

/**
 * calculate_depths - Calculates the depth, direction,
 * and offset for raycasting.
 * @player: Pointer to the Player structure.
 * @map: Pointer to the Map structure.
 * @ray_angle: Angle of the ray being cast.
 * @depth: Pointer to store the calculated depth.
 * @direction: Pointer to store the direction (horizontal/vertical).
 * @offset: Pointer to store the texture offset.
 */
static void calculate_depths(Player *player, Map *map, float ray_angle,
	float *depth, int *direction, int *offset)
{
	float sin_a = sinf(ray_angle);
	float cos_a = cosf(ray_angle);
	float x_hor, y_hor, depth_hor;
	float x_vert, y_vert, depth_vert;

	calculate_horizontal_depth(player, map, sin_a, cos_a,
		&x_hor, &y_hor, &depth_hor);
	calculate_vertical_depth(player, map, sin_a, cos_a,
		&x_vert, &y_vert, &depth_vert);

	*depth = (depth_vert < depth_hor) ? depth_vert : depth_hor;
	*direction = (depth_vert < depth_hor) ? 1 : 0;
	*offset = (depth_vert < depth_hor) ?
		(int)fmod(y_vert, TILE_SIZE) :
		(int)fmod(x_hor, TILE_SIZE);

	*depth *= cos(player->angle - ray_angle);
}

/**
 * ray_cast - Performs raycasting and renders the scene.
 * @player: Pointer to the Player structure.
 * @map: Pointer to the Map structure.
 * @results: Array to store raycasting results for each ray.
 */
void ray_cast(Player *player, Map *map, RaycastingResult *results)
{
	SDL_Texture *wall1_texture = load_texture(player, TEXTURE_PATH1);
	SDL_Texture *wall2_texture = load_texture(player, TEXTURE_PATH2);

	draw_sky(player->renderer);
	draw_floor(player->renderer);

	float ray_angle = player->angle - HALF_FOV + 0.0001;

	for (int ray = 0; ray < NUM_RAYS; ray++)
	{
		float depth, proj_height;
		int direction, offset;

		calculate_depths(player, map, ray_angle, &depth, &direction, &offset);
		proj_height = SCREEN_DIST / (depth + 0.0001);

		results[ray] = (RaycastingResult){depth, proj_height, direction, offset};

		SDL_Texture *current_texture = (direction == 1) ?
			wall1_texture : wall2_texture;

		draw_wall_texture(player->renderer, current_texture,
			ray, proj_height, offset);

		ray_angle += DELTA_ANGLE;
	}

	SDL_DestroyTexture(wall1_texture);
	SDL_DestroyTexture(wall2_texture);
}
