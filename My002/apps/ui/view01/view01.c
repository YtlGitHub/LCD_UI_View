#include "../../apps.h"


#define mode_select_icon_x0 200  //模式选择图标img0x坐标
#define mode_select_icon_x1 400  //模式选择图标img1x坐标
#define mode_select_icon_x2 201  //模式选择图标img2x坐标
#define mode_select_icon_x3 0  //模式选择图标img3x坐标
#define mode_select_icon_y 0  //模式选择图标y坐标
#define switch_speed 300  //切换速度
#define scale 256  //图大小缩放:256原大小,128缩小一倍,512放大一倍
#define scaling 0.6  //缩放比例


//创建任务名
static grf_task_t *key_task1 = NULL;


//创建控件名
static grf_ctrl_t *img0 = NULL;
static grf_ctrl_t *img1 = NULL;
static grf_ctrl_t *img2 = NULL;
static grf_ctrl_t *img3 = NULL;
static grf_ctrl_t *cont0 = NULL;
static grf_ctrl_t *label_name_ID1 = NULL;  //选择模式图片下方文字控件名:1智能清扫,2智能除菌,3智能吸水,4系统设置


//自定义变量
static u8 i = 1;  //控制选择模式1-4循环轮播图


//自定义数组
static u8 *select_mode_array[4] = {"/mode_select/1_1.png","/mode_select/2_1.png","/mode_select/3_1.png","/mode_select/4_1.png"};
static u8 *select_mode_array_3[4] = {"/mode_select/1_3.png","/mode_select/2_3.png","/mode_select/3_3.png","/mode_select/4_3.png"};
static u8 *select_mode_value_array[4] = {"#smart_cleaning","#smart_sterilization","#smart_water_suction","#system_setting"};


//自定义函数
static void anim_img_pos(void* var, u16 v)
{
	grf_ctrl_set_pos(var,v,mode_select_icon_y);
}
static void anim_img_zoom(void* var, u32 v)
{
	grf_img_zoom_setting(var,v);
}
//第一次进入显示的界面
static void first_display()
{
	if (i == 1) {
		grf_ctrl_move_forground(img0);

		grf_img_zoom_setting(img0,scale);
		grf_img_zoom_setting(img1,scaling*scale);
		grf_img_zoom_setting(img2,scaling*scale);
		grf_img_zoom_setting(img3,scaling*scale);

		grf_ctrl_set_pos(img0,mode_select_icon_x0,mode_select_icon_y);
		grf_ctrl_set_pos(img1,mode_select_icon_x1,mode_select_icon_y);
		grf_ctrl_set_pos(img2,mode_select_icon_x2,mode_select_icon_y);
		grf_ctrl_set_pos(img3,mode_select_icon_x3,mode_select_icon_y);

		grf_img_set_src(img0, select_mode_array[i-1]);
		grf_img_set_src(img1, select_mode_array_3[1]);
		grf_img_set_src(img2, select_mode_array_3[2]);
		grf_img_set_src(img3, select_mode_array_3[3]);
	}
	else if (i == 2) {
		grf_ctrl_move_forground(img1);
		grf_img_zoom_setting(img0,scaling*scale);
		grf_img_zoom_setting(img1,scale);
		grf_img_zoom_setting(img2,scaling*scale);
		grf_img_zoom_setting(img3,scaling*scale);
		grf_ctrl_set_pos(img1,mode_select_icon_x0,mode_select_icon_y);
		grf_ctrl_set_pos(img2,mode_select_icon_x1,mode_select_icon_y);
		grf_ctrl_set_pos(img3,mode_select_icon_x2,mode_select_icon_y);
		grf_ctrl_set_pos(img0,mode_select_icon_x3,mode_select_icon_y);
		grf_img_set_src(img1, select_mode_array[i-1]);
		grf_img_set_src(img0, select_mode_array_3[0]);
		grf_img_set_src(img2, select_mode_array_3[2]);
		grf_img_set_src(img3, select_mode_array_3[3]);
	}
	else if (i == 3) {
		grf_ctrl_move_forground(img2);
		grf_img_zoom_setting(img0,scaling*scale);
		grf_img_zoom_setting(img1,scaling*scale);
		grf_img_zoom_setting(img2,scale);
		grf_img_zoom_setting(img3,scaling*scale);
		grf_ctrl_set_pos(img2,mode_select_icon_x0,mode_select_icon_y);
		grf_ctrl_set_pos(img3,mode_select_icon_x1,mode_select_icon_y);
		grf_ctrl_set_pos(img0,mode_select_icon_x2,mode_select_icon_y);
		grf_ctrl_set_pos(img1,mode_select_icon_x3,mode_select_icon_y);
		grf_img_set_src(img2, select_mode_array[i-1]);
		grf_img_set_src(img0, select_mode_array_3[0]);
		grf_img_set_src(img1, select_mode_array_3[1]);
		grf_img_set_src(img3, select_mode_array_3[3]);
	}
	else if (i == 4) {
		grf_ctrl_move_forground(img3);
		grf_img_zoom_setting(img0,scaling*scale);
		grf_img_zoom_setting(img1,scaling*scale);
		grf_img_zoom_setting(img2,scaling*scale);
		grf_img_zoom_setting(img3,scale);
		grf_ctrl_set_pos(img3,mode_select_icon_x0,mode_select_icon_y);
		grf_ctrl_set_pos(img0,mode_select_icon_x1,mode_select_icon_y);
		grf_ctrl_set_pos(img1,mode_select_icon_x2,mode_select_icon_y);
		grf_ctrl_set_pos(img2,mode_select_icon_x3,mode_select_icon_y);
		grf_img_set_src(img3, select_mode_array[i-1]);
		grf_img_set_src(img0, select_mode_array_3[0]);
		grf_img_set_src(img1, select_mode_array_3[1]);
		grf_img_set_src(img2, select_mode_array_3[2]);
	}
	grf_img_set_pivot(img0,200,350);
	grf_img_set_pivot(img1,200,350);
	grf_img_set_pivot(img2,200,350);
	grf_img_set_pivot(img3,200,350);
}


