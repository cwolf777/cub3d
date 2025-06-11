/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:28:45 by cwolf             #+#    #+#             */
/*   Updated: 2025/06/07 12:51:41 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
// {
// 	size_t	dest_len;
// 	size_t	src_len;
// 	size_t	i;

// 	dest_len = 0;
// 	src_len = 0;
// 	while (dest[dest_len] != '\0' && dest_len < dstsize)
// 		dest_len++;
// 	while (src[src_len] != '\0')
// 		src_len++;
// 	if (dstsize == 0)
// 		return (dest_len + src_len);
// 	i = 0;
// 	while (src[i] != '\0' && (dest_len + i < dstsize - 1))
// 	{
// 		dest[dest_len + i] = src[i];
// 		i++;
// 	}
// 	if (dest_len + i < dstsize)
// 		dest[dest_len + i] = '\0';
// 	return (dest_len + src_len);
// }

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len])
	{
		src_len++;
	}
	if (dstsize > 0)
	{
		while (i < src_len && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

int	ft_strchr_check(const char *s, int c)
{
	char	a;

	a = (char) c;
	while (*s)
	{
		if (*s == a)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_allocate_rest_str(char *rest_str)
{
	if (rest_str == NULL)
	{
		rest_str = malloc(1);
		if (rest_str == NULL)
			return (NULL);
		rest_str[0] = '\0';
	}
	return (rest_str);
}
