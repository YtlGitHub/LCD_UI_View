#include "../../apps.h"


//.c文件里面自定义函数
void task_create02();
void task_del02();



static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view02_cleaning_cc.h"


void view02_cleaning_init(void)
{
	grf_view_create(GRF_VIEW02_CLEANING_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view02_cleaning_entry(void)
{
	task_create02();
	grf_view_set_dis_view(GRF_VIEW03_VOICE_ICON_ID);
	grf_view_set_dis_view(GRF_VIEW04_BATTERY_WATER_ID);

	//发送串口数据
	grf_reg_com_send(0x04, 0xA0, 0x01, 0x00, 0x00);
}


void view02_cleaning_exit(void)
{
	task_del02();
	grf_view_hide_layer(GRF_LAYER_STATE);
	grf_view_hide_layer(GRF_LAYER_TOP);
	view03_voice_icon_exit();
	view04_battery_water_exit();
}
