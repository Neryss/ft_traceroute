/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss <ckurt@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:56:18 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 17:02:02 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMS_H
# define PARAMS_H

#include <netdb.h>
# include <stdbool.h>
# include <stdint.h>
# include <arpa/inet.h>

typedef struct s_params
{
	char			host[NI_MAXHOST];
	struct addrinfo	*ip;
	char			rdns_str[NI_MAXHOST];
	int				packet_size;
	// -m set max number of hops (max TTL). Default is 30
	uint8_t			ttl;
	// -f starts from N hop instead of 1
	int				hop_start;
	// -q number of probes per hop, default is 3
	int				probes_per_hop;
	// -z minimal interval between each probe (default is 0)
	float			interval;
	// -rdns reverse dns resolution
	bool			rdns;
}			t_params;

void	init_flags(t_params *flags);
void	print_flags(t_params *flags);
void	print_help_menu(void);

#endif
