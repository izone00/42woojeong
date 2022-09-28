#include "fdf.h"

int key_hook(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_clear_window(mlx_ptr, win_ptr);
		mlx_destroy_window(mlx_ptr, win_ptr);
		exit(0);
	}
	return (1);
}