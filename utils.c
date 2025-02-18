#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_binary_value(int number, int byte_count) {
  char *num_str = (char *)malloc((byte_count * 8 + 1) * sizeof(char));
  int idx = 0;
  memset(num_str, '0', (byte_count*8));
  num_str[(byte_count*8)] = '\0';

  while (number != 0) {
    num_str[idx] = (number % 2 == 1 ? '1' : '0');
    idx += 1;
    number /= 2;
  }
  return num_str;
}

char* get_binary_message(char* message) {
  int str_size = strlen(message);
  char *msg_str = (char *)malloc(8*str_size + 1);
  for(int i = 0; i < str_size; i++) {
    int curr_char = message[i];
    char* curr_char_val = get_binary_value(curr_char, 1);
    int char_size = strlen(curr_char_val);
    for(int j = 0; j < char_size; j++) {
      msg_str[j+i*8] = curr_char_val[j];
    }
  }
  msg_str[8*str_size] = '\0';
  return msg_str;
}

char* parse_binary_message(char* message, int byte_count) {
  int char_size = byte_count * 8;
  int char_count = strlen(message) / char_size;
  char* result = (char*)malloc(char_count + 1);
  // for all the characters that are possible, I would start from the last bit and try constructing the number possible.
  printf("(%d, %d, %d)", strlen(message), char_size, char_count);
  for(int i = 1; i <= char_count; i++) {
    int char_value = 0;
    for(int j = i*char_size - 1; j >= (i-1)*char_size; j--) {
      char_value *= 2;
      if(message[j] == '1') {
        char_value += 1;
      }
    }
    char result_char = (char)char_value;
    result[i-1] = result_char;
  }
  result[char_count] = '\0';
  return result;
}

int parse_binary_count(char* message, int byte_count) {
  int char_size = byte_count * 8;
  int num_count = strlen(message) / char_size;
  int* result = (int*)malloc(num_count);
  for(int i = 1; i <= num_count; i++) {
    int curr_value = 0;
    for(int j = i*char_size - 1; j >= (i-1)*char_size; j--) {
      curr_value *= 2;
      if(message[j] == '1') {
        curr_value += 1;
      }
    }
    result[i-1] = curr_value;
  }
  return result[0];
}
