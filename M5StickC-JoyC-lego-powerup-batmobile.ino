/*
 * @Author: Sorzn
 * @Date: 2019-11-22 14:48:10
 * @LastEditTime: 2019-11-22 15:45:27
 * @Description: M5Stack project
 * @FilePath: /M5StickC/examples/Hat/JoyC/JoyC.ino
 */

#include <PoweredUpHub.h>
#include "M5StickC.h"
#include "JoyC.h"

JoyC joyc;
TFT_eSprite img = TFT_eSprite(&M5.Lcd);

int y_left;
int y_right;
char text_buff[100];

PoweredUpHub myHub;
PoweredUpHub::Port _portA = PoweredUpHub::Port::A;
PoweredUpHub::Port _portB = PoweredUpHub::Port::B;
boolean powerup_ok    = false;

uint8_t show_flag = 0;

void setup()
{
    M5.begin();
    myHub.init(); 
    Wire.begin(0, 26, 400000);
    img.createSprite(80, 160);
}

void loop()
{
  powerup_ok = myHub.isConnected();
  if (!powerup_ok)
  {
    if (myHub.isConnecting()) {
      myHub.connectHub();  
    }
  }
  else
  {
    M5.update();

    y_right =(joyc.GetY(1)/10+(joyc.GetY(1)/10)%2-10)*10;
    y_left  =(joyc.GetY(0)/10+(joyc.GetY(0)/10)%2-10)*10;

    myHub.setMotorSpeed(_portA,  y_right);
    myHub.setMotorSpeed(_portB, -y_left);     
    
    img.fillSprite(TFT_BLACK);

    img.drawCentreString("y left", 40, 62, 1);
    sprintf(text_buff, "%d", y_left);
    img.drawCentreString(text_buff, 40, 76, 1);

    img.drawCentreString("y right", 40, 90, 1);
    sprintf(text_buff, "%d", y_right);
    img.drawCentreString(text_buff, 40, 104, 1);
    
    img.pushSprite(0, 0);
    
    if(M5.BtnA.wasPressed())
    {
        joyc.SetLedColor(random(0xFFFFFF));    
        show_flag = 1 - show_flag;
    }
  }
    delay(10);
}
