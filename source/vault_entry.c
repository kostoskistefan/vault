#include "vault_entry.h"
#include <stdlib.h>
#include <string.h>

VaultEntry *vault_entry_create(const char *name, const char *value)
{
    VaultEntry *entry = malloc(sizeof(VaultEntry));

    entry->name = strdup(name);
    entry->value = strdup(value);

    return entry;
}

void vault_entry_destroy(VaultEntry *entry)
{
    free(entry->name);
    free(entry->value);
    free(entry);
}
