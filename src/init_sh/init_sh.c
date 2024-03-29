/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** init_sh
*/

#include "my.h"

void print_errors_exec(char *command)
{
    if (errno == 8) {
        my_putstr_err(command);
        my_putstr_err(": Exec format error. Wrong Architecture.\n");
    } else if (errno != 2) {
        my_putstr_err(command);
        my_putstr_err(": Permission denied.\n");
    }
}

char **new_path_to_env(char **env)
{
    int j = 0;

    for (; env[j] != NULL; j++);
    env[j] = malloc(sizeof(char) * 50);
    env[j] = strcpy(env[j],
    "PATH=/bin:/usr/local/bin:/sbin:/usr/bin:/usr/sbin");
    env[j + 1] = 0;
    return (env);
}

void init_sh(sh_t *sh, char **env)
{
    sh->exit_status = 0;
    sh->redirection_name = NULL;
    sh->old_pwd = NULL;
    sh->nbr_args = NULL;
    sh->not_found = 0;
    sh->args = NULL;
    sh->nbr_command = 0;
    if (env[0] == 0)
        env = new_path_to_env(env);
    sh->path = get_path(env);
    if (sh->path == NULL) {
        env = new_path_to_env(env);
        sh->path = get_path(env);
    }
    sh->env = env;
    put_in_history(sh, -1);
}