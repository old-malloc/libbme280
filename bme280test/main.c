/**\
 * Copyright (c) 2021 SubHumanSoftware All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

/******************************************************************************/
/*!                         Own header files                                  */

#include "bme280func.h"

/*!
 * @brief This function starts execution of the program.
 */
int main(int argc, char* argv[])
{
    struct bme280_dev dev;
    
    struct bme280_data data;
    
    int c;
    
    /* Variable to define the result */
    int8_t rslt = BME280_OK;
    
    c = 0;
    while(1)
    {
        c++;
        rslt = get_one_sample(&dev, &data);
        if (rslt != BME280_OK)
        {
            fprintf(stderr, "get_one_sample: failed to get sensor data (code %+d).\n", rslt);
            return(rslt);
        }
    
        printf("Ciclo: %i\n", c);
        print_sample(&data);
        sleep(5);
    }

    return 0;
}
