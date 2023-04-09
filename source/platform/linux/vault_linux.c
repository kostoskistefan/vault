#ifdef __linux__

#include "../../../include/vault.h"
#include <pwd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

char *vault_get_default_file_path(const char *vault_name)
{
    char *home_directory = getenv("HOME");

    if (!home_directory)
        home_directory = getpwuid(getuid())->pw_dir;

    const char *path_format = "%s/.config/%s/%s.vlt";

    uint16_t path_length = snprintf(NULL, 0, path_format, home_directory, vault_name, vault_name);

    char *path = malloc(path_length);

    sprintf(path, path_format, home_directory, vault_name, vault_name);

    return path;
}

void vault_create_required_directories(const char *path)
{
    char *dir_path = malloc(strlen(path) + 1);
    char *next_sep = strchr(path, '/');

    while (next_sep != NULL)
    {
        int dir_path_len = next_sep - path;
        memcpy(dir_path, path, dir_path_len);
        dir_path[dir_path_len] = '\0';
        mkdir(dir_path, S_IRWXU | S_IRWXG | S_IROTH);
        next_sep = strchr(next_sep + 1, '/');
    }

    free(dir_path);
}

#endif
