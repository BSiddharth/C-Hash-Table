#include "hashmap.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const uintmax_t total_buckets = 100;

typedef struct HashMapValue {
  size_t data_size;
  void *key;
  void *data;
  hashmap_value *next; // could be pointing to NULL
} hashmap_value;

typedef struct HashMap {
  uintmax_t total_buckets;
  hashmap_value *keys[];
} hashmap;

hashmap *create_hashmap() {

  // allocating space for hashmap
  hashmap *hashmap_pointer =
      malloc(sizeof(hashmap) + (total_buckets * sizeof(hashmap_value *)));

  if (hashmap_pointer == NULL) {
    printf("Could not allocate space for hashmap, exiting...");
    exit(EXIT_FAILURE);
  }

  // setting up the allocated memory for a new hashmap
  hashmap_pointer->total_buckets = total_buckets;
  for (uintmax_t i = 0; i < total_buckets; i++) {
    hashmap_pointer->keys[i] = NULL; // NULL means the bucket is empty
  }

  return hashmap_pointer;
};

/* Can also be used to update element */
void insert_in_hash_map(hashmap *hm, uintmax_t key, void *value) {}

void remove_from_hash_map(hashmap *hm, char *key);

bool is_in_hash_map(hashmap *hm, char *key);

/* Always check for that key exists in the HashMap */
void *get_value(hashmap *hm, char *key);
