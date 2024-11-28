#include <bootloader.h>
#include <ext2.h>
#include <malloc.h>
#include <paging.h>
#include <string.h>
#include <system.h>
#include <task.h>
#include <timer.h>
#include <util.h>

bool ext2Mount(MointPoint *mount)
{
    mount->handlers = &ext2Handlers;
    mount->stat = ext2Stat;
    mount->lstat = ext2Lstat;
    mount->mkdir = ext2Mkdir;

}