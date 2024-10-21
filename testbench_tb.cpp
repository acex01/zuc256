#include "ZUC.h"
#include <stdio.h>
#include <stdint.h>

int main()
{
    const int DATA_LEN = 8000;  // Process 8000 data units
    hls::stream<axis_data> input_data;
    hls::stream<axis_data> output_data;

    // Expected keystream words (only for the first 20)
    u32 expected_keystream[20] = {
        0x3356cbae, 0xd1a1c18b, 0x6baa4ffe, 0x343f777c, 0x9e15128f,
        0x251ab65b, 0x949f7b26, 0xef7157f2, 0x96dd2fa9, 0xdf95e3ee,
        0x7a5be02e, 0xc32ba585, 0x505af316, 0xc2f9ded2, 0x7cdbd935,
        0xe441ce11, 0x15fd0a80, 0xbb7aef67, 0x68989416, 0xb8fac8c2
    };

    // Initialize input data (dummy values since we are verifying keystream)
    for (int i = 0; i < DATA_LEN; i++) {
        axis_data temp;
        temp.data = 0;  // Using 0 as a placeholder since we're only testing keystream
        temp.last = (i == DATA_LEN - 1) ? true : false;
        input_data.write(temp);
    }

    // Perform encryption (in this case, just generating the keystream)
    encrypt_hw(input_data, output_data, 10);

    // Read from output stream and verify only the first 20 keystreams
    bool success = true;
    for (int i = 0; i < DATA_LEN; i++) {
        axis_data temp = output_data.read();

        // Verify only the first 20 keystreams
        if (i < 20) {
            printf("Keystream[%d]: 0x%08x\n", i, temp.data);
            if (temp.data != expected_keystream[i]) {
                printf("Mismatch at index %d: expected 0x%08x, got 0x%08x\n", i, expected_keystream[i], temp.data);
                success = false;
            }
        }

        if (temp.last) {
            break; // Exit the loop if 'last' is true
        }
    }

    // Check the test result for the first 20 keystream words
    if (success) {
        printf("Test passed: First 20 keystreams match expected output.\n");
    } else {
        printf("Test failed: First 20 keystreams do not match expected output.\n");
    }

    return 0;
}
