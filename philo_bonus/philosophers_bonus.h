/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:12:56 by aserebry          #+#    #+#             */
/*   Updated: 2024/01/29 12:53:57 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct timeval	t_timeval;

typedef struct s_base
{
	int		nof;
	int		ttd;
	int		tte;
	int		tts;
	int		nom;
	int		counter;
	int		pids[201];
	long	time;
	long	meal_time;
	sem_t	*fork;
	sem_t	*sem;
}	t_base;

int		err_msg(char *err);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);

long	actual_time(void);
void	usleep_custom(long long time);
void	print_status(t_base *base, char type);
void	*monitor(void *base);

void	main_process(t_base *base);
void	secondary_process(t_base *base);
void	create_phil(t_base *base);
void	init_semaphore(t_base *base, char type);

int		err_exit(t_base *base, char err_code);

#endif