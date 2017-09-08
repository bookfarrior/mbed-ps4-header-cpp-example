#include "PS3.h"

PS3::PS3(I2C *i, char addr)
{
    i2c = i;
    ADDR = addr;

    for(int i=0; i<21; i++) {
        DATA_CONTROLLER[i] = 0;
        DATA_CONTROLLER_OLD[i] = 0;
    }
}

bool PS3::UpDate()
{
    //Make backup
    memcpy( DATA_CONTROLLER_OLD, DATA_CONTROLLER, sizeof(DATA_CONTROLLER) );

    //Get data by I2C
    if(i2c->read((ADDR | 1), data, 8) == 0) {

        //UpDate
        DATA_CONTROLLER[CONNECTION] = (data[1] >> 1) & 0x01;
        DATA_CONTROLLER[UP] = (data[0] >> 7) & 0x01;
        DATA_CONTROLLER[RIGHT] = (data[0] >> 6) & 0x01;
        DATA_CONTROLLER[DOWN] = (data[0] >> 5) & 0x01;
        DATA_CONTROLLER[LEFT] = (data[0] >> 4) & 0x01;
        DATA_CONTROLLER[TRIANGLE] = (data[0] >> 3) & 0x01;
        DATA_CONTROLLER[CIRCLE] = (data[0] >> 2) & 0x01;
        DATA_CONTROLLER[CROSS] = (data[0] >> 1) & 0x01;
        DATA_CONTROLLER[SQUARE] = (data[0] >> 0) & 0x01;
        DATA_CONTROLLER[L1] = (data[1] >> 7) & 0x01;
        DATA_CONTROLLER[R1] = (data[1] >> 6) & 0x01;
        DATA_CONTROLLER[SELECT] = (data[1] >> 5) & 0x01;
        DATA_CONTROLLER[START] = (data[1] >> 4) & 0x01;
        DATA_CONTROLLER[L3] = (data[1] >> 3) & 0x01;
        DATA_CONTROLLER[R3] = (data[1] >> 2) & 0x01;
        DATA_CONTROLLER[LeftHatX] = data[2];
        DATA_CONTROLLER[LeftHatY] = data[3];
        DATA_CONTROLLER[RightHatX] = data[4];
        DATA_CONTROLLER[RightHatY] = data[5];
        DATA_CONTROLLER[L2] = data[6];
        DATA_CONTROLLER[R2] = data[7];
    } else {
        for(int i = 0; i < 21; i++){
            DATA_CONTROLLER[i] = i >= 15 && i <= 18 ? 127 : 0;
        }
    }
    return DATA_CONTROLLER[CONNECTION];
}

int PS3::getPress( CONTROLLER buttom )
{
    if(buttom < 21) {
        return DATA_CONTROLLER[buttom];
    } else {
        return 0;
    }
}

int PS3::getClick( CONTROLLER button, bool mode )
{
    //mode:0 -> Rising
    //mode:1 -> Falling

    if(button <= 13) {
        return mode*(DATA_CONTROLLER[button]*!DATA_CONTROLLER_OLD[button])
               + !mode*(!DATA_CONTROLLER[button]*DATA_CONTROLLER_OLD[button]);

    } else if( (19<=button) && (button<=20) ) {
        return mode*((DATA_CONTROLLER[button]>127)*!(DATA_CONTROLLER_OLD[button]>127))
               + !mode*(!(DATA_CONTROLLER[button]>127)*(DATA_CONTROLLER_OLD[button]>127));

    } else {
        return 0;
    }
}
