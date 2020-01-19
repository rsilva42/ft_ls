/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_longformat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 19:12:24 by rsilva            #+#    #+#             */
/*   Updated: 2018/09/22 19:12:35 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_put_total(t_file *head, int flags, int *maxlnk, int *maxsize)
{
	t_file			*ptr;
	unsigned int	total;

	ptr = head;
	total = 0;
	while (ptr)
	{
		if (ptr->name[0] != '.' || flags & FLAG_LIL_A)
		{
			total += ptr->blocks;
			if (ft_uintlen(ptr->links) > *maxlnk)
				*maxlnk = ft_uintlen(ptr->links);
			if (ft_uintlen(ptr->size) > *maxsize)
				*maxsize = ft_uintlen(ptr->size);
		}
		ptr = ptr->next;
	}
	write(1, "total ", 6);
	ft_putunbr(total);
	write(1, "\n", 1);
}

void			ft_putfile_typ_per(mode_t mode)
{
	if (S_ISDIR(mode))
		write(1, "d", 1);
	else if (S_ISLNK(mode) || S_ISFIFO(mode))
		S_ISLNK(mode) ? write(1, "l", 1) : write(1, "p", 1);
	else
		write(1, "-", 1);
	mode & S_IRUSR ? write(1, "r", 1) : write(1, "-", 1);
	mode & S_IWUSR ? write(1, "w", 1) : write(1, "-", 1);
	if (mode & S_ISUID)
		mode & S_IXUSR ? write(1, "s", 1) : write(1, "S", 1);
	else
		mode & S_IXUSR ? write(1, "x", 1) : write(1, "-", 1);
	mode & S_IRGRP ? write(1, "r", 1) : write(1, "-", 1);
	mode & S_IWGRP ? write(1, "w", 1) : write(1, "-", 1);
	if (mode & S_ISGID)
		mode & S_IXGRP ? write(1, "s", 1) : write(1, "S", 1);
	else
		mode & S_IXGRP ? write(1, "x", 1) : write(1, "-", 1);
	mode & S_IROTH ? write(1, "r", 1) : write(1, "-", 1);
	mode & S_IWOTH ? write(1, "w", 1) : write(1, "-", 1);
	if (mode & S_ISVTX)
		mode & S_IXOTH ? write(1, "t ", 2) : write(1, "T ", 2);
	else
		mode & S_IXOTH ? write(1, "x ", 2) : write(1, "- ", 2);
}

void			ft_putlnk_ids(t_file *file, int maxlnk)
{
	t_passwd	owinfo;
	t_group		group;

	owinfo = *getpwuid(file->owner);
	group = *getgrgid(file->owgroup);
	write(1, "             ", 1 + maxlnk - ft_uintlen(file->links));
	ft_putunbr(file->links);
	write(1, " ", 1);
	write(1, owinfo.pw_name, ft_strlen(owinfo.pw_name));
	write(1, "  ", 2);
	write(1, group.gr_name, ft_strlen(group.gr_name));
	write(1, " ", 1);
}

void			ft_putsize_date(t_file *file, int maxsize)
{
	char	*ftime;

	ftime = ctime(&file->modtime);
	write(1, "             ", 1 + maxsize - ft_uintlen(file->size));
	ft_putunbr(file->size);
	if (file->modtime > time(NULL) - 15552000)
		write(1, &ftime[3], 13);
	else
	{
		write(1, &ftime[3], 8);
		write(1, &ftime[20], 4);
	}
	write(1, " ", 1);
}

void			print_longformat(t_file *files, int flags)
{
	t_file	*fileptr;
	int		maxlnk;
	int		maxsize;

	maxlnk = 0;
	maxsize = 0;
	fileptr = files->next;
	ft_put_total(files, flags, &maxlnk, &maxsize);
	while (fileptr)
	{
		if (fileptr->name[0] && (fileptr->name[0] != '.' || flags & FLAG_LIL_A))
		{
			ft_putfile_typ_per(fileptr->mode);
			ft_putlnk_ids(fileptr, maxlnk);
			ft_putsize_date(fileptr, maxsize);
			ft_putstr(fileptr->name);
			if (S_ISLNK(fileptr->mode))
				ft_putlink(fileptr->path);
			write(1, "\n", 1);
		}
		fileptr = fileptr->next;
	}
}
