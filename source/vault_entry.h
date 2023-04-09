#ifndef VAULT_ENTRY_H
#define VAULT_ENTRY_H

typedef struct VaultEntry
{
    char *name;
    char *value;
} VaultEntry;

extern VaultEntry *vault_entry_create(const char *name, const char *value);
extern void vault_entry_destroy(VaultEntry *entry);

#endif // VAULT_ENTRY_H
