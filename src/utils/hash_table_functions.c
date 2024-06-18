#include "./core/core.h"

hash_table_t* newHashTable(short table_size) {
  hash_table_t* hash_table = (hash_table_t*) malloc(sizeof(hash_table_t));
  hash_table->table_size = table_size;
  hash_table->data_size = 0;
  hash_table->entries = calloc(hash_table->table_size, sizeof(key_value_t*));
  for (int i = 0; i < table_size; i++) {
    hash_table->entries[i] = NULL;
  }
  return hash_table;
}