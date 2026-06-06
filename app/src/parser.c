/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:44:56 by neryss            #+#    #+#             */
/*   Updated: 2026/06/05 18:57:55 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "params.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int	handle_solo_id(char *id, t_params *params)
{
  (void)params;
	if (strcmp(id, "--help"))
	{
		print_help_menu();
		exit(0);
	}
	// else if (*id == 'v')
	// 	return (flags->verbose = true);
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

static void	store_flags(char *id, char *pass, t_params *params)
{
	if (*id == 'm')
		store_int_flag(pass, params->ttl);
	else if (*id == 'f')
		store_int_flag(pass, params->hop_start);
	else if (*id == 'q')
		store_int_flag(pass, params->probes_per_hop);
	else if (*id == 'z')
		store_float_flag(pass, params->interval);
	else if (!strcmp(id, "rdns"))
    params->rdns = true;
	else
		error_exit(1, "invalid option %s", id);
}

int	check_identifier(int *i_argc, char *id, char *value, t_params *params)
{
	char	*pass;
	int		ret;

	if (strlen(id) > 1 && (strcmp(id, "ttl") | strcmp(id, "help")))
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
	return (check_identifier(i_argc, identifier, argv[i + 1], flags));
}

void	parse_args(int argc, char **argv, t_params *params)
{
	int		i;

	i = 0;
	// if (argc < 2)
	// 	error_exit(1, "missing host operand");
	// else
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
					params->packet_size = atoi(argv[i]);
			}
		}
	}
	// if (!params->host[0])
	// 	error_exit(1, "missing host operand");
}
