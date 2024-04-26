#include "hashmap.h"
#include "murmurhash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *first_name;
  char *last_name;
  char *phone_number;
} User;

bool compare_user(const void *user1, const void *user2) {
  const User *user_1 = (const User *)user1;
  const User *user_2 = (const User *)user2;
  printf("Element addr: %p being received \n", user_1);
  printf("first name addr: %p\n", user_1->first_name);
  printf("last name addr: %p\n", user_1->last_name);
  printf("phone num addr: %p\n", user_1->phone_number);
  // printf("%s\n", user_1->phone_number);

  // use "or" instead of "and" because strcmp gives "0" if equal
  bool result = strcmp(user_1->first_name, user_2->first_name) ||
                strcmp(user_1->last_name, user_2->last_name) ||
                strcmp(user_1->phone_number, user_2->phone_number);

  return result == 0;
}

uint32_t hash_user(const void *item, uint32_t len, uint32_t seed) {
  const User *user = item;
  size_t buffer_len = strlen(user->first_name) + strlen(user->last_name) +
                      strlen(user->phone_number);
  char *user_str[buffer_len + 1];
  int result;

  result =
      strcpy_s((char *)user_str, buffer_len + 1, (char *)&(user->first_name));
  if (result != 0) {
    printf("Error while copying first_name");
    exit(EXIT_FAILURE);
  }

  result = strcat_s((char *)user_str, buffer_len + 1, user->last_name);
  if (result != 0) {
    printf("Error while copying last_name");
    exit(EXIT_FAILURE);
  }
  result = strcat_s((char *)user_str, buffer_len + 1, user->phone_number);

  if (result != 0) {
    printf("Error while copying phone_number");
    exit(EXIT_FAILURE);
  }

  return murmurhash((const char *)user_str, buffer_len, 123123);
}

int main() {
  printf("Running test now\n");

  User sid = {"Siddharth", "Bisht", "1234567890"};
  User vaish = {"Vaishnavi", "Bisht", "1934767890"};

  hashmap *my_hashmap = create_hashmap(
      &hash_user, compare_user); // &func and func are the same thing

  insert_in_hash_map(my_hashmap, &sid, sizeof(sid), &vaish, sizeof(vaish));
  // bool isitin = is_in_hash_map(my_hashmap, &sid, sizeof(sid));
  assert(is_in_hash_map(my_hashmap, &sid, sizeof(sid)));

  printf("Test was succcesful\n");
  return EXIT_SUCCESS;
}
