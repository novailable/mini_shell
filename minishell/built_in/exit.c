/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:28:37 by aoo               #+#    #+#             */
/*   Updated: 2025/03/16 20:29:06 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_sign(const char *nptr, int *sign)
{
	*sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			*sign = -1;
		return (1);
	}
	return (0);
}

bool	ft_atoll_vali_ok(const char *nptr, long long *result)
{
	long long	i;
	int			sign;

	i = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	nptr += change_sign(nptr, &sign);
	if (!*nptr)
		return (false);
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (i > LLONG_MAX / 10 || (i == LLONG_MAX / 10 && \
			(*nptr - '0') > LLONG_MAX % 10 + (sign == -1)))
			return (false);
		i = i * 10 + (*(nptr++) - '0');
	}
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr != '\0')
		return (false);
	return (*result = i * sign, true);
}

int	get_exit_status(char *args, t_core *core, int *numeric)
{
	long long	num;

	if (args)
	{
		if (!ft_atoll_vali_ok(args, &num))
		{
			print_err_msg("exit: ", args, ": numeric argument required\n");
			core->status = 2;
			*numeric = 0;
			return (2);
		}
		else
			return (*numeric = 1, (unsigned int) num % 256);
	}
	*numeric = 1;
	return (core->status);
}

int	ft_exit(char **args, int *org_fd, t_core *core)
{
	unsigned int	status;
	int				size;
	int				numeric;

	args++;
	size = 0;
	while (args[size])
		size++;
	status = get_exit_status(*args, core, &numeric);
	if (core->single_time)
	{
		ft_putstr_fd("exit\n", 2);
		if (numeric && size > 1)
			return (print_err_msg("too many arguments\n", NULL, NULL), 1);
		reset_close_fd(org_fd, 1, 1);
		free_core(core);
		exit(status);
	}
	if (numeric && size > 1)
	{
		print_err_msg("minishell : too many arguments\n", NULL, NULL);
		status = 1;
	}
	return (status);
}
