#ifndef KB_imu_h
#define KB_imu_h

//#include <Arduino.h>
#include <Wire.h>
#include "LSM303AGR_ACC_Sensor.h"
#include "LSM303AGR_MAG_Sensor.h"
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "KB_ht16k33.h"
#include "MCP7941x.h"
// Various
#define GRAVITY (9.80665F)



typedef struct {
  int16_t x;
  int16_t y;
  int16_t z;
} LSM303AGR_raw;

typedef struct {
  LSM303AGR_raw raw;
  float x;
  float y;
  float z;
} LSM303AGR_sensor;

class KB_imu
{
 public:
	KB_imu();
	void begin(void);
	int get_heading(void);
	void set_mag_min_max(LSM303AGR_raw mag_min, LSM303AGR_raw mag_max);
	int get_acc_xyz(int index_a);
	void calibrate_mag(void);
	void calibrate_acc(void);
	void calibrate_compass(void);
 protected:
	// Components.
	LSM303AGR_ACC_Sensor *Acc;
	LSM303AGR_MAG_Sensor *Mag;
	KB_8x16Matrix matrix = KB_8x16Matrix();
	MCP7941x rtc_imu = MCP7941x();
	int compass_heading;
 private:
	LSM303AGR_raw my_mag_min;
	LSM303AGR_raw my_mag_max;
};

#endif /* KB_COMPASS_h */