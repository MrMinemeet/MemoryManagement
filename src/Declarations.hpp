#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define KiB * 1024
#define MiB * (1024 * 1024)

/*
 * FIXME: Enabling this causes a segfault in Heap Line 18.
 * There the "fb-ToString()" causes some weird behaviour.
 * In general it seems kind of random when the segfault occurs.
 * It happens more often with the DEBUG flag enabled.
 * I don't know why this happens, maybe you can figure it out :)
*/
#define DEBUG false

#endif
