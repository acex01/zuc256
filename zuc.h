#ifndef ZUC_H
#define ZUC_H

#include <stdint.h>
#include <hls_stream.h>

/* Type definitions */
typedef unsigned char u8;
typedef unsigned int u32;

#define FIXED_SIZE 20

/* Stream data structure */
struct axis_data {
    u32 data;
    bool last;
};

/* Function prototypes */
void Initialization(u8 k[32], u8 iv[25]);
void GenerateKeystream(u32* pKeystream, u32 KeystreamLen);
void encrypt_hw(hls::stream<axis_data> &input, hls::stream<axis_data> &output, int k_param);

#endif // ZUC_H
