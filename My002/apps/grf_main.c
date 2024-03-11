#include "apps.h"
#include "../libs/appscc/grf_prj_cc.h"

void grf_main(void)
{
	grf_hw_init();
	grf_prj_create(grf_views_fun, sizeof(grf_views_fun) / sizeof(grf_view_fun_t));
}
