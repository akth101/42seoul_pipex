/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:17:44 by seongjko          #+#    #+#             */
/*   Updated: 2023/03/19 16:17:45 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	letsgo_atoi(const char *str)
{
	long long	num;

	num = 0;
	while ('0' <= *str && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int				sign;
	long long		ans;
	unsigned char	*temp;

	sign = 1;
	temp = (unsigned char *)str;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (*str == '-' || *str == '+')
		return (0);
	ans = letsgo_atoi(str);
	return (ans * sign);
}
