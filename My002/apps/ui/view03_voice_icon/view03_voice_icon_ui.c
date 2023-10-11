#include "../../apps.h"


static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view03_voice_icon_cc.h"
void view03_voice_icon_init(void)
{
	grf_view_create(GRF_VIEW03_VOICE_ICON_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view03_voice_icon_entry(void)
{
	task_create03();
}

void view03_voice_icon_exit(void)
{
	task_del03();
}
