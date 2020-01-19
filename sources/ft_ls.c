/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:39:42 by rsilva            #+#    #+#             */
/*   Updated: 2018/07/23 14:03:58 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_recurse_ls(t_file *fileptr, unsigned int *flags, char *arg)
{
	char		*path;

	if (*flags & FLAG_SIMPL)
	{
		*flags = *flags ^ FLAG_SIMPL;
		write(1, "\n", 1);
	}
	while (fileptr)
	{
		if ((fileptr->name[0] != '.') || *flags & FLAG_LIL_A)
		{
			path = ft_pathjoin(arg, fileptr->name);
			if (ft_strcmp(fileptr->name, ".") &&
				ft_strcmp(fileptr->name, "..") && ft_isdir(path))
				ft_arg_ls(path, *flags);
			if ((fileptr->name[0] != '.') || *flags & FLAG_LIL_A)
				free(path);
		}
		fileptr = fileptr->next;
	}
}

void	ft_simple_ls(unsigned int flags)
{
	DIR			*dir;
	t_file		*fileptr;
	t_file		*files;

	dir = opendir(".");
	files = populate_files(dir, ".");
	print_files(files, flags);
	fileptr = files->next;
	if (flags & FLAG_BIG_R)
		ft_recurse_ls(fileptr, &flags, ".");
	free_but_it_gets_freer_every_time(files);
	closedir(dir);
}

int		ft_arg_ls(char *arg, unsigned int flags)
{
	DIR			*currdir;
	t_file		*fileptr;
	t_file		*files;

	if (ft_isdir(arg))
	{
		if (!(currdir = opendir(arg)))
			return (ft_error(3, arg));
		files = populate_files(currdir, arg);
		if (!(flags & FLAG_SIMPL))
			ft_putfilename(arg, flags);
		print_files(files, flags);
		fileptr = files->next;
		if (flags & FLAG_BIG_R)
			ft_recurse_ls(fileptr, &flags, arg);
		free_but_it_gets_freer_every_time(files);
		closedir(currdir);
	}
	else
		ft_isfile(arg) == -1 ? ft_error(1, arg) : ft_putwnl(arg);
	return (0);
}

void	ft_ls(char **av, unsigned int flags)
{
	int		i;

	if (!av[0])
		ft_simple_ls(flags);
	else if (!av[1] && (i = ft_isfile(av[0])))
		i == -1 ? ft_error(1, av[0]) : ft_putwnl(av[0]);
	else
	{
		i = 0;
		while (av[i])
		{
			ft_arg_ls(av[i], flags);
			i++;
		}
	}
}

int		main(int ac, char **av)
{
	int				i;
	unsigned int	flags;

	i = 1;
	flags = check_flags(ac, av, &i);
	ft_ls(&av[i], flags);
	return (EXIT_SUCCESS);
}
