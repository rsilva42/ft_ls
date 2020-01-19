/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 16:16:19 by rsilva            #+#    #+#             */
/*   Updated: 2018/09/17 16:16:58 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				add_flags(char *arg)
{
	int		i;
	int		flags;

	i = 1;
	flags = 0;
	while (arg[i])
	{
		if (arg[i] == 't')
			flags = flags | FLAG_LIL_T;
		else if (arg[i] == 'r')
			flags = flags | FLAG_LIL_R;
		else if (arg[i] == 'a')
			flags = flags | FLAG_LIL_A;
		else if (arg[i] == 'l')
			flags = flags | FLAG_LIL_L;
		else if (arg[i] == 'R')
			flags = flags | FLAG_BIG_R;
		else
			ft_error(0, 0);
		i++;
	}
	if (i <= 1)
		ft_error(0, 0);
	return (flags);
}

unsigned int	check_flags(int ac, char **av, int *i)
{
	int		flags;

	flags = 0;
	if (!av[*i])
		return (FLAG_SIMPL);
	while (av[*i] && av[*i][0] == '-')
	{
		flags = flags | add_flags(av[*i]);
		if (flags & FLAG_ERROR)
			return (-1);
		*i = *i + 1;
	}
	if ((ac - *i) <= 1)
		flags = flags | FLAG_SIMPL;
	return (flags);
}
