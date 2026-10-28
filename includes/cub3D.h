/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:14:31 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 17:39:15 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# ifndef __Apple__
# include "../lib/mlx_mac/mlx.h"
# else
# include "../lib/mlx_linux/mlx.h"
# include <X11/keysym.h>
# endif
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define STEP_LEN 0.3
# define ROTATE_SPEED 0.5

enum						e_colour
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	PLAYER_C = 14176079,
	WALL_MAP_C = 9076325,
	FLOOR_MAP_C = 11183506,
	NORTH_C = 612669,
	SOUTH_C = 1219765,
	EAST_C = 6033031,
	WEST_C = 11866916,
	SPARE_C = 15917052,
	RAY_C = 15113737,
};

enum						e_data
{
	BLOC_LEN = 10,
	WIDTH = 1280,
	HEIGHT = 720,
	BPP = 32,
	PLAYER_SIZE = 2,
	RESOLUTION = 10,
	RAY_PER_PIX = 1,
	VISION_WIDE = 60,
};

enum						e_zones
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	NORTH_WEST = 4,
	NORTH_EAST = 5,
	SOUTH_WEST = 6,
	SOUTH_EAST = 7,
	INSIDE = 8,
	VERTICAL = 9,
	HORIZONTAL = 10,
};

# ifdef __APPLE__
enum						e_keys
{
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_LEFT = 123,
	KEY_D = 2,
	KEY_RIGHT = 124,
	ON_KEYDOWN = 2,
};
# endif

#ifdef __LINUX__
enum						e_keys
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_LEFT = 65361,
	KEY_D = 100,
	KEY_RIGHT = 65363,
	ON_KEYDOWN = 2,
};
#endif

typedef struct s_cubed		t_cubed;
typedef struct s_imgs		t_imgs;
typedef struct s_garbage	t_garbage;

typedef struct s_imgs
{
	void					*imgs;
	char					*ptr_east;
	char					*ptr_west;
	char					*ptr_north;
	char					*ptr_south;
	char					*east_texture;
	char					*west_texture;
	char					*north_texture;
	char					*south_texture;
	int						tex_x;
	int						x_start;
	int						x_end;
	int						draw_start;
	int						draw_end;
	int						bytes_per_pixel;
	double					tex_step;
}							t_imgs;

typedef struct s_pixel_data
{
	void					*img;
	char					*addr;
	unsigned char			*minimap;
	void					*ptr_minimap;
	void					*ptr_floor;
	void					*ptr_background;
	char					*background;
	char					*backgr_empty;
	int						play_pix_x;
	int						play_pix_y;
	int						size_len;
	int						size_len_background;
	int						bpp;
	int						bpp_background;
	int						floor_color;
	int						ceiling_color;
	int						endian;
	int						line_len;
	int						bit_pixels;
}							t_pixel_data;

typedef struct s_player
{
	double					x_pos;
	double					y_pos;
	float					facing_pos;
}							t_player;

typedef struct s_ray
{
	double					ray_len_hit;
	double					ray_lenx_hit;
	double					ray_leny_hit;
	double					x_hit;
	double					y_hit;
	int						dda;
	double					rad;
	double					player_pos_x;
	double					player_pos_y;
	double					ray_rad_x;
	double					ray_rad_y;
	int						move_spot_x;
	int						move_spot_y;
	double					delta_x;
	double					delta_y;
	double					dist_line_x;
	double					dist_line_y;
	int						step_x;
	int						step_y;

}							t_ray;

typedef struct s_cubed
{
	char					**map;
	char					**cpy_map;
	char					**map_formated;
	int						spwn_x;
	int						spwn_y;
	int						max_wid;
	int						max_hei;
	int						start_map;
	int						wall_orientation;
	int						prev_color;
	long					keys[70000];
	void					*mlx;
	void					*win;
	t_imgs					*imgs;
	t_garbage				*garbage;
	t_pixel_data			*pixel_data;
	t_player				*player;
	t_ray					*ray;
}							t_cubed;

// Name Texture
int							stack_name_txt(t_cubed *cubed);

// Map
char						**split_map(char *path);

// Init
int							init_mlx(t_cubed *cubed);
int							init_string_textures(t_imgs *imgs);
void						check_max(int i, t_cubed *cube);
void						cleanup_textures(t_cubed *cubed);

// Input
int							esc_close(int keycode, t_cubed *cubed);
int							loop_handler(t_cubed *cubed);
int							key_press(int keycode, t_cubed *cubed);
int							key_release(int keycode, t_cubed *cubed);

// Garbadge
int							free_all(t_cubed *cubed);
void						free_imgs_error_pars(t_cubed *cubed);
void						free_imgs(t_cubed *cubed);
void						free_textures(t_imgs *imgs);
void						destroy_textures(t_cubed *cubed);
void						free_texture_names(t_imgs *imgs);

// Parsing
int							error_parsing(t_cubed *cubed);
int							parsing_textures(t_cubed *cubed);
int							check_flood_fill(t_cubed *cubed);
int							parsing_nbr_colors(t_cubed *cubed);

// Utils Parsing
int							check_looong(char *str);
int							is_map_line(const char *line);
int							validate_rgb_value(int value);
int							ends_with_xpm(const char *filename);
int							parsing_floor_color(t_pixel_data *pixel_data,
								char *line);
int							parsing_ceiling_color(t_pixel_data *pixel_data,
								char *line);
int							parse_rgb(char *line, int *r, int *g, int *b);
int							copy_line(char **dest, char *src, int max_wid);
void						start_map(t_cubed *cubed);
int							init_colors(t_cubed *cubed);
int							check_size_map(t_cubed *cubed);

// Display
int							display_floor_ceiling(t_cubed cube);
// Minimap
int							minimap(t_cubed *cube);

// Map_formated
int							format_map(t_cubed *cube);
// Map_formated_utils
int							is_player_pos(char c);
int							is_valid_char(char c);
// Utils
int							is_whitespace(char c);
int							is_map(t_cubed *cube, int i);
int							is_white_line(char *str);
int							is_line_empty(char *content, int start, int end);
// Colors
int							color_convert(int colour, int name_colour);
void						wall_colour(int x, int y, t_cubed *cube);
void						walk_colour(int x, int y, t_cubed *cube);
void						player_colour(int x, int y, t_cubed *cube);
// Clicks
void						change_pix(t_cubed *cube, int colour);
void						pix_colour(double ray_x, double ray_y, int colour,
								t_cubed *cube);
void						move_player_forward(t_cubed *cube);
void						move_player_side(t_cubed *cube, int dir);
void						move_player_backward(t_cubed *cube);
int							key_press(int keycode, t_cubed *cubed);
int							key_release(int keycode, t_cubed *cubed);
// OTHER
int							ray_vision(t_cubed *cube);
void						dda(t_cubed *cube);
// Ray_casting
int							orientation_color(t_cubed *cube);
int							angle_correction(float angle);
int							get_texture_pixel(char *texture, int tex_x,
								int tex_y, int tex_width);
char						*get_wall_texture(t_cubed *cube);
void						put_texture(t_cubed *cube, char *texture, int tex_x,
								double tex_pos);
#endif