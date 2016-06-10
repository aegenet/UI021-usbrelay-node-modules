#include <unistd.h>
#include "usbrelay.h"

#define Level2OpenRelay  0
/*******************�򿪹رպ���****************************/
//�򿪶˿ڻ�ȡ���;
//Nbr�Ǵ򿪵Ķ˿ںţ���1��ʼ������Ϊ2/3/4...�����126
libusb_device_handle *USBRELAY_Open(int Nbr)
{
    return(USB2IO_Open(Nbr));
}

int USBRELAY_Close(libusb_device_handle *USBRELAY_hdl)
{
    return(USB2IO_Close(USBRELAY_hdl));
}

//RelayNbr:  �̵���λ�ã���1��ʼ
//OpCode: 0�ǹرգ�1�Ǵ�
//���أ� -1=err; -2=����û�гɹ�; 0=OK
const int IO_RELAY_MAP[] = {1, 2, 4, 5};
const int LEDIO_RELAY_MAP[] = {7, 8, 11, 12};
int USBRELAY_SetRelay(libusb_device_handle *USBRELAY_hdl, int RelayNbr, int OpCode)
{
    int IoNbr;
	int Level2Set;
	int IoCfg;
    int Delay = 20; //delay 1s
	int RdVal;

    if ((RelayNbr < 0) || (RelayNbr > 4)) {
        return -1;
    }
    IoNbr = IO_RELAY_MAP[RelayNbr - 1];
    //���ܵ�ǰPIN��ƽ��ֱ�����������ƽ
    if (OpCode == 0) {
        Level2Set = 1 - Level2OpenRelay;  //�ر�
    }
    else if (OpCode == 1) {
        Level2Set = Level2OpenRelay;      //��
    }
    else {
        return -1;
    }
    if (USB2IO_SetIoOut(USBRELAY_hdl, IoNbr, Level2Set) != 0) {
        return -1;
    }
    //�жϵ�ǰIO�Ƿ���PP OUT��������ǣ�������ΪPP OUT
    if (USB2IO_RdIoCfg(USBRELAY_hdl, IoNbr, &IoCfg) != 0) {
        return -1;
    }
    if (IoCfg != 3) {
        if (USB2IO_SetIoCfg(USBRELAY_hdl, IoNbr, 3) != 0) {
            return -1;
        }
    }
    //��ȡ��ǰPIN�Ƿ��Ѿ�����Ҫ�ĵ�ƽ
    Delay = 20; //delay 1s
    while(Delay) {
        usleep(50000); //50ms
        Delay--;
        if (USB2IO_RdPin(USBRELAY_hdl, IoNbr, &RdVal) != 0) {
            return -1;
        }
        if (RdVal == Level2Set) {
            //����led
            USB2IO_SetIoOut(USBRELAY_hdl, LEDIO_RELAY_MAP[RelayNbr - 1], OpCode);
            return 0;
        }
        else {
            USB2IO_SetIoOut(USBRELAY_hdl, IoNbr, Level2Set);
        }
    }
    return -2;
}

//��ȡ�̵���״̬
//RelayStatus: 0�رգ� 1��
int USBRELAY_GetRelay(libusb_device_handle *USBRELAY_hdl, int RelayNbr, int *RelayStatus)
{
    int RdVal;
    int IoNbr;
    
    if ((RelayNbr < 0) || (RelayNbr > 4)) {
        return -1;
    }
    IoNbr = IO_RELAY_MAP[RelayNbr - 1];
    if (USB2IO_RdPin(USBRELAY_hdl, IoNbr, &RdVal) != 0) {
        return -1;
    }
    if (RdVal == Level2OpenRelay) {
        *RelayStatus = 1;
    }
    else if (RdVal == (1 - Level2OpenRelay)) {
        *RelayStatus = 0;
    }
    else {
        return -1;
    }
    return 0;
}