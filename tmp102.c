/* Jordan Ebel
 * July 2017   
 */

#include "tmp102.h"

static IO_SPA_I2C_PARAMS params;

TMP102_RC tmp102_init(const char *bus, uint8_t addr)
{
    params.dev_addr = addr;
#ifdef PLATFORM_LINUX
    params.bus = bus;
#endif

    if (io_spa_i2c_init(&params) != IO_SPA_OK)
    {
        return TMP102_FAILURE;
    }

    return TMP102_SUCCESS;
}

TMP102_RC tmp102_read_temp(double *temp)
{
    uint8_t buf[2];
    if (io_spa_i2c_read_short(&params, 2, buf) != IO_SPA_OK)
    {
        return TMP102_FAILURE;
    }

    *temp = (((uint16_t)buf[0] << 8) + buf[1]) >> 4;
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
    io_spa_i2c_close(&params);
    return TMP102_SUCCESS;
}

