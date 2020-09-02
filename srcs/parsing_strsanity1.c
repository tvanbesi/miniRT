/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_strsanity1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 18:09:36 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/09/02 22:29:10 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
	ft_isvalid_int(char *s)
{
	if (*s == '-')
		s++;
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

int
	ft_isvalid_intendc(char *s, const char *c)
{
	if (*s == '-')
		s++;
	if (!ft_isdigit(*s))
		return (0);
	while (ft_isdigit(*s))
		s++;
	return (ft_strchr(c, *s) != NULL);
}

int
	ft_isvalid_db(char *s)
{
	if (*s == '-')
		s++;
	if (!ft_isvalid_intendc(s, ".\0"))
		return (0);
	if (!(s = ft_strchr(s, '.')))
		return (1);
	s++;
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}
