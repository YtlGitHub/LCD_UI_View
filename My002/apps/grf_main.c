#include "apps.h"
#include "../libs/appscc/grf_prj_cc.h"

void grf_main(void)
{
	//grf_printf("giraffe sdk version %s \n",grf_ver_get_str());
	grf_hw_init();
//	grf_printf("sizeof(grf_views_fun) == %d\n",sizeof(grf_views_fun));
//	grf_printf("sizeof(grf_view_fun_t) == %d\n",sizeof(grf_view_fun_t));
	grf_prj_create(grf_views_fun, sizeof(grf_views_fun) / sizeof(grf_view_fun_t));
}
