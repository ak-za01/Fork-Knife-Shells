/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:50:37 by anktiri           #+#    #+#             */
/*   Updated: 2025/06/26 21:14:43 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_bonus.h"

void	error_message(char *cmd, char *str)
{
	char	*clean_str;

	clean_str = NULL;
	if (!clean_str)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
		fprintf(stderr, "minishell: %s: invalid argument\n", cmd);
}

char	*get_var_value(char *str)
{
	char	**value;
	char	*result;

	value = ft_split_env(str, '=');
	if (!value)
		return (NULL);
	result = value[1];
	free(value[0]);
	free(value);
	return (result);
}

static int	process_existing_var(t_env *current, char *arg)
{
	char	*new_val;

	if (!ft_strchr(arg, '='))
		return (0);
	new_val = get_var_value(arg);
	if (!new_val)
		return (1);
	if (current->value)
		free(current->value);
	current->value = new_val;
	return (0);
}

static int	process_export_arg(char *arg, t_env *env_list)
{
	t_env	*current;

	if (!valid_variable(arg))
	{
		error_message("export", arg);
		return (1);
	}
	current = env_list;
	if (search_variable(&current, arg))
		return (process_existing_var(current, arg));
	if (!add_new_node(arg, env_list))
		return (1);
	return (0);
}

int	ft_export(t_token *data, t_extra *x)
{
	int		i;
	t_env	*copy;

	i = 1;
	copy = NULL;
	if (!data->c_arg[i])
	{
		sort_env_list(x->env_list, &copy);
		print_env_list(copy);
	}
	while (data->c_arg[i])
	{
		if (process_export_arg(data->c_arg[i], x->env_list))
			x->exit_status = 1;
		i++;
	}
	return (x->exit_status);
}
