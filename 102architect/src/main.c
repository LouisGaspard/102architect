/*
** EPITECH PROJECT, 2017
** arch
** File description:
** arch
*/

#include "my.h"

int	is_num(char *str)
{
	int	a = 0;

	while (str[a]) {
		if ((str[a] >= '0' && str[a] <= '9') || str[a] == '-')
			a++;
		else
			return (-1);
	}
	return (1);
}

t_mat	*init_struct(int ac, char **av)
{
	t_mat	*mat;

	mat = malloc(sizeof(*mat));
	mat->ac = ac;
	mat->av = av;
	return (mat);
}

double	*trans(t_mat *mat, double *matrice, int a)
{
	double	Tx;
	double	Ty;

	Tx = atof(mat->av[a + 1]);
	Ty = atof(mat->av[a + 2]);
	matrice[2] = matrice[2] + Tx;
	matrice[5] = matrice[5] + Ty;
	printf("Translation by the vector (%.0f, %.0f)\n", Tx, Ty);
	mat->res[0] += Tx;
	mat->res[1] += Ty;
	return (mat->res);
}

double	*homo(t_mat *mat, double *matrice, int a)
{
	double	Hx;
	double	Hy;

	Hx = atof(mat->av[a + 1]);
	Hy = atof(mat->av[a + 2]);
	matrice[0] = matrice[0] * Hx;
	matrice[1] = matrice[1] * Hx;
	matrice[2] = matrice[2] * Hx;
	matrice[3] = matrice[3] * Hy;
	matrice[4] = matrice[4] * Hy;
	matrice[5] = matrice[5] * Hy;
	printf("Homothety by the ratios %.0f and %.0f\n", Hx, Hy);
	mat->res[0] += Hx;
	mat->res[1] += Hy;
	return (mat->res);
}

void	arch(t_mat *mat, double *matrice)
{
	int	a = 3;

	while (a != mat->ac) {
		if (mat->av[a][0] == '-' && mat->av[a][1] == 't' && mat->av[a][2] == '\0') {
			if (mat->av[a + 1] != '\0' && mat->av[a + 2] != '\0') {
				trans(mat, &matrice[0], a);
				a += 3;
			}
			else
				exit(84);
		}
		else if (mat->av[a][0] == '-' && mat->av[a][1] == 'h' && mat->av[a][2] == '\0') {
			if (mat->av[a + 1] != '\0' && mat->av[a + 2] != '\0') {
				homo(mat, &matrice[0], a);
				a += 3;
			}
			else
				exit(84);
		}
		else
			exit(84);
	}
}

int	is_option(char option)
{
	switch (option) {
	case 't':
		return (1);
	case 'h':
		return (1);
	case 'r':
		return (1);
	case 's':
		return (1);
	default:
		return (-1);
	}
	return (-1);
}

void	check_arg(t_mat *mat)
{
	int	a = 1;

	while (a != mat->ac) {
		if (is_num(mat->av[a]) == 1 ||
		    (mat->av[a][0] == '-' && is_option(mat->av[a][1]) == 1 && mat->av[a][2] == '\0'))
			a++;
		else
			exit(84);
	}
}

int	main(int ac, char **av)
{
	double	matrice[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
	t_mat	*mat;

	if (ac < 5)
		exit(84);
	mat = init_struct(ac, av);
	check_arg(mat);
	mat->res[0] = atof(av[1]);
	mat->res[1] = atof(av[2]);
	mat->res[2] = 1;
	arch(mat, matrice);
	int	x;
	int	y;

	x = 0;
	while (x < 9) {
		if (matrice[x] >= -0.5 && matrice[x] <= 0.5)
			printf("0.00");
		else
			printf("%.2f", matrice[x]);
		x++;
		if (x % 3 == 0)	{
			printf("\n");
			y++;
		}
		else
			printf("\t");
	}
	printf("(%s,%s) => (%.2f,%.2f)\n", mat->av[1], mat->av[2], mat->res[0], mat->res[1]);
}
