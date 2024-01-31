#include "../../apps.h"


//.c文件里面自定义函数
void task_create06();
void task_del06();


static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view06_sterilization_cc.h"
void view06_sterilization_init(void)
{
	grf_view_create(GRF_VIEW06_STERILIZATION_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view06_sterilization_entry(void)
{
	task_create06();
	grf_view_set_dis_view(GRF_VIEW03_VOICE_ICON_ID);
	grf_view_set_dis_view(GRF_VIEW04_BATTERY_WATER_ID);
	//发送串口数据
	grf_reg_com_send(0x05, 0xA0, 0x02, 0x02, 0x00);
	//语音播报:除菌也已制备完成,请开始清洁
	switch_language_pack("05_02_sterilization_fluid_preparation_100%");
}

void view06_sterilization_exit(void)
{
	task_del06();
	grf_view_hide_layer(GRF_LAYER_STATE);
	grf_view_hide_layer(GRF_LAYER_TOP);
	view03_voice_icon_exit();
	view04_battery_water_exit();
}
