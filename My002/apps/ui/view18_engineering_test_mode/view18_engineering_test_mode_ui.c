#include "../../apps.h"



static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view18_engineering_test_mode_cc.h"
void view18_engineering_test_mode_init(void)
{
	grf_view_create(GRF_VIEW18_ENGINEERING_TEST_MODE_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view18_engineering_test_mode_entry(void)
{
	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	task_create18();
	grf_view_set_dis_view(GRF_VIEW03_VOICE_ICON_ID);
	grf_view_set_dis_view(GRF_VIEW04_BATTERY_WATER_ID);
}

void view18_engineering_test_mode_exit(void)
{
	grf_view_hide_layer(GRF_LAYER_STATE);
	grf_view_hide_layer(GRF_LAYER_TOP);
	view03_voice_icon_exit();
	view04_battery_water_exit();
	task_del18();
}