//切换高亮显示
static void switch_highlight()
{
	if (i == 1) {
		grf_img_set_src(img0, select_mode_array[i-1]);
		grf_img_set_src(img3, select_mode_array_3[3]);

	}
	else if (i == 2) {
		grf_img_set_src(img1, select_mode_array[i-1]);
		grf_img_set_src(img0, select_mode_array_3[0]);

	}
	else if (i == 3) {
		grf_img_set_src(img2, select_mode_array[i-1]);
		grf_img_set_src(img1, select_mode_array_3[1]);

	}
	else if (i == 4) {
		grf_img_set_src(img3, select_mode_array[i-1]);
		grf_img_set_src(img2, select_mode_array_3[2]);
	}
	grf_img_set_pivot(img0,200,350);
	grf_img_set_pivot(img1,200,350);
	grf_img_set_pivot(img2,200,350);
	grf_img_set_pivot(img3,200,350);
}


//在清扫界面按右键进入模式选择时,显示对应的界面
static void select_mode_value_var_i(){
	if (ytl_view_get_cur_id == 2) {
		i = 2;
	}
	else if (ytl_view_get_cur_id == 5) {
		i = 3;
	}
	else if (ytl_view_get_cur_id == 7) {
		i = 1;
	}
	grf_printf("右键值i == %d\n",i);
	first_display();
	grf_label_set_txt(label_name_ID1, select_mode_value_array[i-1]);  //1智能清扫,2智能除菌,3智能吸水,4系统设置
}

//按键任务
static void key_task01_cb(){
	control_key_failure();

	if (ytl_right)
	{
		ytl_right = GRF_FALSE;
		grf_printf("ytl_right_task1 == %d\n",ytl_right);

		for(u8 i=0;i<4;i++)
		{
			grf_ctrl_t *obj=grf_ctrl_get_child(cont0,i);
			grf_printf("grf_ctrl_get_x(%d)==%d\n",i,grf_ctrl_get_x(obj));
			grf_printf("grf_ctrl_get_y(%d)==%d\n",i,grf_ctrl_get_y(obj));
			if(grf_ctrl_get_x(obj)==mode_select_icon_x0)
				grf_animation_set(obj,switch_speed,0,0,mode_select_icon_x0,mode_select_icon_x3,anim_img_pos,scale,scaling*scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x1)
				grf_animation_set(obj,switch_speed,0,0,mode_select_icon_x1,mode_select_icon_x0,anim_img_pos,scaling*scale,scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x2)
				grf_animation_set(obj,switch_speed,0,0,mode_select_icon_x2,mode_select_icon_x1,anim_img_pos,scaling*scale,scaling*scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x3)
				grf_animation_set(obj,switch_speed,0,0,mode_select_icon_x3,mode_select_icon_x2,anim_img_pos,scaling*scale,scaling*scale,anim_img_zoom);
			grf_ctrl_update_location(obj);
		}
		grf_ctrl_update_location(cont0);
		for(u8 i=0;i<4;i++)
			{
				grf_ctrl_t *obj=grf_ctrl_get_child(cont0,i);
				if(grf_ctrl_get_x(obj)==mode_select_icon_x2)
					grf_ctrl_move_background(obj);
				if(grf_ctrl_get_x(obj)==mode_select_icon_x1)
					grf_ctrl_move_forground(obj);
			}
		i++;
		if (i > 4) {
			i = 1;
		}
		switch_highlight();
		grf_printf("右键值i == %d\n",i);
		grf_label_set_txt(label_name_ID1, select_mode_value_array[i-1]);  //1智能清扫,2智能除菌,3智能吸水,4系统设置

	}
	else if (ytl_back) {
		ytl_back = GRF_FALSE;
		grf_printf("ytl_back_task1 == %d",ytl_back);
		grf_view_set_dis_view(ytl_view_get_cur_id);
	}
	else if (ytl_confirmation) {
		ytl_confirmation = GRF_FALSE;
		grf_printf("确认值i: == %d\n",i);
		if (i == 1)
		{
			grf_view_set_dis_view(GRF_VIEW02_CLEANING_ID);  //智能清扫
		}
		else if (i == 2)
		{
			grf_view_set_dis_view(GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID);  //除菌液制备中-->智能除菌
		}
		else if (i == 3)
		{
			grf_view_set_dis_view(GRF_VIEW07_WATER_SUCTION_ID);  //智能吸水
		}
		else if (i == 4)
		{
			grf_view_set_dis_view(GRF_VIEW17_SYSTEM_SETTING_ID);  //系统设置
		}
	}
	else if (ytl_help) {
		ytl_help = GRF_FALSE;
		grf_view_set_dis_view(GRF_VIEW12_HELP_ID);
	}
}


void task_create01()
{
	grf_printf("task_create1--key_task1 == %p\n",key_task1);

	//获取控件
	img0 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE0_ID);
	img1 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE2_ID);
	img2 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE3_ID);
	img3 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE4_ID);
	cont0 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_CONTAINER0_ID);
	label_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_LABEL0_ID);

	select_mode_value_var_i();

	//创建按键任务
	key_task1 = grf_task_create(key_task01_cb,100,NULL);
}


void task_del01(void)
{
	grf_printf("task_del01\n");
	grf_task_del(key_task1);
}
