#include "../../apps.h"


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void qrcode0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view12_help_cc.h"
void view12_help_init(void)
{
	grf_view_create(GRF_VIEW12_HELP_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view12_help_entry(void)
{
	task_create12();
	//发送串口数据
	grf_reg_com_send(0x04, 0xA0, 0x00, 0x00, 0x00);
	//语音播报测试:"欢迎来到帮助界面"
	switch_language_pack("12_help");
}

void view12_help_exit(void)
{
	task_del12();
}
