//use the hideakitai  library (https://github.com/hideakitai)
#include "MPU9250.h"

MPU9250 mpu;

//this structure is needed by hatire
struct  {
int16_t  Begin  ;   // begin
uint16_t Cpt ;      // Frame Number or Error code
float    gyro[3];   // [Y, P, R] Yaw, Pitch, Roll
float    acc[3];    // [x, y, z] Displacements
int16_t  End ;      // end
} hat;

void setup()
{
Serial.begin(115200);
    
Wire.begin();
    
while (!Serial && (millis() < 30000)); //WARNING: comment if you DO NOT use a micro/leonardo board.

mpu.setup(0x68);
    
// set here the mag. declination for your country  http://www.magnetic-declination.com
//mpu.setMagneticDeclination(3.57);
mpu.setMagneticDeclination(4.10);
    
// header frame for hatire
hat.Begin=0xAAAA;
// Frame Number or Error code
hat.Cpt=0;
// footer frame for hatire
hat.End=0x5555;
  
/* 1) load the calibration script and open the terminal, leave the MPU on the table without move it;
   2) the magnetometer now, it says to draw some eight. Move it drawing a sphere, fast you move more data you'll get.
   3) replace my values, with yours. DO NOT use the accelerometer values.*/

/*
Please leave the device still on the flat plane.
Mag calibration will start in 5sec.
Please Wave device in a figure eight until done.
Mag Factory Calibration Values: 
X-Axis sensitivity offset value 1.19
Y-Axis sensitivity offset value 1.20
Z-Axis sensitivity offset value 1.15
Mag Calibration: Wave device in a figure eight until done!
mag x min/max:
202
-154
mag y min/max:
320
-228
mag z min/max:
207
-353
Mag Calibration done!
AK8963 mag biases (mG)
42.87, 82.44, -125.70
AK8963 mag scale (mG)
1.37, 0.89, 0.87
Mag Factory Calibration Values: 
X-Axis sensitivity offset value 1.19
Y-Axis sensitivity offset value 1.20
Z-Axis sensitivity offset value 1.15
< calibration parameters >
accel bias [g]: 
-126.06, 39.01, 11.62
gyro bias [deg/s]: 
-2.91, 1.67, 0.16
mag bias [mG]: 
42.87, 82.44, -125.70
mag scale []: 
1.37, 0.89, 0.87

 */
        
//mpu.setAccBias(+78.75, 144.67, -201.21);  //x, y, z   
//mpu.setAccBias(-126.06, 39.01, 11.62);  //x, y, z   
//mpu.setGyroBias(-5.89, -3.20, -1.81);     //x, y, z
mpu.setGyroBias(-2.91, 1.67, 0.16);     //x, y, z
// mpu.setMagBias(+104.97, +57.91, -418.89); //x, y, z
mpu.setMagBias(42.87, 82.44, -125.70); //x, y, z
//mpu.setMagScale(+1.24, +0.94, +0.89);     //x, y, z
mpu.setMagScale(1.37, 0.89, 0.87);     //x, y, z
}

void loop()
{ 
static uint32_t prev_ms = millis();
if ((millis() - prev_ms) > 16)
{
mpu.update();
//mpu.print();

/*THIS IS COMMENTED, use it to read values of pitch, yaw, roll. 
Serial.print("roll(x-forward (north)): ");
Serial.print(mpu.getRoll());
Serial.println();
Serial.print("pitch(y-right (east)): ");
Serial.print(mpu.getPitch());
Serial.println();
Serial.print("yaw(z-down (down)): ");
Serial.print(mpu.getYaw());
Serial.println();*/

/*hat.acc[0]=((mpu.getAccX()*pow((millis() - prev_ms),2.0)))/98066500; // 1 milliG=9.80665 m/s^2.
hat.acc[1]=((mpu.getAccY()*pow((millis() - prev_ms),2.0)))/98066500; //displacements are in cm.
hat.acc[2]=((mpu.getAccZ()*pow((millis() - prev_ms),2.0)))/98066500;*/

//comment these if you want to read pitch, yaw, roll
hat.gyro[0]=mpu.getYaw();
hat.gyro[1]=mpu.getPitch();
hat.gyro[2]=mpu.getRoll();
  
prev_ms = millis();
      
// Send HAT Frame to PC
Serial.write((byte*)&hat,30);
hat.Cpt++;
if (hat.Cpt>999) 
{
hat.Cpt=0;
}
}
}
