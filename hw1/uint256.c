#include "uint256.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a UInt256 value from a single uint32_t value.
// Only the least-significant 32 bits are initialized directly,
// all other bits are set to 0.
UInt256 uint256_create_from_u32(uint32_t val) {
  UInt256 result;
  // Initialize all words to 0, except for the least significant word.
  for (int i = 1; i < 8; i++) {
    result.data[i] = 0;
  }

  result.data[0] = val;
  return result;
}

// Create a UInt256 value from an array of NWORDS uint32_t values.
// The element at index 0 is the least significant, and the element
// at index 7 is the most significant.
UInt256 uint256_create(const uint32_t data[8]) {
  UInt256 result;

  for (int i = 0; i < 8; i++) {
    result.data[i] = data[i];
  }

  return result;
}

// Create a UInt256 value from a string of hexadecimal digits.
// test hex strings less than 64 characters
UInt256 uint256_create_from_hex(const char *hex) {
  UInt256 result;
  // need 65 characters to include the null terminator
  char temp[65];
  // case  *hex >= 64 hex digits
  // if less than 64 hex digits pad with zeroes
  int num_zeroes =
      64 - strlen(hex);  // need to test when string has 63 characters
  if (num_zeroes >= 0) {
    memset(temp, '0', num_zeroes);
    temp[num_zeroes] = '\0';
    strcat(temp, hex);
  } else {
    temp[64] = '\0';  // add null terminator to the end
    int offset = strlen(hex) - 64;
    strncpy(temp, hex + offset, 64);
  }

  // convert hex to uint32
  for (int i = 0; i < 8; i++) {
    int lastIndex = strlen(temp) - 1;
    int startIndex = lastIndex - 7 * (i + 1);

    // hexadec buffer
    char hexChar_section[9];
    strncpy(hexChar_section, temp + startIndex,
            8);  // 0-7 are chars, 8 is null term
    hexChar_section[8] = '\0';

    uint32_t val = (uint32_t)strtoul(hexChar_section, NULL, 16);
    result.data[i] = val;
  }
  return result;
}

// Return a dynamically-allocated string of hex digits representing the
// given UInt256 value.
char *uint256_format_as_hex(UInt256 val) {
  char *hex = NULL;
  char *buf = (char *)malloc(65 * sizeof(char));
  if (buf == NULL) {
    printf("Memory allocation failed \n");
    return NULL;
  }
  // extract first element in U256
  for (int i = 0; i < 8; i++) {
    int buf_index = 8;

    uint32_t value = val.data[i];
    // convert to hexadecimal
    // store in char buf (starting at last index to represent least sig digit)
    sprintf(buf + i, "%X", value);
    hex[i] = buf[buf_index];
    buf_index--;
  }
  printf(" hex contents: %s \n", hex);
  

  free(buf);
  return hex;
}

// Get 32 bits of data from a UInt256 value.
// Index 0 is the least significant 32 bits, index 7 is the most
// significant 32 bits.
uint32_t uint256_get_bits(UInt256 val, unsigned index) {
  uint32_t bits;
  bits = val.data[index];
  return bits;
}

// Compute the sum of two UInt256 values.
// no need to handle Uint256max * 2
// create tests for
UInt256 uint256_add(UInt256 left, UInt256 right) {
  UInt256 sum;
  uint32_t carry = 0;

  for (int i = 0; i < 8; i++) {
    // uint32_t MAX32 = 0xFFFFFFFFU;
    uint32_t leftval = left.data[i];
    uint32_t rightval = right.data[i];
    uint32_t sumval = leftval + rightval + carry;
    // if overflow occurs
    if (sumval < leftval || sumval < rightval) {
      carry = 1;
    } else {
      carry = 0;
    }

    sum.data[i] = sumval;
  }
  return sum;
}

// Compute the difference of two UInt256 values.
UInt256 uint256_sub(UInt256 left, UInt256 right) {
  UInt256 result;
  UInt256 right_neg = uint256_negate(right);

  result = uint256_add(left, right_neg);
  return result;
}

// Return the two's-complement negation of the given UInt256 value.
UInt256 uint256_negate(UInt256 val) {
  UInt256 result;
  UInt256 one = {1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
  uint32_t val_data;
  uint32_t carry = 0;

  for (int j = 0; j < 8; j++) {
    // get val at jth element of uint256
    // manipulate bits at jth element
    val_data = val.data[j];
    val_data += carry;
    for (int i = 0; i < 32; i++) {
      // extract bit
      uint32_t bit = (val_data >> i) & 1;
      // invert
      if (bit == 1) {
        val_data &= ~(1 << i);
      } else {
        val_data |= (1 << i);
      }
    }
    result.data[j] = val_data;
  }
  result = uint256_add(result, one);

  return result;
}

// Return the result of rotating every bit in val nbits to
// the left.  Any bits shifted past the most significant bit
// should be shifted back into the least significant bits.
UInt256 uint256_rotate_left(UInt256 val, unsigned nbits) {
  UInt256 result;
  // TODO: implement
  return result;
}

// Return the result of rotating every bit in val nbits to
// the right. Any bits shifted past the least significant bit
// should be shifted back into the most significant bits.
UInt256 uint256_rotate_right(UInt256 val, unsigned nbits) {
  UInt256 result;
  // TODO: implement
  return result;
}