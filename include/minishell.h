/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/09 21:08:01 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PORMT "minishel> "

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

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
# include "get_next_line.h"

void	set_up_signals(void);

#endif
