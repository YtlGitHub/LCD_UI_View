#include "../../apps.h"


static void label3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image1_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void label0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void container0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image4_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image3_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}
#include "../../../libs/appscc/view01_cc.h"
void view01_init(void)
{
	grf_view_create(GRF_VIEW01_ID, view_ctrls_fun_t,sizeof(view_ctrls_fun_t) / sizeof(grf_ctrl_fun_t));
}

void view01_entry(void)
{
	grf_printf("view01_entry\n");
	//system("/usr/bin/aplay /mnt/app/grf_app/res/sound/1.wav &");
	task_create01();
}


void view01_exit(void)
{
	grf_printf("view01_exit\n");
	task_del01();
}
