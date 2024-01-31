#include "../../apps.h"



static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image_button0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label6_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label5_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view17_system_setting_cc.h"
void view17_system_setting_init(void)
{
	grf_view_create(GRF_VIEW17_SYSTEM_SETTING_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view17_system_setting_entry(void)
{
	//key_sound_tr660r_wavplay("dongPart002");  //按键音效
	key_sound_tr660r_wavplay("du");  //按键音效
	task_create17();
}

void view17_system_setting_exit(void)
{
	task_del17();
}
