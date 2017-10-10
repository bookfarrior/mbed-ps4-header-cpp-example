#pragma once
#include "mbed.h"

enum CONTROLLER {
    UP, RIGHT, DOWN, LEFT,
    TRIANGLE, CIRCLE, CROSS, SQUARE,
    L1, R1,
    SHARE, OPTIONS,
    L3, R3,
    CONNECTION,
    LeftHatX, LeftHatY,
    RightHatX, RightHatY,
    L2, R2
};

class PS4
{
private:
    char data[8];
    int DATA_CONTROLLER_OLD[21];
    I2C *i2c;
    char ADDR;
public:
    int DATA_CONTROLLER[21];
    PS4(I2C *i, char addr);
    bool UpDate();
    int getPress( CONTROLLER buttom );
    int getClick( CONTROLLER button, bool mode );
};