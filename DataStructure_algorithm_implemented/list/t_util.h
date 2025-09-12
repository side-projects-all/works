#ifndef T_UTIL_H
#define T_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

static inline int cmpint(const void *p1, const void *p2)
{
    const uint16_t *i1 = (const uint16_t *) p1;
    const uint16_t *i2 = (const uint16_t *) p2;
    return *i1 - *i2;
}

#ifdef __cplusplus
}
#endif
#endif /* T_UTIL_H */