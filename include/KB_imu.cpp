#if (ARDUINO >= 100)
#include <Arduino.h>
#define WireSend(x) Wire1.write(x)
#define WireReceive() Wire1.read()
#else
#include <WProgram.h>
#define WireSend(x) Wire1.send(x)
#define WireReceive(x) Wire1.receive(x)
#endif

#include "Wire.h"
#include "KB_imu.h"
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "KB_ht16k33.h"

// Constructor:
KB_imu::KB_imu()
{
  matrix.displayBegin();
  Wire1.begin(4,5);
}

void KB_imu::begin(void) {
  Acc = new LSM303AGR_ACC_Sensor(&Wire1);
  Acc->Enable();
  Acc->EnableTemperatureSensor();
  Mag = new LSM303AGR_MAG_Sensor(&Wire1);
  Mag->Enable();
  int my_mag_x=abs(rtc_imu.getSramWord(10)-rtc_imu.getSramWord(13));
  if((my_mag_x>500)&&(my_mag_x<1000)){
	  my_mag_min = {rtc_imu.getSramWord(10),rtc_imu.getSramWord(11),rtc_imu.getSramWord(12)};
      my_mag_max = {rtc_imu.getSramWord(13),rtc_imu.getSramWord(14),rtc_imu.getSramWord(15)};
  }else{
	my_mag_min = {-567,-384,94};
    my_mag_max = {169,402,472};
  }


}

