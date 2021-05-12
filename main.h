/* main.h -- global definitions for main task.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Wed May 12 17:52:12 EEST 2021
 * Copyright: (C) 2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#define F(_fmt) __FILE__":%d:%s:" _fmt, __LINE__, __func__

#define P(_dst, _fmt, ...) do {                 \
        fprintf((_dst), _fmt, ##__VA_ARGS__);   \
    } while (0)

#define INFO(_fmt, ...) do {                    \
        P(stdout,                               \
            F("INFO: "_fmt),                    \
            ##__VA_ARGS__);                     \
    } while (0)

#define LOG(_fmt, ...) do {                     \
        if (conf_flags & FLAG_VERBOSE) {        \
            P(stderr,                           \
                F("LOG: "_fmt),                 \
                ##__VA_ARGS__);                 \
        }                                       \
    } while (0)

#define WARN(_fmt, ...) do {                    \
        P(stderr,                               \
            F("WARN: "_fmt),                    \
            ##__VA_ARGS__);                     \
    } while (0)

#define ERR(_code, _fmt, ...) do {              \
        P(stderr,                               \
                F("ERR: "_fmt),                 \
                ##__VA_ARGS__);                 \
        if (_code)  exit(_code);                \
    } while (0)

#define FLAG_BINARY     (1 << 0)
#define FLAG_VERBOSE    (1 << 1)
#define FLAG_HELP       (1 << 2)

#define STATUS_OK		0
#define STATUS_CMDLINE	1
#define STATUS_OPENFIL	2
#define STATUS_PROCESS	3

extern int conf_flags;
