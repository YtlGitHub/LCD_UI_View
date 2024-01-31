#include "../../apps.h"


//创建任务名
grf_task_t *logo_task = NULL;  //工程测试模式任务


//创建控件名
static grf_ctrl_t *label_name_ID1 = NULL;  //欢迎文本显示控件名

//自定义变量
static u8 i = 0;  //等待叮咚完，播报开机语音


//自定义数组


//自定义调用函数


//logo任务
void logo_task_cb()
{
	if (i == 1) {
		power_on();
		grf_ctrl_set_hidden(label_name_ID1, GRF_FALSE);
	}
	else if (i == 2) {
		key_sound_tr660r_wavplay("dingdong");  //开机音效
	}
	else if (i == 7) {
		switch_language_pack("00_01_power_on");  //开机语音播报
	}
	else if (i == 11) {
		//滚刷照明
		if (ytl0_roller_brush_lighting)
		{
			//发送串口数据
			grf_reg_com_send(0x05, 0xC0, 0x01, 0x01, 0);
		}
		else
		{
			//发送串口数据
			grf_reg_com_send(0x05, 0xC0, 0x01, 0x00, 0);
		}
		if (ytl_battery_quantity_val == 101) {
			grf_reg_com_send(0x04, 0x90, 0x02, 0, 0);  //获取电量
		}
	}
	if (i<=11) {
		i++;
	}
}


void task_create20(void)
{
	//获取控件
	label_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW20_LOGO_ID, VIEW20_LOGO_LABEL0_ID);

	//创建任务
	logo_task = grf_task_create(logo_task_cb,100,NULL);  //创建logo任务

	//立即执行
	grf_task_ready(logo_task);
}


void task_del20(void)
{
	grf_task_del(logo_task);
}
