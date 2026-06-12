/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss <ckurt@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:59:23 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 14:31:12 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
#define SOCKET_H

#include "traceroute.h"

void	set_icmp_sockopt(int socket);
int		create_udp_socket(void);
int		create_icmp_socket(void);
void	set_udp_sockopt(int socket);
void	init_sockets(t_traceroute *traceroute);

#endif
