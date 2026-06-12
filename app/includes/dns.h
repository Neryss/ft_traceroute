/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dns.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:23:24 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 16:51:35 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DNS_H
#define DNS_H

#include "params.h"

void	dns_lookup(t_params *params);
void	reverse_dns_lookup(t_params *params);

#endif
