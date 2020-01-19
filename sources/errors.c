/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:30:38 by rsilva            #+#    #+#             */
/*   Updated: 2018/09/16 15:32:11 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_error(unsigned char e, char *arg)
{
	if (!e)
	{
		write(STDERR_FILENO,
			"illegal option\nusage: ./ft_ls [-Rlart] [file ...]\n", 50);
		exit(EXIT_FAILURE);
	}
	else if (e == 1)
	{
		write(STDERR_FILENO, "ft_ls: ", 7);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
	else if (e == 2)
	{
		write(STDERR_FILENO, "malloc failure\n", 15);
		exit(EXIT_FAILURE);
	}
	else if (e == 3)
	{
		write(STDERR_FILENO, "ft_ls: ", 7);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
	return (EXIT_FAILURE);
}

char	*ft_pathcat(char *s1, const char *s2)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (ft_strcmp(s1, "/"))
	{
		while (s1[a])
			a++;
		s1[a] = '/';
	}
	a++;
	while (s2[b])
	{
		s1[a] = s2[b];
		a++;
		b++;
	}
	s1[a] = '\0';
	return (s1);
}

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!(s3 = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	ft_strcpy(s3, s1);
	ft_pathcat(s3, s2);
	return (s3);
}

void	ft_putlink(char *path)
{
	char buf[256];

	readlink(path, buf, 255);
	ft_putstr(" -> ");
	ft_putstr(buf);
}
