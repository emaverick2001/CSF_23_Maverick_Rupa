#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint8_t add_8bit(uint8_t left,uint8_t right){
    uint8_t result = 0; // Initialize the result to 0
    int carry = 0; // Initialize the carry to 0

    for (int i = 0; i < 8; i++) {
        // Use bitwise AND to check the i-th bit
        int lbit = (left >> i) & 1;
        int rbit = (right >> i) & 1;

        // Calculate the sum and carry for this bit
        int sum = lbit ^ rbit ^ carry;
        carry = (lbit & rbit) | (carry & (lbit ^ rbit));

        // Set the i-th bit in the result
        result |= (sum << i);
    }

    return result;
}

int main() {
    // // Input hexadecimal string
    // const char* hexString = "0xAB0478C9EF";

    // // Use strtoull to convert the hexadecimal string to uint64_t
    // char* endPtr;
    // uint32_t result = (uint32_t)strtoull(hexString, &endPtr, 16);
    // uint32_t result2 = (uint32_t)strtoull(endPtr, &endPtr, 16);

    // // Check for conversion errors
    // if (*endPtr != '\0') {
    //     printf("Conversion error: Not a valid hexadecimal number\n");
    //     return 1;
    // }

    // // Print the result
    // printf("Hexadecimal String: %s\n", hexString);
    // printf("Equivalent uint64_t: %" PRIu64 "\n", result);

    unsigned int num = 7; // Example: 7 (binary: 0111)

    uint8_t a = 3; // Example: 170 (in decimal)
    uint8_t b = 1; // Example: 204 (in decimal)

    uint8_t sum = add_8bit(a, b);

    printf("Sum: %d\n", sum); // Expected output: 118 (in decimal)


    return 0;
}