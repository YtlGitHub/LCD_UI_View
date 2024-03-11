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
static grf_task_t *arc0_task1 = NULL;


//创建控件名
static grf_ctrl_t *img0 = NULL;
static grf_ctrl_t *img1 = NULL;
static grf_ctrl_t *img2 = NULL;
static grf_ctrl_t *img3 = NULL;
static grf_ctrl_t *cont0 = NULL;
static grf_ctrl_t *label_name_ID1 = NULL;  //选择模式图片下方文字控件名:1智能清扫,2智能除菌,3智能吸水,4系统设置
static grf_ctrl_t *arc0_ID10 = NULL;  //选择模式选择后自动开始到计时结束自动进入对应模式


//自定义变量
static u8 i = 1;  //控制选择模式1-4循环轮播图
static u16 arc0_value = 0;  //arc0的值
static u16 arc0_i = 0;  //arc0计数


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
	arc0_value = 0;
	arc0_i = switch_speed/10;
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
	//grf_printf("右键值i == %d\n",i);
	first_display();
	grf_label_set_txt(label_name_ID1, select_mode_value_array[i-1]);  //1智能清扫,2智能除菌,3智能吸水,4系统设置
}

//动画设置{动画主体，主体动画时间，(返回动画时间，返回动画延时时间,若无需返回动画，则均设置为0），变化的范围值，动画回调函数（函数参数为void *与u32）支持双函数，不需要则填NULL}
s32 yk_animation_set(grf_ctrl_t* ctrl,u32 time,u32 back_time,u32 back_time_delay,s32 value_start_a,s32 value_end_a,void *anim_cb_a,s32 value_start_b,s32 value_end_b,void *anim_cb_b)
{
	grf_anim_set_t anim_set = {0};
	anim_set.time = time;
	anim_set.back_time = back_time;
	anim_set.back_time_delay = back_time_delay;
	anim_set.value_start_a = value_start_a;
	anim_set.value_end_a = value_end_a;
	anim_set.anim_cb_a = anim_cb_a;
	anim_set.value_start_b = value_start_b;
	anim_set.value_end_b = value_end_b;
	anim_set.anim_cb_b = anim_cb_b;
	grf_animation_set(ctrl,&anim_set);
}

//按键任务
static void key_task01_cb()
{
	control_key_failure();
	//丢掉太快的静音键
	control_ytl_mute_v_away();

	if (ytl_right)
	{
		ytl_right = GRF_FALSE;
		//grf_printf("ytl_right_task1 == %d\n",ytl_right);
		arc0_value = 0;
		arc0_i = 0;
		grf_ctrl_set_hidden(arc0_ID10, GRF_TRUE);  //隐藏arc控件
		for(u8 i=0;i<4;i++)
		{
			grf_ctrl_t *obj=grf_ctrl_get_child(cont0,i);
			//grf_printf("grf_ctrl_get_x(%d)==%d\n",i,grf_ctrl_get_x(obj));
			//grf_printf("grf_ctrl_get_y(%d)==%d\n",i,grf_ctrl_get_y(obj));
			if(grf_ctrl_get_x(obj)==mode_select_icon_x0)
				yk_animation_set(obj,switch_speed,0,0,mode_select_icon_x0,mode_select_icon_x3,anim_img_pos,scale,scaling*scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x1)
				yk_animation_set(obj,switch_speed,0,0,mode_select_icon_x1,mode_select_icon_x0,anim_img_pos,scaling*scale,scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x2)
				yk_animation_set(obj,switch_speed,0,0,mode_select_icon_x2,mode_select_icon_x1,anim_img_pos,scaling*scale,scaling*scale,anim_img_zoom);
			if(grf_ctrl_get_x(obj)==mode_select_icon_x3)
				yk_animation_set(obj,switch_speed,0,0,mode_select_icon_x3,mode_select_icon_x2,anim_img_pos,scaling*scale,scaling*scale,anim_img_zoom);
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
		//grf_printf("右键值i == %d\n",i);
		grf_label_set_txt(label_name_ID1, select_mode_value_array[i-1]);  //1智能清扫,2智能除菌,3智能吸水,4系统设置

	}
	else if (ytl_back) {
		ytl_back = GRF_FALSE;
		//grf_printf("ytl_back_task1 == %d",ytl_back);
		grf_view_set_dis_view(ytl_view_get_cur_id);
	}
	else if (ytl_confirmation) {
		ytl_confirmation = GRF_FALSE;
		//grf_printf("确认值i: == %d\n",i);
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
}


//arc0任务
static void arc0_task01_cb()
{
	arc0_value++;
	if (arc0_i < switch_speed/10) {
		arc0_i++;
	}
	else if (arc0_i == switch_speed/10) {
		arc0_value = 0;
		arc0_i++;
		grf_ctrl_set_hidden(arc0_ID10, GRF_FALSE);  //显示arc控件
	}
	if (arc0_value == 300) {
		ytl_confirmation = GRF_TRUE;
	}
	grf_arc_set_value(arc0_ID10,arc0_value);
}


void task_create01()
{
	//grf_printf("task_create1\n");

	//获取控件
	img0 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE0_ID);
	img1 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE2_ID);
	img2 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE3_ID);
	img3 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_IMAGE4_ID);
	cont0 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_CONTAINER0_ID);
	label_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_LABEL0_ID);
	arc0_ID10 = grf_ctrl_get_form_id(GRF_VIEW01_ID, VIEW01_ARC0_ID);

	select_mode_value_var_i();

	//创建任务
	key_task1 = grf_task_create(key_task01_cb,100,NULL);  //按键任务
	arc0_task1 = grf_task_create(arc0_task01_cb,10,NULL);  //选中模式后倒计时进入对应模式任务
}


void task_del01(void)
{
	//grf_printf("task_del01\n");
	grf_task_del(key_task1);
	grf_task_del(arc0_task1);
}
