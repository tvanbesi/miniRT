/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_strsanity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <thomasvanbesien@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 18:09:36 by thomasvanbe       #+#    #+#             */
/*   Updated: 2020/08/23 13:09:23 by thomasvanbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static int
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
