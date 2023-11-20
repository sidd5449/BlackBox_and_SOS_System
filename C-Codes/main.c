#include <lpc214x.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "GPS.h"
#include "GSM.c"
#include "IMU.c"
#include "LM35.c"
#include "WiFi.c"

int main(){
    int valCNT = 0;
    while(1){
        valCNT++;
//        float thAX, thAY, thAZ, thGX, thGY, thGZ, thTemp, thVib;
//        char gps = getGPS();
//        float temp = ReadTemperature();
//        float imu = readIMU();
//        float vib = 0;
//        int accident = 0;

//        if((imu[0]>thAX) ||
//        (imu[1]>thAY) ||
//        (imu[2]>thAZ) ||
//        (imu[3]>thGX) ||
//        (imu[4]>thGY) ||
//        (imu[5]>thGZ) ||
//        (temp>thTemp) ||
//        (vib>thVib)){
//            accident = 1;
//        }

//        thAX += imu[0]/valCNT;
//       thAY += imu[1]/valCNT;
//        thAY += imu[2]/valCNT;
//        thGX += imu[3]/valCNT;
//        thGY += imu[4]/valCNT;
//        thGZ += imu[5]/valCNT;
//        thTemp += temp/valCNT;
//        thVib += vib/valCNT;




    }
    return 1;

}