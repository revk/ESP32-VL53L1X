// VL53L0X control
// Copyright Â ©2019 Adrian Kennard, Andrews & Arnold Ltd.See LICENCE file for details
   .GPL 3.0

#ifndef VL53L0X_H
#define VL53L0X_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

      typedef struct vl53l1x_s vl53l1x_t;

enum DistanceMode
{
   VL53L1X_Short, VL53L1X_Medium, VL53L1X_Long, VL53L1X_Unknown
};

enum
{
   VL53L1X_RangeValid = 0,
   VL53L1X_SigmaFail = 1,
   VL53L1X_SignalFail = 2,
   VL53L1X_RangeValidMinRangeClipped = 3,
   VL53L1X_OutOfBoundsFail = 4,
   VL53L1X_HardwareFail = 5,
   VL53L1X_RangeValidNoWrapCheckFail = 6,
   VL53L1X_WrapTargetFail = 7,
   VL53L1X_ProcessingFail = 8,
   VL53L1X_XtalkSignalFail = 9,
   VL53L1X_SynchronizationInt = 10,
   VL53L1X_RangeValid MergedPulse = 11,
   VL53L1X_TargetPresentLackOfSignal = 12,
   VL53L1X_MinRangeFail = 13,
   VL53L1X_RangeInvalid = 14,
   VL53L1X_None = 255,
};

                vl53l1x_t * vl53l1x_config(int8_t port, int8_t scl, int8_t sda, int8_t xshut, uint8_t address, uint8_t io_2v8);
const char     *vl53l1x_init(vl53l1x_t *);
void            vl53l1x_end(vl53l1x_t *);

void            vl53l1x_setAddress(vl53l1x_t *, uint8_t new_addr);
uint8_t         vl53l1x_getAddress(vl53l1x_t * v);

void            vl53l1x_writeReg8Bit(vl53l1x_t *, uint8_t reg, uint8_t value);
void            vl53l1x_writeReg16Bit(vl53l1x_t *, uint8_t reg, uint16_t value);
void            vl53l1x_writeReg32Bit(vl53l1x_t *, uint8_t reg, uint32_t value);
uint8_t         vl53l1x_readReg8Bit(vl53l1x_t *, uint8_t reg);
uint16_t        vl53l1x_readReg16Bit(vl53l1x_t *, uint8_t reg);
uint32_t        vl53l1x_readReg32Bit(vl53l1x_t *, uint8_t reg);

void            vl53l1x_writeMulti(vl53l1x_t *, uint8_t reg, uint8_t const *src, uint8_t count);
void            vl53l1x_readMulti(vl53l1x_t *, uint8_t reg, uint8_t * dst, uint8_t count);


bool            vl53l1x_setDistanceMode(DistanceMode mode);
DistanceMode
vl53l1x_getDistanceMode()
{
   return distance_mode;
}

bool            vl53l1x_setMeasurementTimingBudget(uint32_t budget_us);
uint32_t        vl53l1x_getMeasurementTimingBudget();

void            vl53l1x_setROISize(uint8_t width, uint8_t height);
void            vl53l1x_getROISize(uint8_t * width, uint8_t * height);
void            vl53l1x_setROICenter(uint8_t spadNum);
uint8_t         vl53l1x_getROICenter();

void            vl53l1x_startContinuous(uint32_t period_ms);
void            vl53l1x_stopContinuous();
uint16_t        vl53l1x_read(bool blocking = true);
uint16_t 
vl53l1x_readRangeContinuousMillimeters(bool blocking = true)
{
   return read(blocking);
} //alias of read()
   uint16_t        vl53l1x_readSingle(bool blocking = true);
   uint16_t        vl53l1x_readRangeSingleMillimeters(bool blocking = true)
{
   return readSingle(blocking);
} //alias of readSingle()

// check if sensor
   has new reading available
      // assumes interrupt is active low(GPIO_HV_MUX__CTRL bit 4 is 1)
   bool            vl53l1x_dataReady()
{
   return (readReg(GPIO__TIO_HV_STATUS) & 0x01) == 0;
}

static const char *vl53l1x_rangeStatusToString(RangeStatus status);

void
vl53l1x_setTimeout(uint16_t timeout)
{
   io_timeout = timeout;
}
uint16_t
vl53l1x_getTimeout()
{
   return io_timeout;
}
bool            vl53l1x_timeoutOccurred();
