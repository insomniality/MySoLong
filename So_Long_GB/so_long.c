/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikarzum <mikarzum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:46:22 by mikarzum          #+#    #+#             */
/*   Updated: 2022/10/18 18:20:37 by mikarzum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>

//ete E (and ig similiar things) chka to error ta

void	*mlx;
void	*wdp;
void	*imgE;
void	*imgP;
void	*img0;
void	*img1;
void	*imgC;
int		a, b;
int		x, y;
int		xp, yp;

int	map_size(char *flnm, int flag)
{
	int		x;
	int		y;
	int		fd;
	char	ch[1];
	
	fd = open(flnm, O_RDONLY);
	x = 0;
	y = 1;
	while (read(fd, ch, 1) == 1)
	{
		if (ch[0] == '\n')
		{
			y++;
			x = 0;
			continue ;
		}
		x++;
	}
	close(fd);
	if (flag == 0)
		return (x);
	else if (flag == 1)
		return (y);
}

char	**map_matrix()
{
	char	**mx;
	int		fd;
	int		ch[1];
	int		erk;
	int		brdz;
	
	fd = open("map.ber", O_RDONLY) + 0 * ((erk = 0) + (brdz = 1));
	while (read(fd, &ch[0], 1) == 1)
		if (ch[0] == '\n' + 0 * (erk++))
			brdz += 1 + 0 * (erk = 0);
	close(fd); // arandzin funkcia sarqi sra hamar
	mx = (char**)malloc(sizeof(char*) * brdz);
	fd = open("map.ber", O_RDONLY);
	while (brdz < 1)
	{
		mx[brdz - 1] = (char*)malloc(sizeof(char) * erk + 1);
		mx[brdz-- - 1][erk] = '\0';
	}
	erk = 0;
	while (read(fd, &mx[brdz - 1][erk], 1) == 1)
		if (mx[brdz - 1][erk] == '\n' + 0 * (erk++))
			brdz += 1 + 0 * (erk = 0);
	close(fd);
	return (mx);
}

void painter(char *flnm)
{
	// printf("HELo\n");
	int	fd;
	int	ch[1];
	
	fd = open(flnm, O_RDONLY);
	while (read(fd, &ch[0], 1) == 1)
	{
		if (ch[0] != '\n' && ch[0] != '0' && ch[0] != '1' && ch[0] != 'C' && ch[0] != 'E' && ch[0] != 'P')
		{
			printf("Error");
			close(fd);
			exit (1);
		}

		if (ch[0] == '\n') //verjum vor continue chgrem, qanzi x-@ zroyanuma
		{
			y += b;
			x = 0;
			continue ;
		}
		if (ch[0] == '0')
			mlx_put_image_to_window(mlx, wdp, img0, x, y);
		if (ch[0] == '1')
			mlx_put_image_to_window(mlx, wdp, img1, x, y);
		if (ch[0] == 'C')
			mlx_put_image_to_window(mlx, wdp, imgC, x, y);
		if (ch[0] == 'E')
			mlx_put_image_to_window(mlx, wdp, imgE, x, y);
		if (ch[0] == 'P')
		{
			mlx_put_image_to_window(mlx, wdp, imgP, x, y);
			xp = x;
			yp = y;
		}
		x += a;
		// if (ch[0] == '\n') //verjum vor continue chgrem, qanzi x-@ zroyanuma
		// 	y += b + 0 * (x = 0);
	}
	x = xp;
	y = yp;
	close(fd);
}

int	cords1(char *flnm, char find)
{
	int		i;
	int		fd;
	char	ch[1];

	i = 0;
	fd = open(flnm, O_RDONLY);
	while (ch[0] == find)
	{
		read(fd, ch, 1) == 1;
		i++;
	}
	close(fd);
	return (i);
}

int	cords2(char *flnm, int x, int y)
{
	int		i;
	int		fd;
	int		xog;
	char	ch[1];
	

	i = 0;
	fd = open(flnm, O_RDONLY);
	while (read(fd, ch, 1) == 1 && (x != xog || y > 0)) // y might be +- 1 initially
	{
		if (ch[0] == '\n')
		{
			y--;
			x = 0;
			i++;
			continue ;
		}
		x++;
		i++;
	}
	close(fd);
	return (i);
}

int map_changer(char **mtrx, int xc, int yc, int key)
{
	//open (write_only)
	int	xp;
	int	yp;
	
	xp = cords1("map.ber", 'P');
	yp = cords1("map.ber", 'P');
	if (key == 123 /*&& x != 0*/) // <
	{
		// x -= a;
		xp -= EEEEEE;
	}
	if (key == 124 && x != 15 * a)  // >
		x += a;
	if (key == 125 && y != 7 * b)  // v
		y += b;
	if (key == 126 && y != 0)  // ^
		y -= b;
}

