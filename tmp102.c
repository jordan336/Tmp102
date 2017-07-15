/* Jordan Ebel
 * July 2017   
 */

#include "tmp102.h"

static I2C_SPA_PARAMS params;

TMP102_RC tmp102_init(const char *bus, uint8_t addr)
{
    params.dev_addr = addr;
#ifdef PLATFORM_LINUX
    params.bus = bus;
#endif

    if (i2c_spa_init(&params))
    {
        return TMP102_FAILURE;
    }

    return TMP102_SUCCESS;
}

TMP102_RC tmp102_read_temp(double *temp)
{
    uint8_t buf[2];
    if (i2c_spa_read(&params, 2, buf) != I2C_SPA_OK)
    {
        return TMP102_FAILURE;
    }

    *temp = (((uint16_t)buf[1] << 8) + buf[0]) >> 4;
    *temp *= TMP102_RESOLUTION;

    return TMP102_SUCCESS;
}

TMP102_RC tmp102_read_temp_f(double *temp)
{
    TMP102_RC rc = TMP102_SUCCESS;
    if ((rc = tmp102_read_temp(temp)) != TMP102_SUCCESS)
    {
        return rc;
    }

    *temp = *temp * 1.8 + 32.0;

    return TMP102_SUCCESS;
}

TMP102_RC tmp102_close()
{
    i2c_spa_close(&params);
    return TMP102_SUCCESS;
}

