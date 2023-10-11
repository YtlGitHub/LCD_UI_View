#include "../../apps.h"


//创建任务名
grf_task_t *key_task07 = NULL;
grf_task_t *water_suction_task = NULL;  //创建吸水中间动图任务名


//创建控件名
grf_ctrl_t* water_suction_task_image2 = NULL;  //创建吸水中间动图控件名


//自定义变量
static u8 i = 1;  //吸水里面动图


//自定义数组
static unsigned char *image_name_water_suction[9] = {
	"/smart_water_suction/00.png",
	"/smart_water_suction/01.png",
	"/smart_water_suction/02.png",
	"/smart_water_suction/03.png",
	"/smart_water_suction/04.png",
	"/smart_water_suction/05.png",
	"/smart_water_suction/06.png",
	"/smart_water_suction/07.png",
	"/smart_water_suction/08.png"
};  //数字图片文件名保存到数组里面


//吸水动图
void water_suction_task_image_task_cb()
{
	if (isCmdCompletedBuf[7]) {
		if (ytl_erected) {
			grf_printf("ytl_erected == %d,倾斜状态\n", ytl_erected);
			if (ytl_dirty_degree <= 2 && ytl_dirty_degree >= 0) {
				grf_printf("i++ == %d,蓝色显示倾斜状态\n", i);
				grf_img_set_src(water_suction_task_image2, image_name_water_suction[i]);
			}
			else if(ytl_dirty_degree <= 4 && ytl_dirty_degree > 2){
				grf_printf("i++ == %d,橘色显示\n", i);
				grf_img_set_src(water_suction_task_image2, image_name_water_suction[i+4]);
			}
			i++;
			if (i > 4)
			{
				i=1;
			}
		}
		else {
			grf_printf("ytl_erected == %d,竖起状态\n", ytl_erected);
			grf_img_set_src(water_suction_task_image2, image_name_water_suction[i]);
			isCmdCompletedBuf[7] = GRF_FALSE;

		}
	}

}


//按键操作
void key_task07_cb(){
	if (ytl_right) {
		ytl_right = GRF_FALSE;
		grf_view_set_dis_view(GRF_VIEW01_ID);
	}
}


void task_create07()
{
	grf_printf("task_create7\n");

	//获取控件
	water_suction_task_image2 = grf_ctrl_get_form_id(GRF_VIEW07_WATER_SUCTION_ID, VIEW07_WATER_SUCTION_IMAGE0_ID);

	//创建任务名
	key_task07 = grf_task_create(key_task07_cb,100,NULL);  //按键任务名
	water_suction_task = grf_task_create(water_suction_task_image_task_cb,100,NULL);  //除菌中间动图任务名

	//立即刷新页面
	grf_task_ready(water_suction_task);
}


void task_del07()
{
	grf_printf("task_del07\n");
	grf_task_del(key_task07);
	grf_task_del(water_suction_task);
}
