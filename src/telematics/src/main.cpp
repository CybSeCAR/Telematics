#include "Particle.h"
#include <CarT.h>


SYSTEM_THREAD(ENABLED);     //setup threading
SYSTEM_MODE(MANUAL);        //system mode to disable auto cell connect        
STARTUP(startup_function());//setup stratup function and block everything untill finished

//holds encryption key
unsigned char key[32];

#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long lastSync = millis();
int counter = 0;
void setup() {


    Serial.begin(9600);
    while(!Serial);

    delay(5000);
    sd_storage->begin();
    dof->getTemp();
    RGB.control(true);
    RGB.color(0,255,0);
    
    for(int i =0; i<=21;i++)
    {
    sd_storage->write((char) can_recv_buffer[i]);
    }
    sd_storage->write('\n');
    
    sd_storage->write(dof->TEMP);
    sd_storage->write('\n');
    
    RGB.color(0,100,100);
    
    



    //rts resync (not used)
    /*
    resync time everyday
    if (millis() - lastSync > ONE_DAY_MILLIS) {
        Particle.syncTime();
        lastSync = millis();
    }

    secretStuff->encryptData(input,output);
    for(int i = 0; i < 11; i++){
        Serial.printf("%c",output[i]);
    }
    secretStuff->decryptData(output,input);
    Serial.println();
    for(int i = 0; i < 11; i++){
        Serial.printf("%c",input[i]);
    }

    /*
    //test dof
    dof.getTemp();          //aquire dof temp
    float temp = dof.TEMP;  //set to temp


    //test sd storage
    if (sd_storage.write<float>(temp)){
        Serial.println("bottom of code");
    } else {
        Serial.println("did not write to sd!");
    }
    */

    


}   

void loop() {

    //curently does nothing
    delay(200);
}

