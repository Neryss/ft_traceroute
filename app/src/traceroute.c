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
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include "socket.h"
#include "../libft/libft.h"
#include <sys/time.h>

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
	(struct sockaddr *)&traceroute->dest, sizeof(traceroute->dest)) == -1)
		printf("Could not send packet");
	gettimeofday(&traceroute->start, 0);
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

void	packet_rdns_lookup(struct sockaddr_in *addr_in, char *dest)
{
	struct sockaddr_in	tmp_addr;
	socklen_t			len;
	int					ret = 0;

	bzero(dest, 255);
	tmp_addr.sin_family = AF_INET;
	tmp_addr.sin_addr.s_addr = addr_in->sin_addr.s_addr;
	len = sizeof(struct sockaddr_in);
	if ((ret = getnameinfo((struct sockaddr *)&tmp_addr, len,
			dest, MAX_PACKET_SIZE, NULL, 0,
			NI_NAMEREQD)))
		dest = NULL;
}

void	recv_icmp(t_traceroute *traceroute)
{
	struct sockaddr_in	rep_addr;
	socklen_t			rep_len = sizeof(rep_addr);
	int					bytes = 0;

	bytes = recvfrom(traceroute->icmp_socket, traceroute->rcv_packet, MAX_PACKET_SIZE, 0, (struct sockaddr *)&rep_addr, &rep_len);
	if (bytes <= 0)
		printf(" * ");
	else
	{
		gettimeofday(&traceroute->end, 0);
		long double	rtt = (traceroute->end.tv_sec - traceroute->start.tv_sec) * 1000000.0 + traceroute->end.tv_usec - traceroute->start.tv_usec;
		rtt /= 1000;
		char	rdns[255];
		parse_icmp(traceroute);
		char	*ip = inet_ntoa(rep_addr.sin_addr);
		packet_rdns_lookup(&rep_addr, rdns);
		if (!strcmp(ip, traceroute->dest_str))
			traceroute->dest_reached = true;
		if (!rdns[0])
			ft_strncpy(rdns, ip, ft_strlen(ip));
		printf("%s (%s) %.3Lf ms ",rdns, ip, rtt);
	}
}
