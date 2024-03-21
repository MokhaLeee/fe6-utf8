#include "prelude.h"
#include "proc.h"
#include "hardware.h"
#include "util.h"

#define gPaletteOpAnimHsBackup ((u16 *)0x02000000)

struct ProcEarlyUI {
    PROC_HEADER;

    int timer;
};

static void InitNintendoGfx(struct ProcEarlyUI * proc)
{
    return;
}

const struct ProcScr ProcScr_GameIntroEarlyUI[] = {
    PROC_SLEEP(0),
    PROC_CALL(InitNintendoGfx),
    PROC_END
};