void KB_imu::set_mag_min_max(LSM303AGR_raw mag_min, LSM303AGR_raw mag_max) {
  my_mag_min = mag_min;
  my_mag_max = mag_max;
}
void KB_imu::calibrate_acc(void) {
  Serial.println("Move sensor in all directions until max/min value do not change anymore");
  // Read magnetometer LSM303AGR.

  LSM303AGR_raw acc_min = {9999, 9999, 9999};
  LSM303AGR_raw acc_max = { -9999, -9999, -9999};
  
  LSM303AGR_raw mag_min = {9999, 9999, 9999};
  LSM303AGR_raw mag_max = { -9999, -9999, -9999};
  
  LSM303AGR_sensor a ;
  LSM303AGR_sensor m ;
  long now = millis();
  matrix.printText(0, 0, " ");
  int pixel[8][8];
  int st_ok=1;
  // TODO stop automatically if no more changes
  while (st_ok) {
     int32_t accelerometer[3];
	 int32_t magnetometer[3];
     Acc->GetAxes(accelerometer);
     a = {accelerometer[0], accelerometer[1], accelerometer[2]}; 
     Mag->GetAxes(magnetometer);
     m = {magnetometer[0], magnetometer[1], magnetometer[2]};
	 
	 int x = map(a.raw.x,800,-800,0,7);
	 int y = map(a.raw.y,-800,800,0,7);
	 if((x<=7)&&(x>=0)&&(y<=7)&&(y>=0)){
		matrix.drawPixel(x, y, 1);
		pixel[x][y]=1;
		if (m.raw.x < mag_min.x) mag_min.x = m.raw.x;
		if (m.raw.x > mag_max.x) mag_max.x = m.raw.x;

		if (m.raw.y < mag_min.y) mag_min.y = m.raw.y;
		if (m.raw.y > mag_max.y) mag_max.y = m.raw.y;

		if (m.raw.z < mag_min.z) mag_min.z = m.raw.z;
		if (m.raw.z > mag_max.z) mag_max.z = m.raw.z;
	 }
	 st_ok=0;
	 int sy=0;
	 int sx=0;
	 for(sx=0;sx<8;sx++){
		delay(1);
		 for(sy=0;sy<8;sy++){
			if(pixel[sx][sy]==0){
				st_ok=1;
				// break;
			}
			delay(1);
		  }
		//delay(1);
		//if(pixel[sx][sy]==0){
				//st_ok=1;
				//break;
		//}
	 }
	 if (millis() - now > 500) {
      matrix.drawPixel(x, y, 0);
	  delay(100);
	  if((x<=7)&&(x>=0)&&(y<=7)&&(y>=0)){
		matrix.drawPixel(x, y, 1);
	  }
      now = millis();
    }
    /* 
    if (a.raw.x < acc_min.x) acc_min.x = a.raw.x;
    if (a.raw.x > acc_max.x) acc_max.x = a.raw.x;

    if (a.raw.y < acc_min.y) acc_min.y = a.raw.y;
    if (a.raw.y > acc_max.y) acc_max.y = a.raw.y;

    if (a.raw.z < acc_min.z) acc_min.z = a.raw.z;
    if (a.raw.z > acc_max.z) acc_max.z = a.raw.z;

    if (millis() - now > 1000) {
      Serial.print("Acc mins (X, Y, Z):{");
	  Serial.print(acc_min.x);
	  Serial.print(",");
	  Serial.print(acc_min.y);
	  Serial.print(",");
	  Serial.print(acc_min.z);
	  Serial.println("}");
      Serial.print("Acc maxs (X, Y, Z):{");
	  Serial.print(acc_max.x);
	  Serial.print(",");
	  Serial.print(acc_max.y);
	  Serial.print(",");
	  Serial.print(acc_max.z);
	  Serial.println("}");
      now = millis();
    } */
  }
  	matrix.printText(0, 0, " ");
	matrix.printText(0, 0, "OK");
	my_mag_min = mag_min;
    my_mag_max = mag_max;

}
void KB_imu::calibrate_compass(void) {
	/*
	  Serial.print("Mag mins (X, Y, Z):{");
	  Serial.print(rtc_imu.getSramWord(0));
	  Serial.print(",");
	  Serial.print(rtc_imu.getSramWord(1));
	  Serial.print(",");
	  Serial.print(rtc_imu.getSramWord(2));
	  Serial.println("}");
      Serial.print("Mag maxs (X, Y, Z):{");
	  Serial.print(rtc_imu.getSramWord(3));
	  Serial.print(",");
	  Serial.print(rtc_imu.getSramWord(4));
	  Serial.print(",");
	  Serial.print(rtc_imu.getSramWord(5));
	  Serial.println("}");
	  Serial.println("Move sensor in all directions until max/min value do not change anymore");
  // Read magnetometer LSM303AGR.
  */
  LSM303AGR_raw acc_min = {9999, 9999, 9999};
  LSM303AGR_raw acc_max = { -9999, -9999, -9999};
  
  LSM303AGR_raw mag_min = {9999, 9999, 9999};
  LSM303AGR_raw mag_max = { -9999, -9999, -9999};
  
  LSM303AGR_sensor a ;
  LSM303AGR_sensor m ;
  long now = millis();
  matrix.printText(0, 0, " ");
  int pixel[16][8];
  int st_ok=1;
  int count_timer=0;
  int last_x=0;
  int last_y=0;

   for(int sx=0;sx<16;sx++){
		 delay(1);
		 for(int sy=0;sy<8;sy++){
			 delay(1);
			 pixel[sx][sy]=0;
		  }
	 }
  // TODO stop automatically if no more changes
  matrix.scrollText("TILT TO FILL SCREEN");
  while (st_ok) {
     int32_t accelerometer[3];
	 int32_t magnetometer[3];
     Acc->GetAxes(accelerometer);
     a = {accelerometer[0], accelerometer[1], accelerometer[2]}; 
     Mag->GetAxes(magnetometer);
     m = {magnetometer[0], magnetometer[1], magnetometer[2]};
	 
	 int x = map(a.raw.x,800,-800,0,15);
	 int y = map(a.raw.y,-800,800,0,7);
	 if((x<=15)&&(x>=0)&&(y<=7)&&(y>=0)){
		matrix.drawPixel(x, y, 1);
		pixel[x][y]=1;
		if (m.raw.x < mag_min.x) mag_min.x = m.raw.x;
		if (m.raw.x > mag_max.x) mag_max.x = m.raw.x;

		if (m.raw.y < mag_min.y) mag_min.y = m.raw.y;
		if (m.raw.y > mag_max.y) mag_max.y = m.raw.y;

		if (m.raw.z < mag_min.z) mag_min.z = m.raw.z;
		if (m.raw.z > mag_max.z) mag_max.z = m.raw.z;
	 }
	 st_ok=0;
	 int8_t sy=0;
	 int8_t sx=0;
	 int8_t count_pixel=0;
	 for(sx=0;sx<15;sx++){
		 delay(1);
		 for(sy=0;sy<8;sy++){
			 delay(1);
			if(pixel[sx][sy]==0){
				st_ok=1;
				// break;
			}else{
				count_pixel++;
			}
		  }
	 }
	 //Serial.println(count_pixel);
	 if(count_timer>5){
		 if(count_pixel>102){
			 st_ok=0;
		 }else{
			 matrix.printText(0, 0, " ");
	         matrix.scrollText("Time Out!");
			 return;
		 }
	 }
	 if (millis() - now > 500) {
      matrix.drawPixel(x, y, 0);
	  delay(100);
	  if((x<=15)&&(x>=0)&&(y<=7)&&(y>=0)){
		matrix.drawPixel(x, y, 1);
	  }
	  if((last_x==x)&&(last_y==y)){
		  count_timer++;
	  }else{
		  count_timer=0;
	  }
	  last_x=x;
	  last_y=y;
      now = millis();
    }
	
  }
  	matrix.printText(0, 0, " ");
	matrix.printText(0, 0, "FINISH");
	delay(500);
	matrix.printText(0, 0, " ");
	my_mag_min = mag_min;
    my_mag_max = mag_max;
	rtc_imu.setSramWord(10,mag_min.x);
	rtc_imu.setSramWord(11,mag_min.y);
	rtc_imu.setSramWord(12,mag_min.z);
    rtc_imu.setSramWord(13,mag_max.x);
	rtc_imu.setSramWord(14,mag_max.y);
	rtc_imu.setSramWord(15,mag_max.z);
}
void KB_imu::calibrate_mag(void) {
  Serial.println("Move sensor in all directions until max/min value do not change anymore");
  // Read magnetometer LSM303AGR.

  LSM303AGR_raw mag_min = {9999, 9999, 9999};
  LSM303AGR_raw mag_max = { -9999, -9999, -9999};
  LSM303AGR_sensor m ;
  long now = millis();

  // TODO stop automatically if no more changes
  while (1) {
    int32_t magnetometer[3];
    Mag->GetAxes(magnetometer);
    m = {magnetometer[0], magnetometer[1], magnetometer[2]};
    if (m.raw.x < mag_min.x) mag_min.x = m.raw.x;
    if (m.raw.x > mag_max.x) mag_max.x = m.raw.x;

    if (m.raw.y < mag_min.y) mag_min.y = m.raw.y;
    if (m.raw.y > mag_max.y) mag_max.y = m.raw.y;

    if (m.raw.z < mag_min.z) mag_min.z = m.raw.z;
    if (m.raw.z > mag_max.z) mag_max.z = m.raw.z;

    if (millis() - now > 1000) {
      Serial.print("Mag mins (X, Y, Z):{");
	  Serial.print(mag_min.x);
	  Serial.print(",");
	  Serial.print(mag_min.y);
	  Serial.print(",");
	  Serial.print(mag_min.z);
	  Serial.println("}");
      Serial.print("Mag maxs (X, Y, Z):{");
	  Serial.print(mag_max.x);
	  Serial.print(",");
	  Serial.print(mag_max.y);
	  Serial.print(",");
	  Serial.print(mag_max.z);
	  Serial.println("}");
      now = millis();
    }
  }
}
int KB_imu::get_heading(void){
	// Read accelerometer LSM303AGR.
  int32_t accelerometer[3];
  Acc->GetAxes(accelerometer);
  // Read magnetometer LSM303AGR.
  int32_t magnetometer[3];
  Mag->GetAxes(magnetometer);

  LSM303AGR_sensor m = {magnetometer[0], magnetometer[1], magnetometer[2]};
  LSM303AGR_sensor a = {accelerometer[0], accelerometer[1], accelerometer[2]};
  //LSM303AGR_sensor my_mag_max = {169,402,472};
  //LSM303AGR_sensor my_mag_min = {-567,-384,94};


  //Serial.printf("m(x, y, z): (%i, %i, %i)\n", m.raw.x, m.raw.y, m.raw.z);
  //Serial.printf("a(x, y, z): (%i, %i, %i)\n", a.raw.x, a.raw.y, a.raw.z);
  //Serial.printf("Maxm(x, y, z): (%i, %i, %i)\n", my_mag_max.raw.x, my_mag_max.raw.y, my_mag_max.raw.z);
  //Serial.printf("Mina(x, y, z): (%i, %i, %i)\n", my_mag_min.raw.x, my_mag_min.raw.y, my_mag_min.raw.z);
  // use calibration values to shift and scale magnetometer measurements
  double x_mag = (0.0 + m.raw.x - my_mag_min.x) / (my_mag_max.x - my_mag_min.x) * 2 - 1;
  double y_mag = (0.0 + m.raw.y - my_mag_min.y) / (my_mag_max.y - my_mag_min.y) * 2 - 1;
  double z_mag = (0.0 + m.raw.z - my_mag_min.z) / (my_mag_max.z - my_mag_min.z) * 2 - 1;
  //Serial.printf("Mag norm (x, y, z): (%f, %f, %f)\n", x_mag, y_mag, z_mag);

  // Normalize acceleration measurements so they range from 0 to 1
  double s = sqrt(pow(a.raw.x, 2) + pow(a.raw.y, 2) + pow(a.raw.z, 2));
  double xAccelNorm = a.raw.x / s;
  double yAccelNorm = a.raw.y / s;
  //DF("Acc norm (x, y): (%f, %f)\n", xAccelNorm, yAccelNorm);

  //double pitch = asin(-xAccelNorm);
  //double roll = asin(yAccelNorm / cos(pitch));
  
  double pitch = asin(-xAccelNorm);
  double roll = asin(yAccelNorm / cos(pitch));

  // tilt compensated magnetic sensor measurements
  double x_mag_comp = x_mag * cos(pitch) + z_mag * sin(pitch);
  double y_mag_comp = x_mag * sin(roll) * sin(pitch) + y_mag * cos(roll) - z_mag * sin(roll) * cos(pitch);

  // arctangent of y/x converted to degrees
  //double heading = 180 * atan2(y_mag_comp, x_mag_comp) / PI;
  double heading = 180 * atan2(x_mag_comp,y_mag_comp) / PI;

  if (heading <= 0) {
    heading = - heading;
  } else {
    heading = 360  - heading;
 }
if(heading>360){
   return compass_heading;
}else{
	compass_heading=heading;
   return heading;
}

}
int KB_imu::get_acc_xyz(int index_a){
  int32_t accelerometer[3];
  Acc->GetAxes(accelerometer);
  if(index_a==0){
    return -accelerometer[index_a];
  }else if(index_a==1){
	return -accelerometer[index_a];
  }else if(index_a==2){
	return -accelerometer[index_a];
  }else if(index_a==3){
	return  sqrt(pow(accelerometer[0], 2) + pow(accelerometer[1], 2) + pow(accelerometer[2], 2));
  }
  
}
