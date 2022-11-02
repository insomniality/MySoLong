/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikarzum <mikarzum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:46:22 by mikarzum          #+#    #+#             */
/*   Updated: 2022/11/03 01:13:01 by mikarzum         ###   ########.fr       */
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
int		mv = 0;

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

char	*ft_strnstr(char *str, char *to_find, int len)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] && len != 0 && (int)i < len)
	{
		j = 0;
		while (to_find[j] && str[i + j] && !(&str[len] == &str[i + j]))
		{
			if (to_find[j] != str[i + j])
				break ;
			j++;
		}
		i++;
		if (to_find[j])
			continue ;
		else if (to_find[j] == '\0')
			return ((char *)str + i - 1);
		len--;
	}
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i + 1);
}

int	ft_mtrxlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	cords1(char **mtrx, char find, int xoy) // starting point is (0,0)
{
	int		erk;
	int		brdz;
	int		i;

	erk = ft_strlen(mtrx[0]) - 1;
	brdz = ft_mtrxlen(mtrx);
	// printf("BB => %i;EE => %i\n", brdz, erk);
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
	{
		printf("There is no '%c' on the map\n", find);
		return (-1);
	}
	if (xoy == 0)
		return (i % erk);	
	return (i / erk);
}

char	**map_matrix(void) // "\n"-er@ chi dnum matrixi mej
{
	char	**mx;
	int		fd;
	char	ch[1];
	int		erk;
	int		brdz;
	int		oldE;
	int		oldB;
	int		p_f;
	
	p_f	= 0;
	oldE = 0;
	erk = 0;
	brdz = 1;
	fd = open(argvv[1], O_RDONLY);
	while (read(fd, &ch[0], 1) == 1)
	{
		// printf("o =  %i; n = %i\n", oldE, erk);
		if (ch[0] == '\n')
		{
			printf("UwU\n");
			brdz += 1;
			if (oldE != 0 && oldE != erk)
			{
				printf("Err; Map is not rectangular; o =  %i; n = %i\n", oldE, erk);
				exit(1);
			}
			oldE = erk;
			erk = 0;
			continue ; // CRITICAL!!!!!!!!!!!----------MIGHT BREAK EVERYTHING IF NOT COMMENTED
		}
		erk++;
	}
	if (oldE != 0 && oldE != erk)
	{
		printf("Err; Map is not rectangular\n");
		exit(1);
	}
	close(fd); // arandzin funkcia sarqi sra hamar
	erk--;
	mx = (char**)malloc(sizeof(char*) * brdz + 1);
	mx[brdz] = NULL;
	fd = open(argvv[1], O_RDONLY);
	oldB = brdz;
	while (brdz > 0)
	{
		mx[brdz - 1] = (char*)malloc(sizeof(char) * erk + 1);
		brdz--;
	}
	erk = 0;
	while (read(fd, &mx[brdz][erk], 1) == 1) // MIAT NORM@ 100%-v stugi !!!!!!!!!!!!! // karas arandzin funcia anes
	{
		// printf("owo; b%i e%i\n", brdz, erk);
		if (mx[brdz][erk] == '\n' /*+ 0 * (erk++)*/)
		{
			brdz += 1 /* + 0 * ((erk = 0) + (mx[brdz][erk] = '\0'))*/;
			mx[brdz][erk] = '\0';
			erk = 0;
			continue ;
		}
		if (mx[brdz][erk] != '0' && mx[brdz][erk] != '1' && mx[brdz][erk] != 'C' && mx[brdz][erk] != 'E' && mx[brdz][erk] != 'P')
		{
			printf("Error\nUnidentified sprite --> %c\n", mx[brdz][erk]);
			exit(1);
		}
		if ( (brdz == 0 || brdz == (oldB - 1) || erk == 0 || erk == (oldE - 1)) && mx[brdz][erk] != '1')
		{
			printf("Err; Corners are not walls");
			exit(1);
		}
		erk++;
	}
	close(fd);
	if (cords1(mx, 'C', 0) != -1 && cords1(mx, 'E', 0) != -1 && cords1(mx, 'P', 0) != -1)
	{
		brdz = cords1(mx, 'P', 1);
		erk = cords1(mx, 'P', 0);
		mx[brdz][erk] = '0';
		if(cords1(mx, 'P', 0) == -1)
			mx[brdz][erk] = 'P';
		else
		{
			printf("Err; Only 1 'P' can be on map\n");
			exit(1);
		}
	}
	else
	{
		printf("Err; At least 1 'C' or 'E' and only 1 'P' can be on map\n");
		exit(1);
	}
	return (mx);
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

char **map_changer(char **mtrx, int xp, int yp, int key)
{
	if (key == 123 && xp != 0 && mtrx[yp][xp - 1] != '1') // <
	{
		if (mtrx[yp][xp - 1] == 'E' && cords1(mtrx, 'C', 0) == -1)
			exit(1);
		else if (mtrx[yp][xp - 1] == 'E')
			return (mtrx);
		mtrx[yp][xp - 1] = 'P';
		mtrx[yp][xp] = '0';
	}
	else if (key == 124 && xp != (ft_strlen(mtrx[yp]) - 1) && mtrx[yp][xp + 1] != '1')  // > //MIHAT \n-i moment@ ushadir exi
	{
		if (mtrx[yp][xp + 1] == 'E' && cords1(mtrx, 'C', 0) == -1)
			exit(1);
		else if (mtrx[yp][xp + 1] == 'E')
			return (mtrx);
		mtrx[yp][xp + 1] = 'P';
		mtrx[yp][xp] = '0';
	}
	else if (key == 125 && yp != (ft_strlen((char*)mtrx) - 1) && mtrx[yp + 1][xp] != '1')  // v
	{
		if (mtrx[yp + 1][xp] == 'E' && cords1(mtrx, 'C', 0) == -1)
			exit(1);
		else if (mtrx[yp + 1][xp] == 'E')
			return (mtrx);
		mtrx[yp + 1][xp] = 'P';
		mtrx[yp][xp] = '0';
	}
	else if (key == 126 && yp != 0 && mtrx[yp - 1][xp] != '1')  // ^
	{
		if (mtrx[yp - 1][xp] == 'E' && cords1(mtrx, 'C', 0) == -1)
			exit(1);
		else if (mtrx[yp - 1][xp] == 'E')
			return (mtrx);
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
		matrix = map_changer(matrix, cords1(matrix, 'P', 0), cords1(matrix, 'P', 1), key);
		mlx_clear_window(mlx, wdp);
		painter(matrix);
		mv++; //assuming you can walk on the wall
		// printf("X,Y -> %i,%i \n", cords1(matrix, 'P', 0), cords1(matrix, 'P', 1));
	}
	param += 0;
	printf("%d %d\n", key, mv);
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

int zZ(void *param)
{
	printf("NyaaaOWO\n");
	exit(1);
}

int	main(int argc, char **argv)
{
	// int						i;
	// int						ecord;
	// printf("--------%i\n", aas);
	int aas = ft_strlen(argv[1]) - 1;
	
	if (argc != 2)
	{
		printf("ErRor");
		return (0);
	}
	if (ft_strlen(argv[1]) - 1 >= 4)
	{
		if (ft_strnstr(&argv[1][aas - 1 - 3], ".ber", 4) != &argv[1][aas - 1 - 3])
		{
			printf("Wrong map file name\n");
			exit (1);
		} // gri tup@ verjic hertov stugi
	}
	argvv = argv;
	matrix = map_matrix();
	if(cords1(matrix, 'P', 0) == -1)
		exit (1);
	printf("Hay\n");
	mlx = mlx_init();
	imgP = mlx_xpm_file_to_image(mlx, "player.xpm", &a, &b);
	wdp = mlx_new_window(mlx, map_size(argv[1], 0) * a, map_size(argv[1], 1) * b, "Ma Game");
	imgE = mlx_xpm_file_to_image(mlx, "exit.xpm", &a, &b);
	img0 = mlx_xpm_file_to_image(mlx, "o_empty.xpm", &a, &b);
	img1 = mlx_xpm_file_to_image(mlx, "wall.xpm", &a, &b);
	imgC = mlx_xpm_file_to_image(mlx, "collectable.xpm", &a, &b);
	x = 0;
	y = 0;
	
	painter(matrix);
	// printf("Hay\n");
	// printf("X,Y -> %i,%i \n", cords1(matrix, 'P', 0), cords1(matrix, 'P', 1));
	// printf("Hay2\n");
	/**/
	// if (!img)
	// {
	// 	perror("");
	// 	exit (1);
	// }
	// mlx_put_image_to_window(mlx, wdp, img, a, b);
	
	mlx_key_hook(wdp, key_hook, &wdp);
	mlx_mouse_hook(wdp, m, NULL);
	// mlx_expose_hook(wdp, z, NULL);
	mlx_hook(wdp, 17, 0, zZ, NULL);

	// mlx_key_hook ( void *win_ptr, &exit, &z);
	// mlx_hook(wdp, 17, int x_mask, int (*f)(), void *param)
	mlx_loop(mlx);
}


// 0 0 1 0 0