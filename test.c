/* Jordan Ebel
 * July 2017   
 */

#include "tmp102.h"

static const char *I2C_BUS="/dev/i2c-1";
static const int I2C_ADDR = 0x48;

int main(int argv, char **argc)
{
    double temp = 0.0;

    if (tmp102_init(I2C_BUS, I2C_ADDR) != TMP102_SUCCESS)
    {
        return 1;
    }

    if (tmp102_read_temp_f(&temp) != TMP102_SUCCESS)
    {
        tmp102_close();
        return 1;
    }

    printf("temp : %f\n", temp);

    tmp102_close();
    return 0;
}

