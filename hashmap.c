#include "hashmap.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uintmax_t initial_total_buckets = 100;
const uint32_t secret_seed = 20010206;

typedef struct HashMapValue {
  void *key;
  void *data;
  hashmap_value *next; // could be pointing to NULL
} hashmap_value;

typedef struct HashMap {
  uintmax_t total_buckets;
  uint32_t (*hash_func)(const void *item, uint32_t seed);
  bool (*compare_func)(const void *item1, const void *item2);
  hashmap_value *keys[];
} hashmap;

hashmap *create_hashmap(uint32_t (*hash_func)(const void *item, uint32_t seed),
                        bool (*compare_func)(const void *item1,
                                             const void *item2)) {
  // allocating space for hashmap
  hashmap *hashmap_pointer = malloc(
      sizeof(hashmap) + (initial_total_buckets * sizeof(hashmap_value *)));

  if (hashmap_pointer == NULL) {
    printf("Could not allocate space for hashmap, exiting...\n");
    exit(EXIT_FAILURE);
  }

  // setting up the allocated memory for a new hashmap
  hashmap_pointer->total_buckets = initial_total_buckets;
  hashmap_pointer->hash_func = hash_func; // func are passed as pointers
  hashmap_pointer->compare_func = compare_func;
  for (uintmax_t i = 0; i < initial_total_buckets; i++) {
    hashmap_pointer->keys[i] = NULL; // NULL means the bucket is empty
  }

  return hashmap_pointer;
};

/* Can also be used to update element */
bool insert_in_hash_map(hashmap *hm, void *key, size_t key_size, void *value,
                        size_t value_size) {

  void *value_copy = malloc(value_size);
  if (value_copy == NULL) {
    printf("Insertion: Could not create space for the new value\n");
    return false;
  }

  int value_copy_status = memcpy_s(value_copy, value_size, value, value_size);
  if (value_copy_status != 0) {
    printf("Insertion: Could not copy the new value\n");
    return false;
  }
  uintmax_t index = hm->hash_func(key, secret_seed) % hm->total_buckets;

  hashmap_value *current_element = hm->keys[index];
  hashmap_value *last_element = NULL;

  while (current_element != NULL) {
    if (hm->compare_func(current_element->key, key)) {
      goto replace;
    }
    last_element = current_element;
    current_element = current_element->next;
  }

  hashmap_value *new_hashmapvalue = malloc(sizeof(hashmap_value));
  if (new_hashmapvalue == NULL) {
    printf("Insertion: Could not create space for the new hashmap_value\n");
    return false;
  }

  void *key_copy = malloc(key_size);
  if (key_copy == NULL) {
    printf("Insertion: Could not create space for the new key\n");
    return false;
  }

  int key_copy_status = memcpy_s(key_copy, key_size, key, key_size);
  if (key_copy_status != 0) {
    printf("Insertion: Could not copy the new key\n");
    return false;
  }
  new_hashmapvalue->key = key_copy;
  new_hashmapvalue->data = value_copy;
  new_hashmapvalue->next = NULL;

  if (last_element == NULL) {
    hm->keys[index] = new_hashmapvalue;
  } else {
    last_element->next = new_hashmapvalue;
  }

  return true;

replace:
  free(current_element->data);
  current_element->data = value_copy;
  return true;
}

bool remove_from_hash_map(hashmap *hm, void *key, size_t key_size) {

  uintmax_t index = hm->hash_func(key, secret_seed) % hm->total_buckets;

  hashmap_value *current_element = hm->keys[index];
  hashmap_value *last_element = NULL;

  while (current_element != NULL) {
    if (hm->compare_func(current_element, key)) {
      if (last_element == NULL) {
        hm->keys[index] = current_element->next;
      } else {
        last_element->next = current_element->next;
      }
      free(current_element);
    }
    last_element = current_element;
  }
  return true;
}

bool is_in_hash_map(hashmap *hm, void *key, size_t key_size) {
  void *return_val = get_value(hm, key, key_size);
  if (return_val == NULL) {
    return false;
  }
  return true;
}

void *get_value(hashmap *hm, void *key, size_t key_size) {
  uintmax_t index = hm->hash_func(key, secret_seed) % hm->total_buckets;

  hashmap_value *current_element = hm->keys[index];

  while (current_element != NULL) {
    if (hm->compare_func(current_element->key, key)) {
      return current_element->data;
    }
    current_element = current_element->next;
  }
  return NULL;
}
