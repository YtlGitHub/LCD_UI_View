#include "../../apps.h"


#define above_y 0  //上面图y坐标
#define under_y 192  //下面图y坐标
#define under_y1 384  //下面图y1坐标
#define hundredth_x 0  //百位x坐标
#define ten_x 120  //十位x坐标
#define unit_x 250  //个位x坐标

#define switch_speed 260  //切换速度



//创建任务名
static grf_task_t *key_task05 = NULL;
static grf_task_t *sterilization_fluid_preparation_digit_task = NULL;
static grf_task_t *sterilization_fluid_preparation_task = NULL;


//创建控件名
static grf_ctrl_t *cont0_ID2 = NULL;  //容器
static grf_ctrl_t *obj0 = NULL;  //百位数字1
static grf_ctrl_t *obj1 = NULL;  //十位数字上
static grf_ctrl_t *obj2 = NULL;  //十位数字下
static grf_ctrl_t *obj3 = NULL;  //个位数字上
static grf_ctrl_t *obj4 = NULL;  //个位数字下

static grf_ctrl_t* image_fluid_circulate_11 = NULL;  //右边溶液循环动图效果控件名


//自定义变量
static u8 j = 0;  //个位图切换计数，0-9循环跑
static u8 k = 0;  //计数百分比0-100


//自定义数组
static unsigned char *image_digit[EXTERNAL_BUFFER_SIZE] = {
	"/sterilization_fluid_preparation/number_big_0.png",
	"/sterilization_fluid_preparation/number_big_1.png",
	"/sterilization_fluid_preparation/number_big_2.png",
	"/sterilization_fluid_preparation/number_big_3.png",
	"/sterilization_fluid_preparation/number_big_4.png",
	"/sterilization_fluid_preparation/number_big_5.png",
	"/sterilization_fluid_preparation/number_big_6.png",
	"/sterilization_fluid_preparation/number_big_7.png",
	"/sterilization_fluid_preparation/number_big_8.png",
	"/sterilization_fluid_preparation/number_big_9.png"
};  //数字图片文件名保存到数组里面
static unsigned char *image_fluid_circulate[EXTERNAL_BUFFER_SIZE] = {
	"/sterilization_fluid_preparation/0.png",
	"/sterilization_fluid_preparation/1.png",
	"/sterilization_fluid_preparation/2.png",
	"/sterilization_fluid_preparation/3.png",
	"/sterilization_fluid_preparation/4.png"
};  //右边溶液循环图片文件名保存到数组里面


//第一次进入
static void first_display(void)
{
	j = 0;  //个位图切换计数，0-9循环跑
	k = 0;  //计数百分比0-100
	grf_img_set_src(obj0,image_digit[1]);
	grf_img_set_src(obj1,image_digit[0]);
	grf_img_set_src(obj2,image_digit[1]);
	grf_img_set_src(obj3,image_digit[0]);
	grf_img_set_src(obj4,image_digit[1]);
	grf_ctrl_set_pos(obj0, hundredth_x,under_y);
	grf_ctrl_set_pos(obj1, ten_x,above_y);
	grf_ctrl_set_pos(obj2, ten_x,under_y);
	grf_ctrl_set_pos(obj3, unit_x,above_y);
	grf_ctrl_set_pos(obj4, unit_x,under_y);
}


