/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:16:56 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 20:11:57 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"
#include "error_exit.h"
#include "params.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include "socket.h"

void	increment_port(t_traceroute *traceroute)
{
	traceroute->port++;
	traceroute->dest.sin_port = htons(traceroute->port);
}

void	init_traceroute(t_traceroute *traceroute, t_params *params)
{
	traceroute->dest = *(struct sockaddr_in *)params->ip->ai_addr;
	traceroute->dest.sin_port = htons(traceroute->port);
	traceroute->ttl = 1;
	for (int i = 0; i < 32; i++)
		traceroute->snd_packet[i] = i + '0' + 16;
	init_sockets(traceroute);
}

void	send_probe(t_traceroute *traceroute)
{
	uint32_t	ttl = traceroute->ttl;

	if (setsockopt(traceroute->udp_socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)))
		error_exit(1, "ttl sockopt failed\n");
	if (sendto(traceroute->udp_socket, traceroute->snd_packet, 32, 0,
	(struct sockaddr *)&traceroute->dest, sizeof(traceroute->dest)))
		return;
		// printf("traceroute sendto: %s\n", strerror(errno));
}

void	parse_icmp(t_traceroute *traceroute)
{
	struct ip		*ip_hdr;
	struct icmphdr	*icmp_hdr;
	// uint8_t			*udp;
	// uint16_t		port;

	ip_hdr = (struct ip *)traceroute->rcv_packet;
	icmp_hdr = (struct icmphdr *)((char *)traceroute->rcv_packet + (ip_hdr->ip_hl * 4));
	// udp = (uint8_t *)(traceroute->rcv_packet + sizeof(struct ip) + ICMP_MINLEN + sizeof(struct ip));
	// port = ntohs(*(uint16_t *)(udp + sizeof(in_port_t)));
	// printf("ip hl %u\nport: %u\n", ip_hdr->ip_hl, port);
	// printf("response type: %u\n", icmp_hdr->type);
	(void)icmp_hdr;
}

void	recv_icmp(t_traceroute *traceroute)
{
	struct sockaddr_in	rep_addr;
	socklen_t			rep_len = sizeof(rep_addr);
	int			bytes = 0;

	bytes = recvfrom(traceroute->icmp_socket, traceroute->rcv_packet, MAX_PACKET_SIZE, 0, (struct sockaddr *)&rep_addr, &rep_len);
	// printf("bytes: %u\n", bytes);
	if (bytes <= 0)
	{
		// printf("recvfrom: %s\n", strerror(errno));
		printf("%*i  *\n", 2, traceroute->ttl);
	}
	else
	{
		parse_icmp(traceroute);
		char	*ip = inet_ntoa(rep_addr.sin_addr);
		if (!strcmp(ip, traceroute->dest_str))
			traceroute->dest_reached = true;
		printf("%*i  %s\n", 2, traceroute->ttl, ip);
	}
}
