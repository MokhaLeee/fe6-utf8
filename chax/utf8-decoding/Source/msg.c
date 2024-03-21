#include "prelude.h"
#include "msg.h"
#include "text.h"
#include "armfunc.h"

#include "decoding.h"

extern u8 const * const * const gpMsgTable;

/* LynJump */
char * DecodeMsg(int id)
{
    u32 addr;
    const u8 * src;

    if (id == sActiveMsg)
        return sMsgString;

    addr = (u32)gpMsgTable[id];
    src = (const u8 *)(addr & (~0xF0000000));

    if (IS_ANTI_HUFFMAN(addr))
    {
        /* We assume that external anti-huffman text are all utf8 encoded */
        strcpy(sMsgString, (const char *)src);
    }
    else
    {
        /* We assume that the huffman compressed text are all vanilla shift-JIS encoded */
        DecodeString((const char *)src, sMsgString);
        Sjis2Utf8(sMsgString, sizeof(sMsgString));
    }

    sActiveMsg = id;
    return sMsgString;
}
