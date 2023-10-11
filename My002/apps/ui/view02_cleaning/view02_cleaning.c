#include "../../apps.h"


//创建任务名
static grf_task_t *qingsao_task = NULL;
static grf_task_t *key_task02 = NULL;


//创建控件名
static grf_ctrl_t* qingsao_image2 = NULL;


//自定义变量
static u8 i = 1;  //清扫里面动图


//自定义数组
static u8 *image_name_cleaning[EXTERNAL_BUFFER_SIZE] = {
	"/smart_cleaning/00.png",
	"/smart_cleaning/01.png",
	"/smart_cleaning/02.png",
	"/smart_cleaning/03.png",
	"/smart_cleaning/04.png",
	"/smart_cleaning/05.png",
	"/smart_cleaning/06.png",
	"/smart_cleaning/07.png",
	"/smart_cleaning/08.png",
	"/smart_cleaning/09.png",
	"/smart_cleaning/10.png"
};  //中间清扫动图文件名保存到数组里面


//清扫动图
static void Intelligent_intermediate_image_task_cb()
{
	if (isCmdCompletedBuf[2]) {
		grf_printf("Intelligent_intermediate_image_task_cb.ytl_erected == %d\n", ytl_erected);
		if (ytl_erected) {
			grf_printf("ytl_erected == %d,倾斜状态\n", ytl_erected);
			if (ytl_dirty_degree <= 2 && ytl_dirty_degree >= 0) {
				grf_printf("i++ == %d,蓝色显示倾斜状态\n", i);
				grf_img_set_src(qingsao_image2, image_name_cleaning[i]);

			}
			else if(ytl_dirty_degree <= 4 && ytl_dirty_degree > 2){
				grf_printf("i++ == %d,橘色显示\n", i+5);
				grf_img_set_src(qingsao_image2, image_name_cleaning[i+5]);
			}
			i++;
			if (i > 5) {
				i = 1;
			}
		}
		else {
			grf_printf("ytl_erected == %d,竖起状态\n", ytl_erected);
			grf_img_set_src(qingsao_image2, image_name_cleaning[i]);
			isCmdCompletedBuf[2] = GRF_FALSE;
		}
	}

}


//按键操作
static void key_task02_cb(){
	if (ytl_right) {
		grf_printf("ytl_right == %d",ytl_right);
		grf_view_set_dis_view(GRF_VIEW01_ID);
		ytl_right = GRF_FALSE;
	}
}


void task_create02()
{
	grf_printf("task_create2\n");
//	ytl_erected = GRF_TRUE;  //是否竖起，0竖起，1倾斜
//	ytl_battery_quantity_val = 20;  //电量信息值
//	ytl_dirty_degree = 1;
//	isCmdCompletedBuf[2] = GRF_TRUE;
//	isCmdCompletedBuf[4] = GRF_TRUE;

	//获取控件
	qingsao_image2 = grf_ctrl_get_form_id(GRF_VIEW02_CLEANING_ID, VIEW02_CLEANING_IMAGE0_ID);

	//创建任务
	key_task02 = grf_task_create(key_task02_cb,100,NULL);  //创建按键任务
	qingsao_task = grf_task_create(Intelligent_intermediate_image_task_cb,100,NULL);  //创建清扫动图任务

	//立即刷新页面,不显示默认页面
	grf_task_ready(qingsao_task);
}


void task_del02()
{
	grf_printf("task_del02\n");
	grf_task_del(key_task02);
	grf_task_del(qingsao_task);

}
