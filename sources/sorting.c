/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:33:11 by rsilva            #+#    #+#             */
/*   Updated: 2018/08/08 20:33:17 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putfilename(char *name, int flags)
{
	(void)flags;
	if (ft_isdir(name))
	{
		write(1, name, ft_strlen(name));
		write(1, ":\n", 2);
	}
	else
		ft_putwnl(name);
}

t_file	*merge_files(t_file *front, t_file *back, int flags)
{
	t_file	*ret;
	int		i;

	if (!front)
		return (back);
	else if (!back)
		return (front);
	if (flags & FLAG_LIL_T)
		i = back->modtime - front->modtime;
	else
		i = ft_strcmp(front->name, back->name);
	if (front->name[0] == 0 || (i <= 0 && !(flags & FLAG_LIL_R))
		|| (i >= 0 && (flags & FLAG_LIL_R)))
	{
		ret = front;
		ret->next = merge_files(front->next, back, flags);
		return (ret);
	}
	ret = back;
	ret->next = merge_files(front, back->next, flags);
	return (ret);
}

void	split_files(t_file *head, t_file **front, t_file **back)
{
	t_file	*end;
	t_file	*half;

	half = head;
	end = head->next;
	while (end)
	{
		end = end->next;
		if (end)
		{
			half = half->next;
			end = end->next;
		}
	}
	*front = head;
	*back = half->next;
	half->next = NULL;
}

void	sort_files(t_file **files, int flags)
{
	t_file	*head;
	t_file	*front;
	t_file	*back;

	head = *files;
	if (!head || !head->next)
		return ;
	split_files(head, &front, &back);
	sort_files(&front, flags);
	sort_files(&back, flags);
	*files = merge_files(front, back, flags);
}
