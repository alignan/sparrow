/*
 * Copyright (c) 2016-2016, Yanzi Networks
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COMPANY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 */

#ifndef I2C_DEV_H_
#define I2C_DEV_H_

#include "contiki-conf.h"
#include "dev/bus-status.h"
#include <stdint.h>

#ifdef PLATFORM_HAS_I2C_ARCH
#include "i2c-arch.h"
#endif

#define I2C_NORMAL_BUS_SPEED  100000  /* 100KHz I2C */
#define I2C_FAST_BUS_SPEED    400000  /* 400KHz I2C */

typedef struct i2c_device i2c_device_t;

/* Timer / timing */
typedef struct {
  i2c_device_t *lock_device;
  volatile uint8_t lock; /* for locking the bus */
#ifdef PLATFORM_HAS_I2C_ARCH
  i2c_bus_config_t config;
#endif
} i2c_bus_t;

/* Timing... */
struct i2c_device {
  i2c_bus_t *bus;
  uint32_t speed;
  uint16_t timeout; /* timeout in milliseconds for this device */
  uint8_t address;
};

/* call for all i2c devices */
int     i2c_dev_has_bus(const i2c_device_t *dev);
uint8_t i2c_dev_acquire(i2c_device_t *dev);
uint8_t i2c_dev_release(i2c_device_t *dev);
uint8_t i2c_dev_restart_timeout(i2c_device_t *dev);
uint8_t i2c_dev_write_byte(i2c_device_t *dev, uint8_t data);
uint8_t i2c_dev_read_byte(i2c_device_t *dev, uint8_t *data);
uint8_t i2c_dev_write(i2c_device_t *dev, const uint8_t *data, int size);
uint8_t i2c_dev_read(i2c_device_t *dev, uint8_t *data, int size);
uint8_t i2c_dev_stop(i2c_device_t *dev);

uint8_t i2c_dev_write_register(i2c_device_t *dev, uint8_t reg, uint8_t value);
uint8_t i2c_dev_write_register_buf(i2c_device_t *dev, uint8_t reg,
                                   const uint8_t *data, int size);

uint8_t i2c_dev_read_register(i2c_device_t *dev, uint8_t reg,
                              uint8_t *data, int size);

/* Arch functions needed per CPU */
uint8_t i2c_arch_lock(i2c_device_t *dev);
uint8_t i2c_arch_unlock(i2c_device_t *dev);
uint8_t i2c_arch_restart_timeout(i2c_device_t *dev);

uint8_t i2c_arch_read(i2c_device_t *dev, uint8_t *data, int len);
uint8_t i2c_arch_write(i2c_device_t *dev, const uint8_t *data, int len);
uint8_t i2c_arch_stop(i2c_device_t *dev);

#endif /* I2C_DEV_H_ */