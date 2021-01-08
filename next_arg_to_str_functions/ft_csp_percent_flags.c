/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csp_percent_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:57:40 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/08 11:57:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_C_TYPE_NEXT_ARG_TO_STR
** FT_PERCENT_TYPE_NEXT_ARG_TO_STR
** FT_S_TYPE_NEXT_ARG_TO_STR
** FT_P_TYPE_NEXT_ARG_TO_STR
**
** Each of the following functions will transform the next argument from va_list
** to a malloc'd string depending on the corresponding type
** Returns the address of the newly created string or 0 in case of error
*/

char	*ft_c_type_next_arg_to_str(va_list *v_l)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_char_alloc(1, '0')))
		return (0);
	arg_as_str[0] = (char)va_arg(*v_l, int);
	return (arg_as_str);
}

char	*ft_percent_type_next_arg_to_str(void)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_char_alloc(1, '%')))
		return (0);
	return (arg_as_str);
}

char	*ft_s_type_next_arg_to_str(va_list *v_l)
{
	char *arg_as_str;

	arg_as_str = va_arg(*v_l, char *);
	if (!(arg_as_str))
		return (ft_strdup("(null)"));
	return (ft_strdup(arg_as_str));
}

char	*ft_p_type_next_arg_to_str(va_list *v_l)
{
	void			*address;
	unsigned long	address_to_ulong;
	char			*arg_as_str;
	char			*temp;

	arg_as_str = 0;
	address = va_arg(*v_l, void *);
	address_to_ulong = (unsigned long)address;
	if (!address_to_ulong)
		return (ft_strdup("0x"));
	if (!(temp = ft_ultoa_base(address_to_ulong, BASE_LX)))
		return (0);
	if (!(arg_as_str = ft_strjoin("0x", temp)))
	{
		ft_free(temp, 0, 0);
		return (0);
	}
	free(temp);
	return (arg_as_str);
}