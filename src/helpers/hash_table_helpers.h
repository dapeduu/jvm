#ifndef HASH_TABLE_HELPERS_H
#define HASH_TABLE_HELPERS_H
#include "./core/core.h"

hash_table_t* newHashTable(short table_size);
hash_table_t addToHashTable(hash_table_t* hash_table, char* key, void* value);

#endif // HASH_TABLE_HELPERS_H