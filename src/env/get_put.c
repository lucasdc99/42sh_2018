/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_put
*/

#include "my.h"

char **put_old_pwd(char **env, char *pwd)
{
    int i = 0;
    int length = 0;

    for (; env[i] != NULL; i++) {
        if (strncmp(env[i], "OLDPWD=", 7) == 0) {
            length = strlen(pwd) + strlen("OLDPWD=") + 1;
            env[i] = malloc(sizeof(char) * length);
            env[i] = strcpy(env[i], "OLDPWD=");
            env[i] = strcat(env[i], pwd);
            return (env);
        }
    }
    env[i] = malloc(sizeof(char) * 100);
    env[i] = strcpy(env[i], "OLDPWD=");
    env[i] = strcat(env[i], pwd);
    env[i + 1] = 0;
    return (env);
}

char *get_old_pwd(char **env)
{
    char *str = NULL;

    for (int i = 0; env[i] != 0; i++) {
        if (strncmp(env[i], "OLDPWD=", 7) == 0) {
            str = malloc(sizeof(char) * (strlen(env[i]) + 1));
            str = strcpy(str, env[i]);
        }
    }
    if (str == NULL)
        return (NULL);
    for (int i = 0; i < 7; i++)
        str++;
    return (str);
}

char *get_home(char **env)
{
    char *str = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], "HOME=", 5) == 0) {
            str = malloc(sizeof(char) * (strlen(env[i]) + 1));
            str = strcpy(str, env[i]);
        }
    }
    if (str == NULL)
        return (NULL);
    while (str[0] != '=' && str[0] != '\0')
        str++;
    str++;
    return (str);
}

char *get_program_name(char *av)
{
    char *str;
    int i = 0;
    int j = 0;

    for (; av[i] != ' ' && av[i] != '\0'; i++);
    str = malloc(sizeof(char) * (i + 1));
    for (; j < i; j++)
        str[j] = av[j];
    str[j] = '\0';
    return (str);
}

int get_nbr_lines(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return (++i);
}