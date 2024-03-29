/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:06:32 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/20 21:45:34 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	return (('0' <= *str) && (*str <= '9'));
}

size_t	ft_atoul_check_range(char *str)
{
	size_t	return_num;

	return_num = 0;
	while (*str)
	{
		if (!is_digit(str))
			return (ERROR);
		return_num *= 10;
		return_num += (*str - '0');
		if (return_num > INT_MAX)
			return (ERROR);
		str++;
	}
	if (return_num == 0)
		return (ERROR);
	else
		return (return_num);
}

int	ft_error(void)
{
	write(2, "ERROR\n", 6);
	return (ERROR);
}

size_t	get_cur_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return (s_time.tv_sec * 1000 + s_time.tv_usec / 1000);
}
