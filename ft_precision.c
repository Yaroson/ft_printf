/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:09:59 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/19 11:40:49 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_PRECISION_S_TYPE_TO_STR
** This function checks precision when the specified type is a string
** Mallocs a string of [precision] chars and copies first
** [precision] chars of str_to_format to it
** Returns the result or 0 malloc fails
*/

static	char	*ft_precision_s_type_to_str(char *str_to_format, t_list *list)
{
	char	*ret_str;
	int		i;

	if (!list->precision || list->precision >= (int)ft_strlen(str_to_format))
		return (ft_strdup(str_to_format));
	if (!(ret_str = ft_char_alloc(list->precision, ' ')))
		return (0);
	i = 0;
	while (ret_str[i] && str_to_format[i])
	{
		ret_str[i] = str_to_format[i];
		i++;
	}
	return (ret_str);
}

/*
** FT_DETERMINE_C_MAX
** This function determines the minimum characters needed to print the
** str_to_format argument which is used in ft_precision_to_str function
** This value is different for 'd' and 'i' type flags and the rest of the flags.
** For 'd' and 'i', we don't count the '-' flag it it is present,
** only the digits are taken into account.
** For other types, we simply count the number of characters in the string
** Returns the number of chars used in comparision with the precision to
** decide whether the precision is ignored or not
*/

static int		ft_determine_c_max(char *str_to_format, t_list *list)
{
	int	c_max;

	c_max = 0;
	if (list->type_flag == 'd' || list->type_flag == 'i')
		c_max = ft_count_n_digits(str_to_format);
	else
		c_max = (int)ft_strlen(str_to_format);
	return (c_max);
}

/*
** FT_PRECISION_TO_STR
** This function checks precision when the specified type is not a string
** Mallocs a string of [precision] chars, fills it with '0'
** and copies str_to_format (at the end of it)
** Returns the result or 0 if malloc fails
*/

static	char	*ft_precision_to_str(char *str_to_format, t_list *list)
{
	char	*ret_str;
	int		i;
	int		j;
	int		precision;

	precision = list->precision;
	if (!precision || (list->precision &&
		list->precision <= ft_determine_c_max(str_to_format, list)))
		return (ft_strdup(str_to_format));
	ret_str = 0;
	if (ft_strchr(str_to_format, '-'))
		precision++;
	if (!(ret_str = ft_char_alloc(precision, '0')))
		return (0);
	i = ft_strlen(str_to_format) + 1;
	j = ft_strlen(ret_str) + 1;
	while (--i >= 0 && --j >= 0)
		ret_str[j] = str_to_format[i];
	if (ft_strchr(str_to_format, '-'))
	{
		ret_str[ft_strlen(ret_str) - ft_strlen(str_to_format)] = '0';
		ret_str[0] = '-';
	}
	return (ret_str);
}

/*
** FT_PRECISION_P_TYPE_TO_STR
** The difference with the 'p' (=address) type is that the precision is added
** after the starting '0x', not before it
** Returns the newly created string with precision applied
*/

static	char	*ft_precision_p_type_to_str(char *str_to_format, t_list *list)
{
	char	*temp;
	char	*ret;

	if (!(temp = ft_precision_to_str(str_to_format + 2, list)))
		return (0);
	ret = ft_strjoin("0x", temp);
	ft_free(&temp, 0, 0);
	return (ret);
}

/*
** FT_PRECISION
** This function checks the type flag of t_list and send the str_to_format
** argument to the corresponding function which will apply the precision flag
** Returns the newly created prec_str (and it will be NULL if a malloc fails)
*/

char			*ft_precision(char *str_to_format, t_list *list)
{
	char *prec_str;

	prec_str = 0;
	if (list->type_flag == 's')
		prec_str = ft_precision_s_type_to_str(str_to_format, list);
	else if (list->type_flag == '%' || list->type_flag == 'c')
		prec_str = ft_strdup(str_to_format);
	else if (list->type_flag == 'p')
		prec_str = ft_precision_p_type_to_str(str_to_format, list);
	else
		prec_str = ft_precision_to_str(str_to_format, list);
	return (prec_str);
}
