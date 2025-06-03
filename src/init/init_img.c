
#include "cub3d.h"

static mlx_image_t	*create_img(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;


	texture = mlx_load_png(path);
	if (!texture)
		handle_error("Failed to load texture");
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		handle_error("Failed to load image");
	return (image);
}

void	init_img(t_img *img, mlx_t *mlx, char *path)
{
	char *temp;

	temp = ft_strdup(path);
	if (!temp)
		handle_error("Allocation failed");
	if (!validate_file_extension(path, ".png"))
		handle_error("Wrong file extension must be .png");
	img->img = create_img(mlx, path);
	img->path = temp;
}