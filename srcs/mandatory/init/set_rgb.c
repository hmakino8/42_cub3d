/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:30:06 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 10:17:32 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_rgb_format(char *digit, bool is_last)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (digit[i] == '\0')
			return (false);
		if (i == 3)
			return (false);
		if (ft_isdigit(digit[i]) == false)
			return (false);
		i++;
		if ((!is_last && digit[i] == ',') || (is_last && ft_isspace(digit[i])))
			break ;
	}
	return (true);
}

static int	get_and_check_rgb_value(char *content, size_t *i, bool is_last)
{
	int	value;

	if (check_rgb_format(&content[*i], is_last) == false)
		return (-1);
	value = ft_atoi(&content[*i]);
	if (value < 0 || value > 255)
		return (-1);
	if (value == 0)
	{
		while (content[*i] == '0')
			(*i)++;
		if ((!is_last && content[*i] != ',')
			|| (is_last && !ft_isspace(content[*i])))
			return (-1);
	}
	while (ft_isdigit(content[*i]))
		(*i)++;
	if (!is_last)
	{
		if (content[*i] != ',')
			return (-1);
		(*i)++;
	}
	return (value);
}

void	set_rgb(t_data *data, char *content, size_t *i, t_rgb_info *color)
{
	if (color->is_set == true)
		end_program(data, HAS_DOUBLE_ENTRIE, HAS_DOUBLE_ENTRIE_MSG);
	(*i) += 1;
	while (ft_isspace(content[*i]))
		(*i)++;
	color->red = get_and_check_rgb_value(content, i, false);
	color->green = get_and_check_rgb_value(content, i, false);
	color->blue = get_and_check_rgb_value(content, i, true);
	color->is_set = true;
	if (color->red == -1 || color->green == -1 || color->blue == -1)
		end_program(data, INVALID_COLOR, INVALID_COLOR_MSG);
	color->rgb = (color->red << 16) + (color->green << 8) + color->blue;
}
