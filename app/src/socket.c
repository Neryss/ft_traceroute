/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss <ckurt@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 14:02:00 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 16:20:55 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.h"
#include "error_exit.h"
#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

int		create_udp_socket(void)
{
	return (socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
}

int		create_icmp_socket(void)
{
	return (socket(AF_INET, SOCK_RAW, IPPROTO_ICMP));
}

void	set_udp_sockopt(int socket)
{
	struct timeval	timeout = {5, 0};
	if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
		error_exit(1, "Could not set sock opt on UDP socket\n");
		exit(1);
	}
}

void	set_icmp_sockopt(int socket)
{
	struct timeval	timeout = {5, 0};
	if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
		error_exit(1, "Could not set sock opt on ICMP socket\n");
		exit(1);
	}
}

void	init_sockets(t_traceroute *traceroute)
{
	traceroute->udp_socket = create_udp_socket();
	traceroute->icmp_socket = create_icmp_socket();
	set_udp_sockopt(traceroute->udp_socket);
	set_icmp_sockopt(traceroute->icmp_socket);
}
