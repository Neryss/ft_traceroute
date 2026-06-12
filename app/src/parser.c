/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss <ckurt@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:56:01 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 13:56:02 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "params.h"
#include "error_exit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int	handle_solo_id(char *id, t_params *params)
{
	(void)params;
	if (!strcmp(id, "--help"))
	{
		print_help_menu();
		exit(0);
	}
	return (0);
}

char	*get_identifier(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '-')
		{
			count++;
			i++;
		}
		else
		{
			if (count > 2)
				return (NULL);
			return (&arg[i]);
		}
	}
	return (NULL);
}

bool	is_numeric(char *s)
{
	while (*s)
	{
		if (!isdigit(*s))
			return (1);
		s++;
	}
	return (0);
}

bool	is_float(char *s)
{
	int	dot_count;

	dot_count = 0;
	while (*s)
	{
		if (*s == '.')
		{
			if (dot_count < 1)
				dot_count++;
			else
				return (1);
		}
		else if (!isdigit(*s))
			return (1);
		s++;
	}
	return (0);
}

int	store_int_flag(char *value, int *var)
{
	if (!is_numeric(value))
	{
		*var = atoi(value);
		return (0);
	}
	error_exit(1, "invalid value: %s\n", value);
	return (1);
}

int	store_uint8_flag(char *value, uint8_t *var)
{
	int	tmp;

	tmp = 0;
	if (!is_numeric(value))
	{
		tmp = atoi(value);
		if (tmp > 255 || tmp < 0)
			error_exit(1, "option value too big: %d\n", tmp);
		*var = tmp;
		return (0);
	}
	error_exit(1, "invalid value: %s\n", value);
	return (1);
}

void	parse_i_float(char *pass, float *var)
{
	if (!is_float(pass))
		*var = atof(pass);
	else
		error_exit(1, "invalid value %s", pass);
}

static void	store_flags(char *id, char *pass, t_params *params)
{
	if (*id == 'm')
		store_uint8_flag(pass, &params->ttl);
	else if (*id == 'f')
		store_int_flag(pass, &params->hop_start);
	else if (*id == 'q')
		store_int_flag(pass, &params->probes_per_hop);
	else if (*id == 'z')
	  parse_i_float(pass, &params->interval);
	else if (!strcmp(id, "rdns"))
    params->rdns = true;
	else
		error_exit(1, "invalid option %s", id);
}

int	check_identifier(int *i_argc, char *id, char *value, t_params *params)
{
	char	*pass;
	int		ret;

	if (strlen(id) > 1 && strcmp(id, "help"))
	{
		pass = &id[1];
		ret = 0;
	}
	else
	{
		pass = value;
		ret = 1;
	}
	if (handle_solo_id(id, params))
		return (0);
	if (i_argc[0] == i_argc[1] - 1 && ret)
		error_exit(1, "missing argument\n");
	store_flags(id, pass, params);
	return (ret);
}

int	handle_dashes(int argc, char **argv, int i, t_params *params)
{
	char	*identifier;
	int		i_argc[2];

	identifier = NULL;
	identifier = get_identifier(argv[i]);
	if (!identifier)
	{
		if (!strcmp(argv[i], "--"))
			return (1);
		error_exit(1, "option \"%s\" requires an argument", argv[i]);
	}
	i_argc[0] = i;
	i_argc[1] = argc;
	return (check_identifier(i_argc, identifier, argv[i + 1], params));
}

void	parse_args(int argc, char **argv, t_params *params)
{
	int		i;

	i = 0;
	if (argc < 2)
	{
		print_help_menu();
		return ;
	}
	else
	{
		while (i++ < argc - 1)
		{
			if (argv[i][0] == '-')
			{
				if (handle_dashes(argc, argv, i, params))
					i++;
			}
			else
			{
				if (!params->host[0])
					memcpy(params->host, argv[i], sizeof(params->host));
				else
				{
					if (is_numeric(argv[i]))
						error_exit(1, "Cannot handle \"packetlen\" cmdline arg `%s` on position %d\n", argv[i], i);
					params->packet_size = atoi(argv[i]);
				}
			}
		}
	}
	if (!params->host[0])
		error_exit(1, "missing host operand");
}
