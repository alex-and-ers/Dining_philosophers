/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:11:52 by aserebry          #+#    #+#             */
/*   Updated: 2024/01/26 16:45:33 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	long long		result;
	int				sign;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i++] - '0';
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483648 && sign == -1)
			return (0);
	}
	return (result * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

int	err_exit(char err_code)
{
	if (err_code == 'a')
		err_msg("The program uses 4 or 5 args!");
	else if (err_code == 'b')
		err_msg("Incorrect args!");
	else if (err_code == 'm')
		err_msg("Malloc error!");
	else if (err_code == 'c')
		err_msg("Thread create error!");
	else if (err_code == 'd')
		err_msg("Thread detach error!");
	else if (err_code == 'x')
		err_msg("Mutex init error!");
	else if (err_code == 'p')
		err_msg("Philosopher creation error!");
	return (1);
}
