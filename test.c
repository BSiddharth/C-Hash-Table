#include "hashmap.h"
#include "murmurhash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECKCOPYERROR(el)                                                     \
  if (result != 0) {                                                           \
    printf("Error while copying ");                                            \
    printf(el);                                                                \
    printf("\n");                                                              \
    exit(EXIT_FAILURE);                                                        \
  }

const uint32_t mumurhash_seed = 123123;

typedef struct {
  char *first_name;
  char *last_name;
  char *phone_number;
} User;

bool compare_user(const void *user1, const void *user2) {
  const User *user_1 = (const User *)user1;
  const User *user_2 = (const User *)user2;

  // use "or" instead of "and" because strcmp gives "0" if equal
  bool result = strcmp(user_1->first_name, user_2->first_name) ||
                strcmp(user_1->last_name, user_2->last_name) ||
                strcmp(user_1->phone_number, user_2->phone_number);

  return result == 0;
}

uint32_t hash_user(const void *item, uint32_t seed) {
  const User *user = item;
  size_t user_data_len = strlen(user->first_name) + strlen(user->last_name) +
                         strlen(user->phone_number);
  char user_str[user_data_len + 1];
  errno_t result;

  result = strcpy_s(user_str, user_data_len + 1, user->first_name);
  CHECKCOPYERROR("first name")

  result = strcat_s(user_str, user_data_len + 1, user->last_name);
  CHECKCOPYERROR("last name")

  result = strcat_s(user_str, user_data_len + 1, user->phone_number);
  CHECKCOPYERROR("phone number")

  return murmurhash(user_str, user_data_len, mumurhash_seed);
}

int main() {
  printf("Running test now\n");

  User sid = {"Siddharth", "Bisht", "1234567890"};
  User vaish = {"Vaishnavi", "Bisht", "1934767890"};
  User mom = {"Mom", "Bisht", "5934767890"};
  User dad = {"Dad", "Bisht", "1034767890"};

  // Test hashmap creation
  printf("Test 1: Creating hashmap \n");

  hashmap *my_hashmap = create_hashmap(
      &hash_user, compare_user); // &func and func are the same thing

  printf("Test 1: Succesful \n");

  // Test insertion
  printf("Test 2: Insertion in hashmap \n");

  insert_in_hash_map(my_hashmap, &sid, sizeof(sid), &vaish, sizeof(vaish));

  assert(is_in_hash_map(my_hashmap, &sid, sizeof(sid))); // should be present
  assert(!is_in_hash_map(my_hashmap, &vaish,
                         sizeof(vaish))); // should not be present

  printf("Test 2: Succesful \n");

  // Test returned value
  printf("Test 3: Check returned value \n");

  assert(compare_user(&vaish, get_value(my_hashmap, &sid, sizeof(sid))));

  printf("Test 3: Succesful \n");

  // Test replacement
  printf("Test 4: Test replacing a value \n");

  insert_in_hash_map(my_hashmap, &sid, sizeof(sid), &dad, sizeof(dad));

  assert(is_in_hash_map(my_hashmap, &sid, sizeof(sid))); // should be present
  assert(!is_in_hash_map(my_hashmap, &dad,
                         sizeof(dad))); // should not be present

  assert(compare_user(&dad, get_value(my_hashmap, &sid, sizeof(sid))));

  printf("Test 4: Succesful \n");

  // Test deletion
  printf("Test 5: Deleting a value \n");

  insert_in_hash_map(my_hashmap, &dad, sizeof(dad), &mom, sizeof(mom));
  assert(is_in_hash_map(my_hashmap, &dad, sizeof(dad))); // should be present

  remove_from_hash_map(my_hashmap, &dad, sizeof(dad));
  assert(
      !is_in_hash_map(my_hashmap, &dad, sizeof(dad))); // should not be present

  printf("Test 5: Succesful \n");

  printf("Test was succesful\n");
  return EXIT_SUCCESS;
}
