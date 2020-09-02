/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <tvanbesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 21:10:22 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/09/02 21:41:14 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t
	ft_wn(char const *s, char *str)
{
	size_t	r;
	int		b;

	r = 0;
	b = 0;
	while (*s)
	{
		if (!b && !ft_strchr(str, *s))
		{
			r++;
			b = 1;
		}
		else if (b && ft_strchr(str, *s))
			b = 0;
		s++;
	}
	return (r);
}

static void
	*ft_fr(char **r, size_t n)
{
	size_t	in;

	in = n;
	while (n-- > 0)
		free(*r++);
	free(r - in);
	return (NULL);
}

static void
	*ft_fr_esc(char **r, char const *s, char *str, size_t cnt)
{
	return (ft_fr(r - (ft_wn(s, str) - (cnt + 1)), (ft_wn(s, str) - cnt)));
}

char
	**ft_splits(char const *s, char *str)
{
	char		**r;
	const char	*ps;
	size_t		cnt;
	size_t		start;
	size_t		end;

	cnt = ft_wn(s, str);
	if (!(r = (char**)ft_calloc(cnt + 1, sizeof(*r))))
		return (NULL);
	ps = s;
	start = 0;
	while (cnt-- > 0)
	{
		while (*ps && ft_strchr(str, *ps++))
			start++;
		end = start + 1;
		while (*ps && !ft_strchr(str, *ps++))
			end++;
		if (!(*r = ft_substr(s, start, end - start)))
			return (ft_fr_esc(r, s, str, cnt));
		r++;
		start = end + 1;
	}
	*r = NULL;
	return (r - ft_wn(s, str));
}
