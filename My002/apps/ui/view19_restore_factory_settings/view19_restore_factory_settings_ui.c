#include "../../apps.h"



static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view19_restore_factory_settings_cc.h"
void view19_restore_factory_settings_init(void)
{
	grf_view_create(GRF_VIEW19_RESTORE_FACTORY_SETTINGS_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view19_restore_factory_settings_entry(void)
{
	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	//发送串口数据
	grf_reg_com_send(0x04, 0xC0, 0x04, 0, 0);
	//语音播报"已恢复出场设置。"
	switch_language_pack("19_restore_factory_settings");
	ytl0_roller_brush_lighting = GRF_TRUE;
	ytl1_cleaning_method = GRF_FALSE;
	ytl2_voice_image_val = 2;
	ytl3_switch_language = 0;
	save_system_settings_var();
//	task_create19();
}

void view19_restore_factory_settings_exit(void)
{
//	task_del19();
}
