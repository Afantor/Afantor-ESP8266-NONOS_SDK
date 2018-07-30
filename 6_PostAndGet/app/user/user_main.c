/*
 * user_main.c
 *
 *  Created on: 2015��7��13��
 *      Author: Administrator
 */
#include "driver/uart.h"
#include "user_main.h"

os_timer_t checkTimer_wifistate;

void Check_WifiState(void) {
	uint8 getState;
	getState = wifi_station_get_connect_status();

	//���״̬��ȷ��֤���Ѿ��ɹ����ӵ�·����
	if (getState == STATION_GOT_IP) {
		os_printf("WIFI���ӳɹ���");
		os_timer_disarm(&checkTimer_wifistate);
		os_timer_disarm(&connect_timer);

		uint8 status = wifi_station_get_connect_status();
		if (status == STATION_GOT_IP) {
			uart0_sendStr("WIFI���ӳɹ���");
			startHttpQuestByGET(
					"https://api.seniverse.com/v3/weather/daily.json?key=rrpd2zmqkpwlsckt&location=guangzhou&language=en&unit=c&start=0&days=3");
			return;
		}
	}

}
void user_init() {

	uart_init(57600, 57600);
	wifi_set_opmode(0x01); //����ΪSTATIONģʽ
	struct station_config stationConf;
	os_strcpy(stationConf.ssid, "TP-LINK_AliYun");	  //�ĳ����Լ���   ·�������û���
	os_strcpy(stationConf.password, "aliyun_123456"); //�ĳ����Լ���   ·����������
	wifi_station_set_config(&stationConf); //����WiFi station�ӿ����ã������浽 flash
	wifi_station_connect(); //����·����

	os_timer_disarm(&checkTimer_wifistate); //ȡ����ʱ����ʱ
	os_timer_setfn(&checkTimer_wifistate, (os_timer_func_t *) Check_WifiState,
	NULL); //���ö�ʱ���ص�����
	os_timer_arm(&checkTimer_wifistate, 500, true); //������ʱ������λ������
	os_printf("57600 end... \n\r");
}
void user_rf_pre_init() {
}

