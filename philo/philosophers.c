/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:11:15 by aserebry          #+#    #+#             */
/*   Updated: 2024/01/26 16:45:10 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	symbol_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] == ' ' || (av[i][j] >= '0' && av[i][j] <= '9')))
				return (0);
			j++;
		}
	}
	return (1);
}

static t_base	*init_mutex_base(t_base *base)
{
	if (pthread_mutex_init(&base->mut, NULL))
	{
		free(base);
		return (NULL);
	}
	if (pthread_mutex_init(&base->meal_mut, NULL))
	{
		free(base);
		return (NULL);
	}
	return (base);
}

static int	check_atoi_result(int ac, char **av, t_base *base)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
		{
			free(base);
			return (1);
		}
		i++;
	}
	return (0);
}

static t_base	*init_base_struct(int ac, char **av)
{
	int		i;
	t_base	*res;

	i = 0;
	if (!symbol_check(ac, av))
		return (NULL);
	res = malloc(sizeof (t_base));
	if (!res)
		return (NULL);
	if (!init_mutex_base(res))
		return (NULL);
	if (check_atoi_result(ac, av, res) == 1)
		return (NULL);
	res->nof = ft_atoi(av[1]);
	res->ttd = ft_atoi(av[2]);
	res->tte = ft_atoi(av[3]);
	res->tts = ft_atoi(av[4]);
	res->nom = -1;
	res->meal_counter = 0;
	if (ac == 6)
		res->nom = ft_atoi(av[5]);
	return (res);
}

int	main(int ac, char **av)
{
	t_base		*base;
	t_phil		*phil;

	if (ac != 5 && ac != 6)
		return (err_exit('a'));
	base = init_base_struct(ac, av);
	if (!base)
		return (err_exit('b'));
	phil = create_phil(base);
	if (!phil)
		return (err_exit('p'));
	if (create_thread(base, phil))
	{
		if (base)
			free(base);
		if (phil)
			free(phil);
		return (err_exit('c'));
	}
	finish_all(phil);
	return (0);
}
