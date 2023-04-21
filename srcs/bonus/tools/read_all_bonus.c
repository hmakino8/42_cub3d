/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:24:53 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 16:40:54 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static bool	do_allocation(char **str1, char **str2)
{
	*str1 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (*str1 == NULL)
		return (false);
	*str2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (*str2 == NULL)
	{
		free(str1);
		return (false);
	}
	return (true);
}

static char	*free_and_return_null(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (NULL);
}

static char	*ft_strjoin_with_free(char *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_length;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_length = s1_len + s2_len;
	result = malloc(sizeof(char) * (total_length + 1));
	if (result == NULL)
		return (result);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return (result);
}

char	*read_all(int fd)
{
	char	*str1;
	char	*str2;
	ssize_t	read_count;

	if (do_allocation(&str1, &str2) == false)
		return (NULL);
	read_count = read(fd, str1, BUFFER_SIZE);
	if (read_count < 0)
		return (free_and_return_null(str1, str2));
	while (read_count == BUFFER_SIZE)
	{
		read_count = read(fd, str2, BUFFER_SIZE);
		if (read_count == -1)
			return (free_and_return_null(str1, str2));
		str1 = ft_strjoin_with_free(str1, str2);
		if (str1 == NULL)
			break ;
		ft_bzero(str2, BUFFER_SIZE);
	}
	free(str2);
	return (str1);
}
