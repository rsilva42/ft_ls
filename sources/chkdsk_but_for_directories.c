/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chkdsk_but_for_directories.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 17:10:54 by rsilva            #+#    #+#             */
/*   Updated: 2018/09/12 17:13:29 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_isdir(char *arg)
{
	t_stat dirchk;

	if (lstat(arg, &dirchk))
		return (0);
	if (!(S_ISDIR(dirchk.st_mode)))
		return (0);
	return (1);
}

char	ft_isfile(char *arg)
{
	t_stat filechk;

	if (lstat(arg, &filechk))
		return (-1);
	if (!(S_ISDIR(filechk.st_mode)))
		return (1);
	return (0);
}

t_file	*init_files(char *name, char *arg)
{
	t_file	*new;
	t_stat	fileinfo;

	if (!(new = (t_file *)ft_memalloc(sizeof(t_file))))
		ft_error(2, 0);
	if (name)
	{
		if (arg)
			new->path = ft_pathjoin(arg, name);
		else
			new->path = ft_pathjoin(".", name);
		ft_strcpy(new->name, name);
		if (lstat(new->path, &fileinfo) == -1)
			exit(ft_error(1, name));
		new->mode = fileinfo.st_mode;
		new->links = fileinfo.st_nlink;
		new->owner = fileinfo.st_uid;
		new->owgroup = fileinfo.st_gid;
		new->size = fileinfo.st_size;
		new->modtime = fileinfo.st_mtime;
		new->blocks = fileinfo.st_blocks;
	}
	return (new);
}

t_file	*populate_files(DIR *currdir, char *arg)
{
	t_dirent	*currfile;
	t_file		*fileptr;
	t_file		*files;

	files = init_files(NULL, NULL);
	fileptr = files;
	while ((currfile = readdir(currdir)))
	{
		fileptr->next = init_files(currfile->d_name, arg);
		fileptr = fileptr->next;
	}
	return (files);
}

void	print_files(t_file *head, int flags)
{
	t_file *files;

	sort_files(&head, flags);
	files = head;
	if (flags & FLAG_LIL_L)
		print_longformat(files, flags);
	else
		while (files)
		{
			if (files->name[0] && (files->name[0] != '.' || flags & FLAG_LIL_A))
				ft_putwnl(files->name);
			files = files->next;
		}
	if (!(flags & FLAG_SIMPL))
		write(1, "\n", 1);
}
