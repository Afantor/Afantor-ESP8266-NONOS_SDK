/*********************************************************************************************
�������� ��LED��˸������WIFIģ���GPIO�ڣ�
��д�ˣ� ���� ��
��дʱ�䣺����
Ӳ��֧�֣�����
�ӿ�˵��������
�޸���־������
����NO.1-								
/*********************************************************************************************
˵����

/*********************************************************************************************/
#include "driver/uart.h"  //����0��Ҫ��ͷ�ļ�
#include "osapi.h"  //����1��Ҫ��ͷ�ļ�
#include "gpio.h"  //�˿ڿ�����Ҫ��ͷ�ļ�
#include "c_types.h"
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"
#include "gpio.h"



/** ��ʱ���ṹ�� */
static os_timer_t os_timer;


/** LED�������� */
void Led_Cmd(bool status ){
    if (status == true ) {
    	GPIO_OUTPUT_SET(GPIO_ID_PIN(12), 0);
    }
    else {
    	GPIO_OUTPUT_SET(GPIO_ID_PIN(12), 1);
    }
}



void Led_Task_Run(void){

	static bool status = false;
    if ( status == true ) {
	    status = false;
	}
    else  {
	    status = true;
	}

    os_printf("ִ�в��� ,%d",status);
    os_printf("\r\n\r\n");
	Led_Cmd( status );
}

void  user_init(void)//��ʼ��
{

   /** ���ô���0�ʹ���1�Ĳ�����*/
   uart_init(115200, 115200);


   PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
   Led_Cmd(false);


   /** �رոö�ʱ�� */
   os_timer_disarm( &os_timer );
   /** ���øö�ʱ���ص����� */
   os_timer_setfn( &os_timer, (ETSTimerFunc *) ( Led_Task_Run ), NULL );
   /** �����ö�ʱ�� */
   os_timer_arm( &os_timer, 500, true );
}

void user_rf_pre_init()
{

}




