#ifndef VAULT_H
#define VAULT_H

#include <stdint.h>

typedef struct Vault Vault;

extern Vault *vault_create(const char *vault_name);
extern void vault_destroy(Vault *vault);

extern void vault_store_entry(Vault *vault, const char *name, const char *value);
extern char *vault_find_entry(Vault *vault, const char *name);

extern uint8_t vault_save_to_file(Vault *vault);
extern uint8_t vault_read_from_file(Vault *vault);

extern void vault_create_required_directories(const char *path);
extern char *vault_get_default_file_path(const char *vault_name);

#ifdef DEBUG
extern void vault_dump_to_stdout(Vault *vault);
#endif

#endif // VAULT_H
