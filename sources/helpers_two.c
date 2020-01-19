/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:09:50 by rsilva            #+#    #+#             */
/*   Updated: 2018/09/24 15:09:53 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_uintlen(unsigned long n)
{
	int len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void			ft_putunbr(unsigned long n)
{
	char val;

	val = n % 10 + 48;
	if (n / 10 > 0)
		ft_putunbr(n / 10);
	write(1, &val, 1);
}

void			ft_putwonl(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	write(1, s, i);
}

char			*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char			*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
