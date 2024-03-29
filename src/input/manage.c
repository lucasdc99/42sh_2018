/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** manage
*/

#include "my.h"

static void manage_command_fill(sh_t *sh, char *actual)
{
    if (sh->redirection_name != NULL || sh->redirection == 0) {
        sh->nbr_args = malloc(sizeof(int) * sh->nbr_command);
        for (int i = 0; sh->command[i] != NULL; i++)
            sh->nbr_args[i] = get_nbr_args(sh->command[i]);
        sh->args = put_args(sh->command, sh->nbr_command);
        for (int i = 0; sh->command[i] != NULL; i++)
            sh->command[i] = get_program_name(sh->command[i]);
        sh->exit_status = find_command(sh);
        free_command(sh, actual);
    }
}

static int manage_command_type(sh_t *sh, char *actual)
{
    if (sh->nbr_command == 84) {
        my_putstr_err("Invalid null command.\n");
        sh->exit_status = 1;
    } else {
        sh->command = malloc(sizeof(char *) * (sh->nbr_command + 1));
        manage_redirection(sh, actual);
        if (sh->redirection == 4 && sh->redirection_name != NULL) {
            actual = modify_actual_redirection(actual, sh->redirection_name);
            sh->redirection = 0;
            sh->nbr_command = 2;
            return (manage_command_type(sh, actual));
        }
        if (sh->redirection_name != NULL || sh->redirection == 0) {
            sh->command = get_tab_command(sh, actual);
            manage_command_fill(sh, actual);
        }
    }
    return (0);
}

int is_binary_condition_verified(sh_t *sh)
{
    if (sh->is_binary_op == 0)
        return (1);
    if (sh->is_binary_op == 1) {
        if (sh->exit_status == 0)
            return (1);
        return (0);
    }
    if (sh->is_binary_op == 2) {
        if (sh->exit_status != 0)
            return (1);
        return (0);
    }
    return (0);
}

void manage_user_input(sh_t *sh, char *str)
{
    char *actual = NULL;

    actual = get_actual_command_line(str);
    if (count_commands(str) == 84) {
        my_putstr_err("Invalid null command.\n");
        actual = get_actual_command_line(str);
        actual = NULL;
        str = "lucas";
        sh->exit_status = 1;
    }
    while (actual != NULL) {
        actual = clean_str(actual);
        sh->nbr_command = count_commands(actual);
        sh->redirection = is_redirection(actual);
        manage_command_type(sh, actual);
        if (is_binary_condition_verified(sh) == 1)
            actual = get_actual_command_line(str);
        else
            actual = get_actual_command_line(NULL);;
    }
}