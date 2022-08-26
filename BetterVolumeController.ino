#include <HID.h>                            //include stuff
#include <HID-Project.h>                    
#include <HID-Settings.h>
#include <math.h>                           
#define REVERSED false                      //if your controller is reversed change it to true


int Aval = 0;
int val = 0;
int volume = 0;
int potbuffer = 4;

void setup() {
  Consumer.begin();                         //initialize computer connection
  delay(1000);                              //wait for computer to connect
  for(int a = 0; a < 52; a++) {
    Consumer.write(MEDIA_VOLUME_DOWN);      //set the volume to 0
  }
}

void loop() {
  if (analogRead(1) >= Aval+potbuffer || analogRead(1) <= Aval-potbuffer) { Aval = analogRead(1); }                                    //read potentiometer value if it has changed more then the buffer amount since last read
  val = map(Aval, 0, 1023, 0, 55);                                                                                                     //map it to 55 steps
  val *= 2;                                                                                                                            //multiply num by 2, this is to get it to 110 steps in even nums, and 110 steps gives a buffer at 100 volume
  if(REVERSED) {                                                                                                                       //reverse val
    val = 110 - val;
  }

  while (volume != val) {                                                                                                              //if current volume doesnt match val
    if (volume < val) { Consumer.write(MEDIA_VOLUME_UP); volume += 2; }                                                                //if the volume is less then val, bring volume up
    if (volume == val) { break; }                                                                                                      //break if correct
    if (volume > val) { Consumer.write(MEDIA_VOLUME_DOWN); volume -= 2; }                                                              //if the volume is more then val, bring volume down
  }
}
