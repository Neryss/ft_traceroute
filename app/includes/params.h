/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:15:41 by neryss            #+#    #+#             */
/*   Updated: 2026/06/05 18:19:03 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMS_H
# define PARAMS_H

# include <stdbool.h>
# include <stdint.h>
# include <arpa/inet.h>

typedef struct s_params
{
	char	host[INET_ADDRSTRLEN];
	int		packet_size;
	// -m set max number of hops (max TTL). Default is 30
	uint8_t	ttl;
	// -f starts from N hop instead of 1
	int		hop_start;
	// -q number of probes per hop, default is 3
	int		probes_per_hop;
	// -z minimal interval between each probe (default is 0)
	float	interval;
	// -rdns reverse dns resolution
	bool	rdns;
}			t_params;

void	init_flags(t_params *flags);
void	print_flags(t_params *flags);
void	print_help_menu(void);

#endif
