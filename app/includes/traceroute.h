/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:45:41 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 19:34:42 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include "params.h"
#include <netinet/in.h>
#include <stdint.h>

#define MAX_PACKET_SIZE 1024
#define DEFAULT_PACKET_SIZE 32

typedef struct	s_traceroute
{
	struct sockaddr_in	dest;
	char		*dest_str;
	int			udp_socket;
	int			icmp_socket;
	uint16_t	port;
	uint8_t		ttl;
	char		snd_packet[MAX_PACKET_SIZE];
	char		rcv_packet[MAX_PACKET_SIZE];
	bool		dest_reached;
}				t_traceroute;

void	increment_port(t_traceroute *traceroute);
void	init_traceroute(t_traceroute *traceroute, t_params *params);
void	send_probe(t_traceroute *traceroute);
void	recv_icmp(t_traceroute *traceroute);

#endif
