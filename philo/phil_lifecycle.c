/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:11:23 by aserebry          #+#    #+#             */
/*   Updated: 2024/01/26 16:37:06 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pass_out_forks(t_phil *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->rfork);
		print_status(philo, philo->start, 'f');
		pthread_mutex_lock(philo->lfork);
		print_status(philo, philo->start, 'f');
	}
	else
	{
		pthread_mutex_lock(philo->lfork);
		print_status(philo, philo->start, 'f');
		pthread_mutex_lock(&philo->rfork);
		print_status(philo, philo->start, 'f');
	}
	print_status(philo, philo->start, 'e');
	pthread_mutex_lock(&philo->get_time);
	philo->tom = actual_time();
	pthread_mutex_unlock(&philo->get_time);
	usleep_custom(philo->base->tte);
}

static int	unlock_forks_and_sleep(t_phil *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(&philo->rfork);
	}
	else
	{
		pthread_mutex_unlock(&philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
	philo->meals++;
	if (philo->meals == philo->base->nom)
	{
		pthread_mutex_lock(&philo->base->meal_mut);
		philo->id = -1;
		philo->base->meal_counter++;
		pthread_mutex_unlock(&philo->base->meal_mut);
		return (0);
	}
	print_status(philo, philo->start, 's');
	usleep_custom(philo->base->tts);
	usleep(200);
	print_status(philo, philo->start, 't');
	return (1);
}

void	*phil_lifecycle(void *phil)
{
	t_phil	*philo;

	philo = (t_phil *)phil;
	philo->start = actual_time();
	pthread_mutex_lock(&philo->get_time);
	philo->tom = philo->start;
	pthread_mutex_unlock(&philo->get_time);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pass_out_forks(philo);
		if (unlock_forks_and_sleep(philo) == 0)
			return (0);
	}
	return (0);
}

static int	mutex_init(t_phil *phil)
{
	if (pthread_mutex_init(&phil->rfork, NULL))
		return (1);
	if (pthread_mutex_init(&phil->get_time, NULL))
		return (1);
	return (0);
}

t_phil	*create_phil(t_base *base)
{
	int			i;
	t_phil		*phil;

	phil = malloc(sizeof(t_phil) * base->nof);
	if (!phil)
		return (NULL);
	i = -1;
	while (++i < base->nof)
	{
		phil[i].id = i + 1;
		if (mutex_init(&phil[i]))
		{
			free(phil);
			return (NULL);
		}
		phil[i].tom = 0;
		phil[i].base = base;
		phil[i].meals = 0;
	}
	i = 0;
	while (++i < base->nof)
		phil[i].lfork = &phil[i - 1].rfork;
	phil[0].lfork = &phil[i - 1].rfork;
	return (phil);
}
