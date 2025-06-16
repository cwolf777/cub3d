
#include "cub3d.h"

static mlx_image_t	*create_img(t_cub3d *cub3d, mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;


	texture = mlx_load_png(path);
	if (!texture)
		handle_error(cub3d, "Failed to load texture");
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		handle_error(cub3d, "Failed to load image");
	return (image);
}

void	init_img(t_cub3d *cub3d, t_img *img, mlx_t *mlx, char *path)
{
	char *temp;

	temp = ft_strdup(path);
	if (!temp)
		handle_error(cub3d, "Allocation failed");
	if (!validate_file_extension(path, ".png"))
		handle_error(cub3d, "Wrong file extension must be .png");
	img->img = create_img(cub3d, mlx, path);
	img->path = temp;
}


