#include "../../apps.h"


//.c文件里面自定义函数
void task_create10_01();
void task_del10_01();


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view10_01_please_clean_the_dirty_water_tank_cc.h"
void view10_01_please_clean_the_dirty_water_tank_init(void)
{
	grf_view_create(GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view10_01_please_clean_the_dirty_water_tank_entry(void)
{
	//判断是快速还是超强
	if (ytl_mode_select_uart == 1)
	{
		grf_reg_com_send(0x06, 0xA0, 0x04, 0x01, 0x08);
	}
	else if (ytl_mode_select_uart == 2) {
		grf_reg_com_send(0x06, 0xA0, 0x04, 0x02, 0x08);
	}

	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	grf_view_set_dis_view(GRF_VIEW03_VOICE_ICON_ID);
	task_create10_01();
	//语音播报:"请清理污水箱,避免异味"
	if (uart_only_sent_once_self_cleaning_var == 9) {
		switch_language_pack("10_01_09_Please_clean_the_sewage_tank_to_avoid_odors");  //"请清理污水箱,避免异味"
	}
	else {
		switch_language_pack("10_01_09_self_cleaning_close");  //"自清洁已关闭,请清理污水箱,避免异味"
	}
}

void view10_01_please_clean_the_dirty_water_tank_exit(void)
{
	task_del10_01();
	grf_view_hide_layer(GRF_LAYER_TOP);
}
