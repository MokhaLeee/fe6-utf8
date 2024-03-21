#pragma once

#include "prelude.h"
#include <string.h>

#define IS_ANTI_HUFFMAN(ptr) ((((u32)(ptr)) & 0xFF000000) == 0x88000000)

/* msg.c */
extern u8 const * const gMsgTable[];
extern char sMsgString[0x1000];
extern int sActiveMsg;

int DecodeUtf8(const char * str, u32 * unicode_out, int * len);
void Sjis2Utf8(char * buf, int len);
