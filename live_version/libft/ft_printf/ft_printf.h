/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:58:41 by pjelinek          #+#    #+#             */
/*   Updated: 2025/08/29 12:59:08 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	ft_va_start(const char *str, va_list ap);
int	find_arg(char c, va_list ap);
int	ft_arg_string(char *str);
int	ft_int_check(int nb);
int	ft_arg_pointer(void *p, char c);
int	ft_putnbr_base(size_t hexanum, size_t divider, char Xx);

#endif
