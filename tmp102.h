/* Jordan Ebel
 * July 2017   
 */

#ifndef _TMP_102_H
#define _TMP_102_H

#include "i2c_spa.h"

static const double TMP102_RESOLUTION=0.0625;

typedef enum 
{
    TMP102_SUCCESS,
    TMP102_FAILURE
} TMP102_RC;

TMP102_RC tmp102_init(const char *bus, uint8_t addr);
TMP102_RC tmp102_read_temp(double *temp);
TMP102_RC tmp102_read_temp_f(double *temp);
TMP102_RC tmp102_close();

#endif  /* _TMP_102_H */

