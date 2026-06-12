/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:45:41 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 14:19:57 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEROUTE_H
#define TRACEROUTE_H

typedef struct	s_traceroute
{
	int	udp_socket;
	int	icmp_socket;
}				t_traceroute;

#endif