//自定义函数
static void anim_img_pos(void* var, u32 v)
{
	grf_ctrl_set_pos(var,unit_x,v);
}
static void anim_img_pos1(void* var, u32 v)
{
	grf_ctrl_set_pos(var,ten_x,v);
}
static void anim_img_pos2(void* var, u32 v)
{
	grf_ctrl_set_pos(var,hundredth_x,v);
}
//动画滑动效果除菌液制备中数字图片
void sterilization_fluid_preparation_digit_task_cd()
{
	k++;
	if (k == 50) {
		//除菌液已制备完成50%
		switch_language_pack("05_01_sterilization_fluid_preparation_50%");
	}
	//个位向上滑动
	if (k >= 0 && k <= 100) {
		//改变个位y坐标位置
		grf_img_set_src(obj3,image_digit[j]);
		grf_ctrl_set_pos(obj3,unit_x,above_y);
		if (j == 9)
		{
			grf_img_set_src(obj4,image_digit[0]);
		}
		else
		{
			grf_img_set_src(obj4,image_digit[j+1]);
		}
		grf_ctrl_set_pos(obj4,unit_x,under_y);
		//刷新控件位置
		grf_ctrl_update_location(obj3);
		grf_ctrl_update_location(obj4);
		//动画个位向上滑动
		yk_animation_set(obj3,switch_speed,0,0,above_y,-under_y,anim_img_pos,0,0,NULL);
		yk_animation_set(obj4,switch_speed,0,0,under_y,above_y,anim_img_pos,0,0,NULL);
	}
	//十位向上滑动
	if (k == 10 || k == 20 || k == 30 || k == 40 || k == 50 || k == 60 || k == 70 || k == 80 || k == 90 || k == 100)
	{
		if (k == 100) {
			grf_img_set_src(obj1,image_digit[k/10-1]);
			grf_ctrl_set_pos(obj1,unit_x,above_y);
			grf_img_set_src(obj2,image_digit[0]);
			grf_ctrl_set_pos(obj2,unit_x,under_y);
			//动画百位向上滑动
			yk_animation_set(obj0,switch_speed,0,0,under_y,above_y,anim_img_pos2,0,0,NULL);
		}
		else {
			grf_img_set_src(obj1,image_digit[k/10-1]);
			grf_ctrl_set_pos(obj1,unit_x,above_y);
			grf_img_set_src(obj2,image_digit[k/10]);
			grf_ctrl_set_pos(obj2,unit_x,under_y);
		}
		//刷新控件位置
		grf_ctrl_update_location(obj1);
		grf_ctrl_update_location(obj2);
		//动画十位向上滑动
		yk_animation_set(obj1,switch_speed,0,0,above_y,-under_y,anim_img_pos1,0,0,NULL);
		yk_animation_set(obj2,switch_speed,0,0,under_y,above_y,anim_img_pos1,0,0,NULL);
	}
	//除菌夜制备完成,跳转下一个对应界面
	if (k > 101)
	{
		ytl1_cleaning_method = GRF_TRUE;
		if (ytl_view_get_cur_id == GRF_VIEW09_SELF_CLEANING_MODE_ID)
		{
			grf_view_set_dis_view(GRF_VIEW10_SELF_CLEANING_ID);
		}
		else
		{
			grf_view_set_dis_view(GRF_VIEW06_STERILIZATION_ID);
		}
	}

	j++;
	if (j > 9) {
		j = 0;
	}
	//grf_printf("j,k =******************************************************= %d %d\n",j,k);
}


void sterilization_image_circulate(){
	static u8 var = 0;
	grf_img_set_src(image_fluid_circulate_11, image_fluid_circulate[var]);
	var++;
	if (var > 4) {
		var = 0;
	}
}


//除菌液制备中右边溶液慢慢变高
void sterilization_fluid_preparation_task_cd(){
	sterilization_image_circulate();
	if (k == 0 ) {
		grf_ctrl_set_pos(image_fluid_circulate_11, 0, 135);
	}
	else if(k>0 && k<=100){
		grf_ctrl_set_pos(image_fluid_circulate_11, 0, 135 - 1.35*k);
	}
}


//按键操作
void key_task05_cb(){
	if (ytl_right) {
		ytl_right = GRF_FALSE;
		if (ytl_view_get_cur_id != GRF_VIEW09_SELF_CLEANING_MODE_ID) {
			grf_view_set_dis_view(GRF_VIEW01_ID);
		}
	}
	else if (ytl_self_cleaning) {
		ytl_self_cleaning = GRF_FALSE;
		//如果在自清洁按自清洁键就取消自清洁跳转到请清理污水箱避免异味
		if (ytl_view_get_cur_id == GRF_VIEW09_SELF_CLEANING_MODE_ID) {
			grf_view_set_dis_view(GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID);
		}
	}
}


void task_create05()
{
	//grf_printf("task_create05\n");


	//获取控件
	cont0_ID2 = grf_ctrl_get_form_id(GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID, VIEW05_STERILIZATION_FLUID_PREPARATION_CONTAINER0_ID);
	obj0=grf_ctrl_get_child(cont0_ID2,0);
	obj1=grf_ctrl_get_child(cont0_ID2,1);
	obj2=grf_ctrl_get_child(cont0_ID2,2);
	obj3=grf_ctrl_get_child(cont0_ID2,3);
	obj4=grf_ctrl_get_child(cont0_ID2,4);
	image_fluid_circulate_11 = grf_ctrl_get_form_id(GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID, VIEW05_STERILIZATION_FLUID_PREPARATION_IMAGE7_ID);


	//第一次进入
	first_display();


	//创建任务
	key_task05 = grf_task_create(key_task05_cb,100,NULL);
	//除菌液制备中数字图片
	sterilization_fluid_preparation_digit_task = grf_task_create(sterilization_fluid_preparation_digit_task_cd,switch_speed,NULL);
	//除菌液制备中右边溶液慢慢变高
	sterilization_fluid_preparation_task = grf_task_create(sterilization_fluid_preparation_task_cd,100,NULL);

	//立即刷新页面,不显示默认界面
	grf_task_ready(sterilization_fluid_preparation_digit_task);
	grf_task_ready(sterilization_fluid_preparation_task);
}


void task_del05()
{
	//grf_printf("task_del05\n");
	grf_task_del(key_task05);
	grf_task_del(sterilization_fluid_preparation_digit_task);
	grf_task_del(sterilization_fluid_preparation_task);
}

