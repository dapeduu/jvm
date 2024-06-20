#include "../core/core.h"

hash_table_t* newHashTable(short table_size) {
  hash_table_t* hash_table = (hash_table_t*) malloc(sizeof(hash_table_t));
  hash_table->table_size = table_size;
  hash_table->data_size = 0;
  hash_table->entries = calloc(hash_table->table_size, sizeof(key_value_t*));
  
  return hash_table;
}

hash_table_t addToHashTable(hash_table_t* hash_table, char* key, void* value) {
  // TODO: add collision treament, test
    if (hash_table == NULL || key == NULL) {
        return *hash_table;  
    }

    int hash = hashFunction(key, hash_table->table_size);
    key_value_t* existing_entry = hash_table->entries[hash];
    if (existing_entry != NULL && strcmp(existing_entry->key, key) == 0) {
        free(existing_entry->value);
        existing_entry->value = value;
        return *hash_table;
    }

    key_value_t* key_value = (key_value_t*) malloc(sizeof(key_value_t));
    if (key_value == NULL) {
        return *hash_table; 
    }
    key_value->key = key;
    key_value->value = value;

    hash_table->entries[hash] = key_value;
    hash_table->data_size++;  

    return *hash_table;
}
