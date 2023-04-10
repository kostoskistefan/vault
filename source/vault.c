#include "../include/vault.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAULT_INITIAL_CAPACITY 16

typedef struct VaultEntry
{
    char *key;
    char *value;
} VaultEntry;

typedef struct Vault
{
    uint16_t capacity;
    uint16_t entry_amount;
    char *file_path;
    struct VaultEntry **entries;
} Vault;

Vault *vault_create(const char *vault_name)
{
    Vault *vault = (Vault *) malloc(sizeof(Vault));

    vault->capacity = VAULT_INITIAL_CAPACITY;
    vault->entry_amount = 0;
    vault->entries = (VaultEntry **) malloc(sizeof(VaultEntry *) * VAULT_INITIAL_CAPACITY);
    vault->file_path = vault_get_default_file_path(vault_name);

    return vault;
}

void vault_destroy(Vault *vault)
{
    for (uint16_t i = 0; i < vault->entry_amount; ++i)
    {
        free(vault->entries[i]->key);
        free(vault->entries[i]->value);
        free(vault->entries[i]);
    }

    free(vault->entries);
    free(vault->file_path);
    free(vault);
}

uint8_t vault_insert(Vault *vault, const char *key, const char *value)
{
    for (uint16_t i = 0; i < vault->entry_amount; ++i)
    {
        if (strcmp(vault->entries[i]->key, key) == 0)
        {
            fprintf(stderr, "vault::error: Failed to insert entry. Key exists.\n");
            return 0;
        }
    }

    if (vault->entry_amount == vault->capacity)
    {
        vault->capacity += VAULT_INITIAL_CAPACITY;
        vault->entries = (VaultEntry **) realloc(vault->entries, vault->capacity);
    }

    VaultEntry *entry = (VaultEntry *) malloc(sizeof(VaultEntry));
    entry->key = strdup(key);
    entry->value = strdup(value);

    vault->entries[vault->entry_amount] = entry;
    ++vault->entry_amount;

    return 1;
}

char *vault_find(Vault *vault, const char *key, char *default_value)
{
    for (uint16_t i = 0; i < vault->entry_amount; ++i)
        if (strcmp(vault->entries[i]->key, key) == 0)
            return vault->entries[i]->value;

    return default_value;
}

uint8_t vault_update(Vault *vault, const char *key, const char *value)
{
    for (uint16_t i = 0; i < vault->entry_amount; ++i)
    {
        if (strcmp(vault->entries[i]->key, key) == 0)
        {
            uint16_t new_value_length = strlen(value);

            if (new_value_length > strlen(vault->entries[i]->value))
                vault->entries[i]->value = realloc(vault->entries[i]->value, new_value_length);

            strcpy(vault->entries[i]->value, value);

            return 1;
        }
    }

    fprintf(stderr, "vault::error: Failed to update entry. Key does not exists.\n");
    return 0;
}

uint8_t vault_save(Vault *vault)
{
    vault_create_required_directories(vault->file_path);

    FILE *file = fopen(vault->file_path, "w");

    if (file == NULL)
    {
        fprintf(stderr, "vault::error: Failed to open vault file in write mode\n");
        return 0;
    }

    for (uint16_t i = 0; i < vault->entry_amount; ++i)
        fprintf(file, "%s = %s\n", vault->entries[i]->key, vault->entries[i]->value);

    fclose(file);

    return 1;
}

uint8_t vault_load(Vault *vault)
{
    FILE *file = fopen(vault->file_path, "r");

    if (file == NULL)
    {
        fprintf(stderr, "vault::error: Failed to open vault file in read mode\n");
        return 0;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        char *key = strtok(line, " =\r\n");
        char *value = strtok(NULL, " =\r\n");

        vault_insert(vault, key, value);
    }

    fclose(file);

    return 1;
}

void vault_dump(Vault *vault)
{
    for (uint16_t i = 0; i < vault->entry_amount; ++i)
        printf("%s = %s\n", vault->entries[i]->key, vault->entries[i]->value);
}
