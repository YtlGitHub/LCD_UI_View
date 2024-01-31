#include "../../apps.h"


//.c文件里面自定义函数
void task_create09();
void task_del09();


static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

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

static void label1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label6_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label7_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label8_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label9_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image6_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label10_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view09_self_cleaning_mode_cc.h"
void view09_self_cleaning_mode_init(void)
{
	grf_view_create(GRF_VIEW09_SELF_CLEANING_MODE_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view09_self_cleaning_mode_entry(void)
{
	ytl_view_get_cur_id = grf_view_get_cur_id(GRF_LAYER_UI);
	grf_view_set_dis_view(GRF_VIEW03_VOICE_ICON_ID);
	task_create09();
	//发送串口数据,写在.c文件里
	//grf_reg_com_send(0x04, 0xB0, 0x00, 0x00, 0x00);
}

void view09_self_cleaning_mode_exit(void)
{
	task_del09();
}

