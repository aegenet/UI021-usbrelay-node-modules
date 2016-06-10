//------------------------------------------------------------------------------//
//          �����������Ƽ����޹�˾                                              //
//       USB�̵���Ӧ�ñ�̽ӿ�(API)˵��                                         //
//                                                                              //
//    ��API������                                                               //
//    1. 1/2/4·USB�̵���                                                       //
//    2. Linux2.6.16�����ϲ���ϵͳ                                              //
//                                                                              //
//    ��ϸ���½�����������Ƽ����޹�˾�ٷ���վhttp://freeeasy-life.com          //
//------------------------------------------------------------------------------//

#ifndef  _USBRELAY_H
#define  _USBRELAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "usb2io.h"

/***********�豸��������;���º����е�USBRELAY_hdl��ָUSBRELAY_Open���صľ��*******/
//�򿪶˿ڻ�ȡ���;  //Nbr�Ƕ˿ںţ���1��ʼ������Ϊ2/3/4...�����126
libusb_device_handle *USBRELAY_Open(int Nbr);
//�رն˿ڣ��ڳ����˳�ǰ�ٹرն˿�; ���� 0: �ɹ���!0: ʧ��
int USBRELAY_Close(libusb_device_handle *USBRELAY_hdl);

/***********�̵�����������;���º����е�USBRELAY_hdl��ָUSBRELAY_Open���صľ��*******/
//���ü̵���
//RelayNbr:  �̵���λ�ã���1��ʼ
//OpCode: 0�ǹرգ�1�Ǵ�
//���أ� -1=err; -2=����û�гɹ�; 0=OK
int USBRELAY_SetRelay(libusb_device_handle *USBRELAY_hdl, int RelayNbr, int OpCode);
//��ȡ�̵���״̬
//RelayStatus: 0�رգ� 1��
//���أ� -1=err;  0=OK
int USBRELAY_GetRelay(libusb_device_handle *USBRELAY_hdl, int RelayNbr, int *RelayStatus);

#ifdef __cplusplus
}
#endif

#endif


