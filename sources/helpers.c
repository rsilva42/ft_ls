/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 01:03:30 by rsilva            #+#    #+#             */
/*   Updated: 2018/07/25 01:08:34 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void	ft_putwnl(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	write(1, "\n", 1);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		c;
	char	*ret;

	i = 0;
	c = 0;
	while (!src[i])
		i++;
	if (!(ret = (char*)malloc(sizeof(src) * i)))
		return (NULL);
	while (c < i)
	{
		ret[c] = src[c];
		c++;
	}
	ret[c] = '\0';
	return (ret);
}

void	*ft_memalloc(size_t size)
{
	void	*alloc;
	size_t	i;

	i = 0;
	alloc = malloc((sizeof(size)) * size);
	if (!alloc)
		return (NULL);
	while (i < size)
	{
		((unsigned char *)alloc)[i] = '\0';
		i++;
	}
	return (alloc);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
