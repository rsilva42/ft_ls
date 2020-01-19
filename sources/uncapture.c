/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncapture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:40:44 by rsilva            #+#    #+#             */
/*   Updated: 2018/09/24 15:44:17 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_but_it_gets_freer_every_time(t_file *head)
{
	t_file	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->path);
		free(head);
		head = tmp;
	}
}
