/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:34:21 by cwolf             #+#    #+#             */
/*   Updated: 2025/06/07 12:52:55 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_in_rest_str(int fd, char *rest_str, char *buf);
char	*ft_linkstrings(char *rest_str, char *buf);
char	*ft_cut_until_newline(char *rest_str);
char	*ft_update_rest_str(char *rest_str);
char	*ft_allocate_rest_str(char *rest_str);

char	*get_next_line(int fd)
{
	char		*return_str;
	static char	*rest_str;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		if (rest_str)
		{
			free(rest_str);
			rest_str = NULL;
		}
		return (NULL);
	}
	rest_str = ft_read_in_rest_str(fd, rest_str, buf);
	if (rest_str == NULL)
		return (NULL);
	return_str = ft_cut_until_newline(rest_str);
	if (return_str == NULL)
	{
		free (rest_str);
		rest_str = NULL;
		return (NULL);
	}
	rest_str = ft_update_rest_str(rest_str);
	return (return_str);
}

// Read text from fd into buf, concatenate rest_str and buf, 
//and continue until a newline is found or EOF is reached.
char	*ft_read_in_rest_str(int fd, char *rest_str, char *buf)
{
	int		chars_read;

	chars_read = 1;
	rest_str = ft_allocate_rest_str(rest_str);
	if (rest_str == NULL)
		return (NULL);
	while (chars_read > 0 && !(ft_strchr_check(rest_str, '\n')))
	{
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free(rest_str);
			return (NULL);
		}
		buf[chars_read] = '\0';
		rest_str = ft_linkstrings(rest_str, buf);
		if (rest_str == NULL)
			return (NULL);
		if (chars_read == 0 && rest_str[0] == '\0')
		{
			free(rest_str);
			return (NULL);
		}
	}
	return (rest_str);
}

//Concatenate rest_str and buf with a temp string
char	*ft_linkstrings(char *rest_str, char *buf)
{
	char	*temp;
	int		total_length;

	if (rest_str == NULL)
		return (NULL);
	total_length = ft_strlen(rest_str) + ft_strlen(buf);
	temp = malloc((sizeof (char)) * total_length + 1);
	if (temp == NULL)
	{
		free(rest_str);
		return (NULL);
	}
	ft_strlcpy(temp, rest_str, ft_strlen(rest_str) + 1);
	ft_strlcat(temp, buf, total_length + 1);
	free(rest_str);
	return (temp);
}

// Alocates and returns return_str with characters 
// from rest_str up to and including the first newline or '\0'.
char	*ft_cut_until_newline(char *rest_str)
{
	int		len;
	char	*return_str;

	len = 0;
	while (rest_str[len] != '\n' && rest_str[len] != '\0')
		len++;
	if (rest_str[len] == '\n')
		len++;
	return_str = malloc(sizeof (char) * (len + 1));
	if (return_str == NULL)
		return (NULL);
	ft_strlcpy(return_str, rest_str, len + 1);
	return (return_str);
}

// Updates rest_str by removing characters up to and including 
// the first newline and returns it.
char	*ft_update_rest_str(char *rest_str)
{
	int		n;
	char	*str;

	n = 0;
	if (rest_str == NULL)
	{
		return (NULL);
	}
	while (rest_str[n] != '\n' && rest_str[n] != '\0')
		n++;
	if (rest_str[n] == '\0')
	{
		free(rest_str);
		return (NULL);
	}
	str = malloc (sizeof (char) * (ft_strlen(rest_str) - n + 1));
	if (str == NULL)
	{
		free(rest_str);
		return (NULL);
	}
	ft_strlcpy(str, rest_str + n + 1, ft_strlen(rest_str) - n + 1);
	free(rest_str);
	return (str);
}
