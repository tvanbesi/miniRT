/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_strsanity2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:06:52 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 22:29:14 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int
	ft_isvalid_dbendc(char *s, const char *c)
{
	if (*s == '-')
		s++;
	if (!ft_isvalid_intendc(s, c) && !ft_isvalid_intendc(s, "."))
		return (0);
	if (!(s = ft_strchr(s, '.')))
		return (1);
	return (ft_isvalid_intendc(++s, c));
}

int
	ft_isvalid_rgb(char *s)
{
	if (!ft_isvalid_intendc(s, ","))
		return (0);
	s = ft_strchr(s, ',') + 1;
	if (!ft_isvalid_intendc(s, ","))
		return (0);
	s = ft_strchr(s, ',');
	if (!++s)
		return (0);
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

int
	ft_isvalid_3db(char *s)
{
	if (!ft_isvalid_dbendc(s, ","))
		return (0);
	s = ft_strchr(s, ',') + 1;
	if (!ft_isvalid_dbendc(s, ","))
		return (0);
	s = ft_strchr(s, ',');
	if (!++s)
		return (0);
	return (ft_isvalid_db(s));
}
