#include "../../apps.h"


static void arc0_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

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

static void label2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
	
}

static void image2_event(grf_ctrl_t *ctrl, grf_event_e event)
{
//	switch (event) {
//		case GRF_EVENT_CLICKED:{
//
//		}break;
//	}
}

#include "../../../libs/appscc/view04_battery_water_cc.h"
void view04_battery_water_init(void)
{
	grf_view_create(GRF_VIEW04_BATTERY_WATER_ID,view_ctrls_fun_t,sizeof(view_ctrls_fun_t)/sizeof(grf_ctrl_fun_t));
}

void view04_battery_water_entry(void)
{
	task_create04();
}

void view04_battery_water_exit(void)
{
	task_del04();
}
