/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:20:09 by bberkrou          #+#    #+#             */
/*   Updated: 2023/11/26 11:48:31 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path_var(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}

char *build_full_path(char *dir, char *cmd)
{
    char *temp;
    char *full_path;

    temp = ft_strjoin(dir, "/");
    full_path = ft_strjoin(temp, cmd);
    free(temp);
    return (full_path);
}

/*
** ft_get_path: Finds the executable path of a command.
**
** @param  cmd        The command to find.
** @param  envp       Environment variables, including PATH.
** @return            Full path of the command, or NULL if not found.
**
** Splits PATH, checks each directory for cmd, and returns the path if found.
*/
char *ft_get_path(char *cmd, char **envp)
{
    char **paths;
    char *path;
    char *path_var;
    int i;

    path_var = find_path_var(envp);
    if (!path_var)
        return (NULL);

    paths = ft_split(path_var, ':');
    i = 0;
    while (paths[i])
    {
        path = build_full_path(paths[i], cmd);
        if (access(path, F_OK | X_OK) == 0)
        {
            ft_free_tab(paths);
            return (path);
        }
        free(path);
        i++;
    }
    ft_free_tab(paths);
    return (NULL);
}