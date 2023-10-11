#include "../../apps.h"


//创建任务名
static grf_task_t *key_task04 = NULL;
static grf_task_t *battery_water_circle_task = NULL;
static grf_task_t *red_outer_circle_task = NULL;


//创建控件名
static grf_ctrl_t* battery2 = NULL;  //电池图标
static grf_ctrl_t* water3 = NULL;  //清水图标

static grf_ctrl_t* battery_quantity4 = NULL;  //当前电量显示0-100%
static grf_ctrl_t* water6= NULL;  //清水或溶液文字显示

static grf_ctrl_t* qingsao_arc1 = NULL;  //红色外圈脏污程度图标


//电池清水图片重复显示自定义变量
static u8 img_repeat_display = 1;
static s8 d = 0;  //arc外圈值 百分比0-100
static u8 e = 5;  //arc外圈每次运动大小
static u8 battery_quantity[1];  //电量显示
//static u8 water[1];  //清水或溶液显示


//自定义数组
static u8 *battery_icon_name[EXTERNAL_BUFFER_SIZE] = {
	"/battery_water/battery00.png",
	"/battery_water/battery01.png",
	"/battery_water/battery02.png",
	"/battery_water/battery03.png",
	"/battery_water/battery04.png",
	"/battery_water/battery05.png"
};  //电池图标文件名数组保存
static u8 *water_icon_name[EXTERNAL_BUFFER_SIZE] = {
	"/battery_water/water (0).png",
	"/battery_water/water (1).png",
	"/battery_water/water (2).png",
	"/battery_water/water (3).png",
	"/battery_water/water (4).png",
	"/battery_water/water (5).png"
};  //清水图标文件名数组保存


//电池 清水 图标重复显示
static void battery_water_task_cb()
{
	if (ytl_erected)
	{
		grf_printf("img_repeat_display == %d\n",img_repeat_display);

		if (ytl_battery_quantity_val >=0 && ytl_battery_quantity_val <= 10)
		{
			grf_img_set_src(battery2, battery_icon_name[0]);
		}
		else
		{
			grf_img_set_src(battery2, battery_icon_name[img_repeat_display]);
		}

		if (!ytl_water_shortage_val)
		{
			grf_img_set_src(water3, water_icon_name[0]);
		}
		else
		{
			grf_img_set_src(water3, water_icon_name[img_repeat_display]);
		}

		img_repeat_display++;
		if (img_repeat_display > 5)
		{
			img_repeat_display = 1;
		}
	}
	if (isCmdCompletedBuf[4]) {
		grf_label_set_align(battery_quantity4,GRF_LABEL_ALIGN_RIGHT);
		//电池图标显示
		if (ytl_battery_quantity_val >=0 && ytl_battery_quantity_val <= 10) {
			grf_img_set_src(battery2, battery_icon_name[0]);
		}
		else {
			grf_img_set_src(battery2, battery_icon_name[img_repeat_display]);
		}

		//清水图标显示
		if (ytl_water_shortage_val) {
			grf_img_set_src(water3, water_icon_name[img_repeat_display]);
		}
		else {
			grf_img_set_src(water3, water_icon_name[0]);
		}

		//电量显示
		grf_label_set_align(battery_quantity4,GRF_LABEL_ALIGN_CENTER);
		sprintf(battery_quantity, "%d" "%s", ytl_battery_quantity_val, "%");
		grf_label_set_txt(battery_quantity4,battery_quantity);

		//清水溶液文字显示
		if (ytl1_cleaning_method) {
			//sprintf(water, "%s", "#solution");
			grf_label_set_txt(water6,"#solution");
		}
		else {
			//sprintf(water, "%s", "#water");
			grf_label_set_txt(water6,"#water");
		}
		isCmdCompletedBuf[4] = GRF_FALSE;
	}

}


//
static void red_outer_circle_erected()
{
	//如果d的值超过100或者小于0的话，就把d的值改为0
	if (d > 100 || d < 0)
	{
		d = 0;
	}
	else
	{
		d += e;
		if (ytl_dirty_degree == 0)
		{
			d = 0;
		}
		else if(ytl_dirty_degree == 1)
		{
			grf_ctrl_set_hidden(qingsao_arc1, GRF_FALSE);
			if (d > 25)
			{
				d = 5;
			}
		}
		else if(ytl_dirty_degree == 2)
		{
			grf_ctrl_set_hidden(qingsao_arc1, GRF_FALSE);
			if (d > 50)
			{
				d = 30;
			}
		}
		else if(ytl_dirty_degree == 3)
		{
			grf_ctrl_set_hidden(qingsao_arc1, GRF_FALSE);
			if (d > 75)
			{
				d = 55;
			}
		}
		else if(ytl_dirty_degree == 4)
		{
			grf_ctrl_set_hidden(qingsao_arc1, GRF_FALSE);
			if (d > 100)
			{
				d = 80;
			}
		}
		else
		{
			grf_printf("脏污程度指令有误:ytl_dirty_degree == %d\n",ytl_dirty_degree);
		}
		grf_arc_set_value(qingsao_arc1,d);
	}
}

//红色外圈,跑马灯
static void red_outer_circle_task_cb()
{

	if (ytl_erected)
	{
		red_outer_circle_erected();
	}
	else if(d >= 0 && !ytl_erected)
	{
		//如果是在工程测试模式,不管是倾斜还是竖起,红色外圈跑马灯都可以跑
		if (ytl_view_get_cur_id == GRF_VIEW18_ENGINEERING_TEST_MODE_ID) {
			red_outer_circle_erected();
		}
		else {
			grf_printf("d == %d\n",d);
			//竖起机身d的值改为0
			d -= e;
			if (d <= 0) {
				ytl_dirty_degree = 0;
			}
			grf_arc_set_value(qingsao_arc1,d);
		}
	}
}


void task_create04()
{
	grf_printf("task_create4\n");

	//获取控件
	battery2 = grf_ctrl_get_form_id(GRF_VIEW04_BATTERY_WATER_ID, VIEW04_BATTERY_WATER_IMAGE0_ID);
	water3 = grf_ctrl_get_form_id(GRF_VIEW04_BATTERY_WATER_ID, VIEW04_BATTERY_WATER_IMAGE1_ID);
	qingsao_arc1 = grf_ctrl_get_form_id(GRF_VIEW04_BATTERY_WATER_ID, VIEW04_BATTERY_WATER_ARC0_ID);
	battery_quantity4 = grf_ctrl_get_form_id(GRF_VIEW04_BATTERY_WATER_ID, VIEW04_BATTERY_WATER_LABEL0_ID);
	water6 = grf_ctrl_get_form_id(GRF_VIEW04_BATTERY_WATER_ID, VIEW04_BATTERY_WATER_LABEL2_ID);

	//红色外圈旋转90度
	grf_arc_set_rotation(qingsao_arc1,90);

	//创建任务名
	battery_water_circle_task = grf_task_create(battery_water_task_cb,100,NULL);  //电池清扫动图
	red_outer_circle_task = grf_task_create(red_outer_circle_task_cb,50,NULL);  //红色外圈,跑马灯

	//立即刷新页面,不显示默认界面
	grf_task_ready(battery_water_circle_task);
	grf_task_ready(red_outer_circle_task);
}


void task_del04()
{
	grf_printf("task_del04\n");
	grf_task_del(battery_water_circle_task);
	grf_task_del(red_outer_circle_task);
}

