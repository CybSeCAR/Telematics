#include "Particle.h"
#include <ArduinoJson.h>
#include <CarT.h>
//#include <SparkJson.h>


SYSTEM_THREAD(ENABLED);     //setup threading
SYSTEM_MODE(MANUAL);        //system mode to disable auto cell connect        
STARTUP(startup_function());//setup stratup function and block everything untill finished

//holds encryption key
unsigned char key[32];
#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long lastSync = millis();
int counter = 0;

    int size;

<<<<<<< HEAD
    Serial.begin(9600);
    while(!Serial);
    delay(5000);
    sd_storage->begin();
    dof->getTemp();

    RGB.control(true);
    RGB.color(0,255,0);

    stn->begin();
    stn->monitorCAN();
    stn->SetProtocol();
    stn->getRPM();
    while(!Serial5.available()){
        Serial.println("no can messages");
    }

    os_mutex_lock(can_recv_mutex);
    stn->receive(can_recv_buffer,size);

    os_mutex_unlock(can_recv_buffer);
   

    for(int i =0; i<=21;i++)
    {
    Serial.print(((char) can_recv_buffer[i]));
    }
    Serial.println();
    
    //sd_storage->write(dof->TEMP);
    //sd_storage->write('\n');

    

    RGB.color(0,100,100);
    
    /*
=======
//create json buffer for parsing data 
DynamicJsonBuffer jsonBuffer;
JsonObject* root;
JsonArray* CAN_data;
JsonArray* GPS_data;
JsonArray* DOF_data;

void setup() {
    
    Serial.begin(9600); //start Serial output
    delay(5000);        //wait for user, needs to be updated

    //initialize the json parser
    static JsonObject& root_temp = jsonBuffer.createObject();
    root=&root_temp;

    static JsonArray& CAN_data_temp = root->createNestedArray("CAN_data");
    CAN_data=&CAN_data_temp;

    static JsonArray& GPS_data_temp = root->createNestedArray("GPS_data");
    GPS_data=&GPS_data_temp;

    static JsonArray& DOF_data_temp = root->createNestedArray("DOF_data");
    DOF_data=&DOF_data_temp;

    WITH_LOCK(Serial)
    {
>>>>>>> 85fa079e0dd606f8ae7147f9815cf11c52fdd476

        secretStuff->generateKey();

        unsigned char input[128];
        unsigned char output[128];
        unsigned char in[128];
        unsigned char put[128];

        memset(input, 0, 128);
        memset(output, 0, 128);
        memset(in, 0, 128);
        memset(put, 0, 128);

        memcpy(input,"hello",strlen("hello"));

<<<<<<< HEAD
    */

=======
        Serial.print("Encrypted Data: ");
        secretStuff->encryptData(input,output);
        for(int i = 0; i < 16; i++){
            Serial.printf("%d",output[i]);
        }
>>>>>>> 85fa079e0dd606f8ae7147f9815cf11c52fdd476

        Serial.println();

        Serial.print("Decrypted Data: ");
        secretStuff->decryptData(output,put);
        for(int i = 0; i < 16; i++){
            Serial.printf("%c",put[i]);
        }
        Serial.println();
        

    }
    
}   

void loop() {

    os_mutex_lock(dof_recv_mutex); 
    os_mutex_lock(gps_recv_mutex); 
    os_mutex_lock(can_recv_mutex);   
    //meesage type
    byte message_id;
    message_id = message_id || (new_can_flag << 3);
    message_id = message_id || (new_can_flag << 2);
    message_id = message_id || (new_can_flag << 1);

    (*root)["messageid"] = message_id;

    
    if(new_dof_flag){
        for(int i =0; i < dof_frames_in_buffer; i++)
        {
            DOF_data->createNestedArray(); 
            (*DOF_data)[i]=dof_recv_buffer[i];    
        }
        new_dof_flag = false; 
    }

    if(new_can_flag){
        for(int i =0; i < can_frames_in_buffer; i++)
        {
            CAN_data->createNestedArray();  
            (*CAN_data)[i]=can_recv_buffer[i];      
        }
        new_can_flag = false; 
    }

    if(new_gps_flag){
        
        for(int i =0; i < gps_frames_in_buffer; i++)
        {
            GPS_data->createNestedArray(); 
            (*GPS_data)[i]=gps_recv_buffer[i];       
        }
        new_gps_flag = false;  
    }

    os_mutex_lock(mqtt_mutex);
    int buflen= root->measurePrettyLength();
    mqtt_send_buffer = (char*)realloc(mqtt_send_buffer,buflen+1);   //adjsut mqtt buffer size
    root->prettyPrintTo(mqtt_send_buffer,buflen+1);                 //create send char array
    awsiot->publish("cart/2",mqtt_send_buffer);                     //aws send new buffer
    os_mutex_unlock(mqtt_mutex);

    //clear arrays
    for(int i =0; i < RECORDS; i++)
    {
        DOF_data->remove(i); 
    }
    for(int i =0; i < RECORDS; i++)
    {
        CAN_data->remove(i);        
    }       
    for(int i =0; i < RECORDS; i++)
    {
        GPS_data->remove(i);     
    }
    os_mutex_unlock(dof_recv_mutex);
    os_mutex_unlock(gps_recv_mutex);
    os_mutex_unlock(can_recv_mutex);
}


