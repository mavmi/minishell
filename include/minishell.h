/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/09 17:40:14 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMT "minishel> "

# include <stdio.h>
# include <fcntl.h>

# include "../readline/chardefs.h"
# include "../readline/history.h"
# include "../readline/keymaps.h"
# include "../readline/readline.h"
# include "../readline/rlconf.h"
# include "../readline/rlstdc.h"
# include "../readline/rltypedefs.h"
# include "../readline/tilde.h"

# include "../libft/libft.h"
# include "utils.h"
# include "enviroment.h"
# include "pipex.h"

void	set_up_signals(void);

#endif
