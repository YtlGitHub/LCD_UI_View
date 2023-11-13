#include "../../apps.h"


//.c文件里面自定义函数
void task_create16();
void task_del16();


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void qrcode0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view16_help4_cc.h"
void view16_help4_init(void)
{
	grf_view_create(GRF_VIEW16_HELP4_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view16_help4_entry(void)
{
	//语音播报"请扫描二维码关注公众号,或拨打电话联系售后。"
	switch_language_pack("16_help");
	task_create16();
}

void view16_help4_exit(void)
{
	task_del16();
}
