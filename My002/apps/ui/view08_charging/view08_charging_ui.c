#include "../../apps.h"


//.c文件里面自定义函数
void background_red_yellow_green_task_cb();
void task_create08();
void task_del08();


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view08_charging_cc.h"
void view08_charging_init(void)
{
	grf_view_create(GRF_VIEW08_CHARGING_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view08_charging_entry(void)
{
	grf_reg_com_send(0x05, 0xB0, 0x01, 0x00, 0x00);
	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	//grf_view_all_set_rotate(2);  //旋转180°
	task_create08();

	//语音播报:开始充电,清洁度检测中,请清理无水箱,避免异味
	switch_language_pack("08_00_start_charging");
}

void view08_charging_exit(void)
{
	task_del08();
}
