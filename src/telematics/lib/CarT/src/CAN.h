#ifndef CAN_H
#define CAN_H

#include "Particle.h"
class CAN
{
    public:
        CAN();
        void begin();
        void SetHS();
        void GetRPM();
        void GetSpeed();
        void monitorCAN();
        void ClearFlowControl();
        void SendFrame(int header, int message);
        int receive(int* buffer, int& size);
        int newData();
        int receive(int* buffer,int number_bytes_to_write);
    private:
};
#endif
