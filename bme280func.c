/**\
 * Copyright (c) 2021 SubHumanSoftware All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

/******************************************************************************/
/*!                         System header files                               */
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
 * @brief This API reads the sensor temperature, pressure and humidity data in forced mode only one time.
 */
int8_t get_sensor_data_forced_mode(struct bme280_dev *dev, struct bme280_data *data)
{
    /* Variable to define the result */
    int8_t rslt = BME280_OK;

    /* Variable to define the selecting sensors */
    uint8_t settings_sel = 0;

    /* Variable to store minimum wait time between consecutive measurement in force mode */
    uint32_t req_delay;

    /* Structure to get the pressure, temperature and humidity values */
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_1X;
    dev->settings.osr_t = BME280_OVERSAMPLING_1X;
    dev->settings.filter = BME280_FILTER_COEFF_OFF;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    /* Set the sensor settings */
    rslt = bme280_set_sensor_settings(settings_sel, dev);
    if (rslt != BME280_OK)
    {
        fprintf(stderr, "Failed to set sensor settings (code %+d).", rslt);

        return rslt;
    }

    /*Calculate the minimum delay required between consecutive measurement based upon the sensor enabled
     *  and the oversampling configuration. */
    req_delay = bme280_cal_meas_delay(&dev->settings)*1000;
    
    /* Set the sensor to forced mode */
    rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
    if (rslt != BME280_OK) 
    {
	fprintf(stderr, "Failed to set sensor mode (code %+d).", rslt);
	return rslt;
    }

    /* Wait for the measurement to complete and print data */
    dev->delay_us(req_delay, dev->intf_ptr);
    rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        
    if (rslt != BME280_OK) 
    {
	fprintf(stderr, "Failed to get sensor data (code %+d).", rslt);
	return rslt;
    }
    
    data->temperature = comp_data.temperature;
    data->pressure = comp_data.pressure;
    data->humidity = comp_data.humidity;
    

    return rslt;
}

/*!
 * @brief This function opens the device, gets one sample of data from the sensor and closes the device.
 */
int8_t get_one_sample(struct bme280_dev *dev, struct bme280_data *data)
{

    struct identifier id;

    /* Variable to define the result */
    int8_t rslt = BME280_OK;

    if ((id.fd = open("/dev/i2c-1", O_RDWR)) < 0)
    {
        fprintf(stderr, "get_data_forced_mode: failed to open the i2c bus, error %i\n", id.fd);
        return(1);
    }

    /* Make sure to select BME280_I2C_ADDR_PRIM or BME280_I2C_ADDR_SEC as needed */
    id.dev_addr = BME280_I2C_ADDR_PRIM;
    //id.dev_addr = BME280_I2C_ADDR_SEC;
    
    if (ioctl(id.fd, I2C_SLAVE, id.dev_addr) < 0)
    {
        fprintf(stderr, "Failed to acquire bus access and/or talk to slave.\n");
        return(1);
    }

    dev->intf = BME280_I2C_INTF;
    dev->read = user_i2c_read;
    dev->write = user_i2c_write;
    dev->delay_us = user_delay_us;

    /* Update interface pointer with the structure that contains both device address and file descriptor */
    dev->intf_ptr = &id;

    /* Initialize the bme280 */
    rslt = bme280_init(dev);
    if (rslt != BME280_OK)
    {
        fprintf(stderr, "Failed to initialize the device (code %+d).\n", rslt);
        return(rslt);
    }

    rslt = get_sensor_data_forced_mode(dev, data);
    if (rslt != BME280_OK)
    {
        fprintf(stderr, "Failed to stream sensor data (code %+d).\n", rslt);
        return(rslt);
    }
    
    if ( close(id.fd) < 0)
    {
        fprintf(stderr, "get_data_forced_mode: Failed to close the i2c bus\n");
        return(1);
    }

    return rslt;
}

/*!
 * @brief This function prints data sample.
 */
void print_sample(struct bme280_data *comp_data)
{
    print_sensor_data(comp_data);
}
