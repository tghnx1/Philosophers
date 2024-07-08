/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:39:33 by mkokorev          #+#    #+#             */
/*   Updated: 2024/07/08 20:04:36 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

char	*ft_spaceskip(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	return ((char *)&nptr[i]);
}

int	ft_atoi(const char *nptr)
{
	long	i;
	long	integer;

	i = 0;
	nptr = ft_spaceskip(nptr);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	if (ft_isdigit (nptr[i]) == 0)
		return (0);
	integer = nptr[i] - 48;
	while (nptr[i + 1] != '\0' && ft_isdigit((int)nptr[i + 1]))
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			integer = integer * 10 + nptr[i + 1] - 48;
		else
			return (0);
		i++;
	}
	if (*nptr == '-')
		integer = -1 * integer;
	if (nptr[i] == ' ')
		return (0);
	return (integer);
}
