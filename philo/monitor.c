/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:11:33 by aserebry          #+#    #+#             */
/*   Updated: 2024/01/26 16:48:07 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor(t_phil *philo, t_base *base)
{
	int	i;

	usleep(100);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&base->meal_mut);
		if (base->meal_counter == base->nof)
			break ;
		pthread_mutex_unlock(&base->meal_mut);
		pthread_mutex_lock(&philo[i].get_time);
		if (((actual_time() - philo[i].tom) > base->ttd)
			&& philo[i].id != -1)
		{
			pthread_mutex_lock(&base->mut);
			printf("%lld %d %s\n", actual_time() - philo[i].start,
				philo[i].id, "died");
			break ;
		}
		pthread_mutex_unlock(&philo[i].get_time);
		i++;
		if (i == base->nof)
			i = 0;
	}
}

int	create_thread(t_base *base, t_phil *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].base->nof)
	{
		if (pthread_create(&philo[i].phil_thread, NULL,
				&phil_lifecycle, &philo[i]) != 0)
			return (err_exit('c'));
		i++;
	}
	monitor(philo, base);
	i = 0;
	while (i < philo[0].base->nof)
	{
		if (pthread_detach(philo[i].phil_thread))
			return (err_exit('d'));
		i++;
	}
	return (0);
}
