#include "../../apps.h"


//.c文件里面自定义函数
void task_create07();
void task_del07();



static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view07_water_suction_cc.h"
void view07_water_suction_init(void)
{
	grf_view_create(GRF_VIEW07_WATER_SUCTION_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view07_water_suction_entry(void)
{
	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	task_create07();
	grf_view_set_dis_view(GRF_VIEW03_VOICE_ICON_ID);
	grf_view_set_dis_view(GRF_VIEW04_BATTERY_WATER_ID);
	//发送串口数据
	grf_reg_com_send(0x04, 0xA0, 0x03, 0x00, 0x00);
	//语音播报:智能吸水
	switch_language_pack("07_smart_water");
}

void view07_water_suction_exit(void)
{
	task_del07();
	grf_view_hide_layer(GRF_LAYER_STATE);
	grf_view_hide_layer(GRF_LAYER_TOP);
	view03_voice_icon_exit();
	view04_battery_water_exit();
}
