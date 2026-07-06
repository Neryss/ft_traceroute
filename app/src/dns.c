/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:23:05 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 16:54:59 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dns.h"
#include "error_exit.h"
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void    dns_lookup(t_params *params)
{
    struct addrinfo    hints;
    struct addrinfo    *result;

    ft_bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;
    if (getaddrinfo(params->host, NULL, &hints, &result) != 0)
        // error_exit(1, "could not getaddrinfo");
		return;
    params->ip = (struct addrinfo *)result;
    snprintf(
    params->host,
    INET_ADDRSTRLEN,
    "%s",
    inet_ntoa(((struct sockaddr_in *)params->ip->ai_addr)->sin_addr));
}

void	reverse_dns_lookup(t_params *params)
{
	struct sockaddr_in	tmp_addr;
	socklen_t			len;

	tmp_addr.sin_family = AF_INET;
	tmp_addr.sin_addr.s_addr = inet_addr(params->host);
	len = sizeof(struct sockaddr_in);
	if (getnameinfo((struct sockaddr *)&tmp_addr, len,
			params->rdns_str, sizeof(params->rdns_str), NULL, 0,
			NI_NAMEREQD))
			error_exit(1, "could not getnameinfo");
	if (!ft_strlen(params->rdns_str))
		ft_strncpy(params->rdns_str, params->host, ft_strlen(params->host));
}
