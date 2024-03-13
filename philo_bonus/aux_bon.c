/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:12:17 by aserebry          #+#    #+#             */
/*   Updated: 2024/01/27 13:27:42 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	err_msg(char *err)
{
	printf("\033[91mError!\n%s\033[0m\n", err);
	return (1);
}

long	actual_time(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	usleep_custom(long long time)
{
	long long	tmp;

	tmp = actual_time();
	while (actual_time() - tmp < time)
		usleep(100);
}

void	*monitor(void *base)
{
	t_base	*phil;

	phil = (t_base *)base;
	while (1)
	{
		if ((actual_time() - phil->meal_time) > (phil->ttd))
		{
			sem_wait(phil->sem);
			printf("%ld %d died\n", actual_time() - phil->time, phil->counter);
			exit (0);
		}
		usleep(1000);
	}
}

void	print_status(t_base *base, char type)
{
	long long	time;

	sem_wait(base->sem);
	time = actual_time() - base->time;
	printf("%lld %d", time, base->counter);
	if (type == 'e')
		printf(" is eating\n");
	if (type == 'f')
		printf(" has taken a fork\n");
	if (type == 't')
		printf(" is thinking\n");
	if (type == 's')
		printf(" is sleeping\n");
	sem_post(base->sem);
}
