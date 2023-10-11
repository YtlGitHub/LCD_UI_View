#include "../../apps.h"


//创建任务名
grf_task_t *key_task06 = NULL;
grf_task_t *sterilization_task = NULL;  //创建除菌中间动图任务名


//控件名
grf_ctrl_t* sterilization_image2 = NULL;  //创建除菌中间动图控件名


//自定义变量
static u8 i = 1;  //除菌里面动图
static u8 *image_name_sterilization[13] = {
	"/smart_sterilization/00.png",
	"/smart_sterilization/01.png",
	"/smart_sterilization/02.png",
	"/smart_sterilization/03.png",
	"/smart_sterilization/04.png",
	"/smart_sterilization/05.png",
	"/smart_sterilization/06.png",
	"/smart_sterilization/07.png",
	"/smart_sterilization/08.png",
	"/smart_sterilization/09.png",
	"/smart_sterilization/10.png",
	"/smart_sterilization/11.png",
	"/smart_sterilization/12.png"
};  //中间除菌液动图文件名保存到数组里面


//除菌动图
void sterilization_image_task_cb()
{
	if (isCmdCompletedBuf[6]) {
		if (ytl_erected) {
			grf_printf("ytl_erected == %d,倾斜状态\n", ytl_erected);
			if (ytl_dirty_degree <= 2 && ytl_dirty_degree >= 0)
			{
				grf_printf("i++ == %d,蓝色显示倾斜状态\n", i);
				grf_img_set_src(sterilization_image2, image_name_sterilization[i]);
			}
			else if(ytl_dirty_degree <= 4 && ytl_dirty_degree > 2)
			{
				grf_printf("i++ == %d,橘色显示\n", i);
				grf_img_set_src(sterilization_image2, image_name_sterilization[i+6]);
			}
			i++;
			if (i > 6)
			{
				i=1;
			}
		}
		else
		{
			grf_printf("ytl_erected == %d,竖起状态\n", ytl_erected);
			grf_img_set_src(sterilization_image2, image_name_sterilization[i]);
			isCmdCompletedBuf[6] = GRF_FALSE;
		}
	}

}


//按键操作
void key_task06_cb(){
	if (ytl_right) {
		ytl_right = GRF_FALSE;
		grf_view_set_dis_view(GRF_VIEW01_ID);

	}
}


void task_create06()
{
//	ytl_erected = GRF_TRUE;  //是否竖起，0竖起，1倾斜
//	ytl_battery_quantity_val = 20;  //电量信息值
//	ytl_dirty_degree = 2;
//	isCmdCompletedBuf[6] = GRF_TRUE;
//	isCmdCompletedBuf[4] = GRF_TRUE;
	grf_printf("task_create6 %p\n",key_task06);

	//获取控件
	sterilization_image2 = grf_ctrl_get_form_id(GRF_VIEW06_STERILIZATION_ID, VIEW06_STERILIZATION_IMAGE0_ID);

	//创建任务
	key_task06 = grf_task_create(key_task06_cb,100,NULL);
	sterilization_task = grf_task_create(sterilization_image_task_cb,100,NULL);

	//立即刷新页面
	grf_task_ready(sterilization_task);
}


void task_del06()
{
	grf_task_del(key_task06);
	grf_task_del(sterilization_task);
}
