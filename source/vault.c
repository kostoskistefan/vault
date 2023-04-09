#include "../include/vault.h"
#include "vault_entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAULT_INITIAL_STORAGE_CAPACITY 8

struct Vault
{
    uint16_t storage_capacity;
    uint16_t number_of_entries;
    char *name;
    VaultEntry **entries;
};

Vault *vault_create(const char *vault_name)
{
    Vault *vault = malloc(sizeof(Vault));

    vault->storage_capacity = VAULT_INITIAL_STORAGE_CAPACITY;
    vault->number_of_entries = 0;
    vault->name = strdup(vault_name);
    vault->entries = malloc(sizeof(VaultEntry *) * VAULT_INITIAL_STORAGE_CAPACITY);

    return vault;
}

void vault_destroy(Vault *vault)
{
    for (uint16_t i = 0; i < vault->number_of_entries; ++i)
        vault_entry_destroy(vault->entries[i]);

    free(vault->name);
    free(vault->entries);
    free(vault);
}

void vault_store_entry(Vault *vault, const char *name, const char *value)
{
    if (vault->number_of_entries == vault->storage_capacity)
    {
        vault->storage_capacity += VAULT_INITIAL_STORAGE_CAPACITY;
        vault->entries = realloc(vault->entries, vault->storage_capacity);
    }

    vault->entries[vault->number_of_entries] = vault_entry_create(name, value);
    ++vault->number_of_entries;
}

char *vault_find_entry(Vault *vault, const char *name)
{
    for (uint16_t i = 0; i < vault->number_of_entries; ++i)
        if (strcmp(vault->entries[i]->name, name) == 0)
            return vault->entries[i]->value;

    return NULL;
}

uint8_t vault_save_to_file(Vault *vault)
{
    char *file_path = vault_get_default_file_path(vault->name);

    vault_create_required_directories(file_path);

    FILE *file = fopen(file_path, "w");

    free(file_path);

    if (!file)
    {
        fprintf(stderr, "vault::error: Failed to open vault file in write mode.\n");
        return 0;
    }

    for (uint16_t i = 0; i < vault->number_of_entries; ++i)
        fprintf(file, "%s=%s\n", vault->entries[i]->name, vault->entries[i]->value);

    fclose(file);

    return 1;
}

uint8_t vault_read_from_file(Vault *vault)
{
    char *file_path = vault_get_default_file_path(vault->name);

    FILE *file = fopen(file_path, "r");

    free(file_path);

    if (!file)
    {
        fprintf(stderr, "vault::error: Failed to open vault file in read mode. Has a vault file ever been created?\n");
        return 0;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file))
    {
        uint8_t index_of_delimiter = strchr(buffer, '=') - buffer + 1;
        uint8_t length_of_value_field = strlen(buffer) - index_of_delimiter;

        char *name = malloc(index_of_delimiter);
        char *value = malloc(length_of_value_field);

        strncpy(name, buffer, index_of_delimiter);
        strncpy(value, buffer + index_of_delimiter, length_of_value_field);

        name[index_of_delimiter - 1] = '\0';
        value[length_of_value_field - 1] = '\0';

        vault_store_entry(vault, name, value);

        free(name);
        free(value);
    }

    fclose(file);

    return 1;
}

#ifdef DEBUG
void vault_dump_to_stdout(Vault *vault)
{
    printf("\n-------------------- DUMPING VAULT CONTENTS --------------------\n\n");

    for (uint16_t i = 0; i < vault->number_of_entries; ++i)
        printf("%d. %s = %s\n", i + 1, vault->entries[i]->name, vault->entries[i]->value);
}
#endif
