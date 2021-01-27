/**\
 * Copyright (c) 2021 SubHumanSoftware All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/
 
#ifndef BME280F_H_
#define BME280F_H_

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

#include "linux_userspace.h"

int8_t get_sensor_data_forced_mode(struct bme280_dev *dev, struct bme280_data *data);

int8_t get_one_sample(struct bme280_dev *dev, struct bme280_data *data);

void print_sample(struct bme280_data *comp_data);

#ifdef __cplusplus
}
#endif /* End of CPP guard */
#endif /* BME280F_H_ */
/** @}*/