int key_hook(int key, void *param)
{
	if (key == 53)
		exit (1);
	if (key >= 123 && key <= 126)
	{
		if (key == 123 && x != 0) // <
			x -= a;
		if (key == 124 && x != 15 * a)  // >
			x += a;
		if (key == 125 && y != 7 * b)  // v
			y += b;
		if (key == 126 && y != 0)  // ^
			y -= b;
		
		esi vor lini logikan map_changer();
		mlx_clear_window(mlx, wdp);
		painter("map.ber");
		// mlx_put_image_to_window(mlx, wdp, imgE, x, y);
		// mlx_put_image_to_window(mlx, wdp, imgP, x, y);
	}
	printf("%d\n", key);
}

int m(int key, int xX, int yY, void *param)
{
	printf("%d %d %d\n", key, xX, yY);
}

int z(void *param)
{
	static int	i;

	i = 0;
	if(i == 1)
		exit(1);
	i++;
}

int	main(int argc, char **argv)
{
	// printf("line=%d\n", __LINE__); //
	// void	*mlx;
	// void	*wdp;
	// void	*img;
	// int		a, b;
	//int		fd;
	int		i;
	int		ecord;
	char	**mtrx;
	// int		qbsz = 270;
	//char	ch[1];
	
	mtrx = map_matrix();
	mlx = mlx_init();
	imgP = mlx_xpm_file_to_image(mlx, "player.xpm", &a, &b);
	wdp = mlx_new_window(mlx, map_size(argv[1], 0) * a, map_size(argv[1], 1) * b, "Ma Game");
	imgE = mlx_xpm_file_to_image(mlx, "exit.xpm", &a, &b);
	// ecord = cords1(argv[1], 'E'); //WHAT IF THERE ARE 2 EXITS??????
	// void	*img0 = mlx_xpm_file_to_image(mlx, "o_empty.xpm", &a, &b); // ira sepakan a-n u b-n sarqi  (the img dimenssions), kam el NULL ete petq chi
	img0 = mlx_xpm_file_to_image(mlx, "o_empty.xpm", &a, &b);
	// void	*img1 = mlx_xpm_file_to_image(mlx, "wall.xpm", &a, &b);
	img1 = mlx_xpm_file_to_image(mlx, "wall.xpm", &a, &b);
	// void	*imgC = mlx_xpm_file_to_image(mlx, "collectable.xpm", &a, &b);
	imgC = mlx_xpm_file_to_image(mlx, "collectable.xpm", &a, &b);
	// void	*imgE = mlx_xpm_file_to_image(mlx, "exit.xpm", &a, &b);
	// void	*imgP = mlx_xpm_file_to_image(mlx, "playstart.xpm", &a, &b);
	
	x = 0;
	y = 0;
	
///////////
	if (argc != 2)
	{
		printf("Error");
		return (0);
	}
	
	painter(argv[1]);
///////////////
	/**/
	// if (!img)
	// {
	// 	perror("");
	// 	exit (1);
	// }
	// mlx_put_image_to_window(mlx, wdp, img, a, b);
	
	mlx_key_hook(wdp, key_hook, &wdp);
	mlx_mouse_hook(wdp, m, NULL);
	mlx_expose_hook(wdp, z, NULL);
	// mlx_key_hook ( void *win_ptr, &exit, &z);
	// mlx_hook(wdp, 17, int x_mask, int (*f)(), void *param)
	
	mlx_loop(mlx);
}


// 0 0 1 0 0