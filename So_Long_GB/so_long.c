/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikarzum <mikarzum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:46:22 by mikarzum          #+#    #+#             */
/*   Updated: 2022/11/01 00:45:27 by mikarzum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> 


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
char	**matrix;
char	**argvv;

int	map_size(char *flnm, int flag)
{
	int		xd;
	int		yd;
	int		fd;
	char	ch[1];
	
	fd = open(flnm, O_RDONLY);
	xd = 0;
	yd = 1;
	while (read(fd, ch, 1) == 1)
	{
		if (ch[0] == '\n')
		{
			yd++;
			xd = 0;
			continue ;
		}
		xd++;
	}
	close(fd);
	if (flag == 0)
		return (xd);
	else if (flag == 1)
		return (yd);
	return (-1);
}

char	**map_matrix() // "\n"-er@ chi dnum matrixi mej
{
	char	**mx;
	int		fd;
	char	ch[1];
	int		erk;
	int		brdz;
	
	fd = open("map.ber", O_RDONLY) + 0 * ((erk = 0) + (brdz = 1));
	while (read(fd, &ch[0], 1) == 1)
	{
		if (ch[0] == '\n')
		{
			brdz += 1;
			erk = 0;
		}
		erk++;
	}
	close(fd); // arandzin funkcia sarqi sra hamar
	erk--;
	mx = (char**)malloc(sizeof(char*) * brdz + 1);
	mx[brdz] = NULL;
	fd = open("map.ber", O_RDONLY);
	while (brdz > 0)
	{
		mx[brdz - 1] = (char*)malloc(sizeof(char) * erk + 1);
		brdz--;
	}
	erk = 0;
	while (read(fd, &mx[brdz][erk], 1) == 1) // MIAT NORM@ 100%-v stugi !!!!!!!!!!!!!
	{
		if (mx[brdz][erk] == '\n' /*+ 0 * (erk++)*/)
		{
			brdz += 1 /* + 0 * ((erk = 0) + (mx[brdz][erk] = '\0'))*/;
			mx[brdz][erk] = '\0';
			erk = 0;
			continue ;
		}
		erk++;
	}
	close(fd);
	return (mx);
}
/*
void painterOld(char *flnm)
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

*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_mtrxlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void painter(char **m)
{
	int	e;
	int	b;
	int	i;
	int j;
	
	j = 0;
	e = ft_strlen(m[0]) - 1;
	b = ft_mtrxlen(m);
	printf("Hallo ==> %i\n", b);
	i = 0;
	while (i < b * e) // nor strlen sarqi vor while-i mej \0-i tex@ voch mi ban chlini (tipo goyutun@ unenal chunenal@ menak stugi)
	{
		if (m[i / e][i % e] != '\0' && m[i / e][i % e] != '0' && m[i / e][i % e] != '1')
		{
			if (m[i / e][i % e] != 'C' && m[i / e][i % e] != 'E' && m[i / e][i % e] != 'P')
			{
				// printf("ErrorPainter --> I == %i; II == %i", i / e, i % e);
				exit(1);
			}
		}
		// printf("x => %i; y => %i; ch => %c\n", i / e, i % e, m[i / e][i % e]);
		// printf("Byeee %i\n", j++);
		// if (m[i / e][i % e] == '\0' && 1 * (i++)) //verjum vor continue chgrem, qanzi x-@ zroyanuma
		// 	break ;
		if (m[i / e][i % e] == '0')
			mlx_put_image_to_window(mlx, wdp, img0, i % e * 32, i / e  * 32);
		else if (m[i / e][i % e] == '1') // if er araj esli chto
			mlx_put_image_to_window(mlx, wdp, img1, i % e * 32, i / e  * 32);
		else if (m[i / e][i % e] == 'C')
			mlx_put_image_to_window(mlx, wdp, imgC, i % e * 32, i / e  * 32);
		else if (m[i / e][i % e] == 'E')
			mlx_put_image_to_window(mlx, wdp, imgE, i % e * 32, i / e  * 32);
		else if (m[i / e][i % e] == 'P')
			mlx_put_image_to_window(mlx, wdp, imgP, i % e * 32, i / e  * 32);
		i++;
	}
}

int	cords1(char **mtrx, char find, int xoy) // starting point is (0,0)
{
	int		erk;
	int		brdz;
	int		i;

	erk = ft_strlen(mtrx[0]) - 1;
	brdz = ft_mtrxlen(mtrx);
	printf("BB => %i;EE => %i\n", brdz, erk);
	i = 0;
	while (i < erk * brdz)
	{
		if (mtrx[i / erk][i % erk] == find)
			break ;
		if (mtrx[i / erk][i % erk] == '\n')
			brdz += 1 + 0 * (erk = 0);
		i++;
	}
	if (i == erk * brdz) // +- 1 ig; idk stugi
		printf("There is no Player on the map\n");
	if (xoy == 0)
		return (i % erk);	
	return (i / erk);
}

// int	cords2(char *flnm, int x, int y)
// {
// 	int		i;
// 	int		fd;
// 	int		xog;
// 	char	ch[1];
//
// 	i = 0;
// 	fd = open(flnm, O_RDONLY);
// 	while (read(fd, ch, 1) == 1 && (x != xog || y > 0)) // y might be +- 1 initially
// 	{
// 		if (ch[0] == '\n')
// 		{
// 			y--;
// 			x = 0;
// 			i++;
// 			continue ;
// 		}
// 		x++;
// 		i++;
// 	}
// 	close(fd);
// 	return (i);
// }

char **map_changer(char **mtrx, int xp, int yp, int key)
{
	if (key == 123 && xp != 0 && mtrx[yp][xp - 1] != '1') // <
	{
		if (mtrx[yp][xp - 1] == 'E')
			exit(1);
		mtrx[yp][xp - 1] = 'P';
		mtrx[yp][xp] = '0';
	}
	else if (key == 124 && xp != (ft_strlen(mtrx[yp]) - 1) && mtrx[yp][xp + 1] != '1')  // > //MIHAT \n-i moment@ ushadir exi
	{
		if (mtrx[yp][xp + 1] == 'E')
			exit(1);
		mtrx[yp][xp + 1] = 'P';
		mtrx[yp][xp] = '0';
	}
	else if (key == 125 && yp != (ft_strlen((char*)mtrx) - 1) && mtrx[yp + 1][xp] != '1')  // v
	{
		if (mtrx[yp + 1][xp] == 'E')
			exit(1);
		mtrx[yp + 1][xp] = 'P';
		mtrx[yp][xp] = '0';
	}
	else if (key == 126 && yp != 0 && mtrx[yp - 1][xp] != '1')  // ^
	{
		if (mtrx[yp - 1][xp] == 'E')
			exit(1);
		mtrx[yp - 1][xp] = 'P';
		mtrx[yp][xp] = '0';
	}
	return (mtrx);
}

int key_hook(int key, void *param)
{
	if (key == 53)
		exit (1);
	if (key >= 123 && key <= 126)
	{
		// if (key == 123 && x != 0) // <
		// 	x -= a;
		// if (key == 124 && x != 15 * a)  // >
		// 	x += a;
		// if (key == 125 && y != 7 * b)  // v
		// 	y += b;
		// if (key == 126 && y != 0)  // ^
		// 	y -= b;		
		matrix = map_changer(matrix, cords1(matrix, 'P', 0), cords1(matrix, 'P', 1), key);
		mlx_clear_window(mlx, wdp);
		painter(matrix);
		printf("X,Y -> %i,%i \n", cords1(matrix, 'P', 0), cords1(matrix, 'P', 1));
		// mlx_put_image_to_window(mlx, wdp, imgE, x, y);
		// mlx_put_image_to_window(mlx, wdp, imgP, x, y);
	}
	printf("%d\n", key);
	param += 0;
	return (0);
}

int m(int key, int xX, int yY, void *param)
{
	printf("%d %d %d\n", key, xX, yY);
	param += 0;
	return (0);
}

int z(void *param)
{
	static int	i;

	i = 0;
	if(i == 1)
		exit(1);
	i++;
	param += 0;
	return (0);
}

int	main(int argc, char **argv)
{
	// printf("line=%d\n", __LINE__); //
	// void	*mlx;
	// void	*wdp;
	// void	*img;
	// int		a, b;
	//int		fd;
	// int						i;
	// int						ecord;
	argvv = argv;
	// int		qbsz = 270;
	//char	ch[1];
	matrix = map_matrix();
	printf("Hay\n");
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
		printf("ErRor");
		return (0);
	}
	printf("Hay\n");
	
	painter(matrix);

	printf("X,Y -> %i,%i \n", cords1(matrix, 'P', 0), cords1(matrix, 'P', 1));
	
	printf("Hay2\n");

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