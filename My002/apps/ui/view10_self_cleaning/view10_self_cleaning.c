#include "../../apps.h"


//创建按键任务
grf_task_t *key_task10 = NULL;
grf_task_t *self_cleaning_task = NULL;


//创建控件名
grf_ctrl_t *self_cleaning_control_name_ID1 = NULL;  //自清洁中间动图控件名
grf_ctrl_t *self_cleaning_control_name_ID2 = NULL;  //自清洁下方文字显示控件名


//自定义变量
static u8 i = 0;  //控制循环跑动变量
static u16 j = 0;  //控制每个动图的时间长短
static u8 k = 20;  //控制每个动图的时间长短的倍数
static u8 uart_only_sent_once = 2;  //控制串口数据只发送一次


//自定义数组
//滚刷除菌浸泡中 滚刷除菌清洗中
static u8 *self_cleaning_image_name1[16] = {
	"/self_cleaning/1_00.png",
	"/self_cleaning/1_01.png",
	"/self_cleaning/1_02.png",
	"/self_cleaning/1_03.png",
	"/self_cleaning/1_04.png",
	"/self_cleaning/1_05.png",
	"/self_cleaning/1_06.png",
	"/self_cleaning/1_07.png",
	"/self_cleaning/1_08.png",
	"/self_cleaning/1_09.png",
	"/self_cleaning/1_10.png",
	"/self_cleaning/1_11.png",
	"/self_cleaning/1_12.png",
	"/self_cleaning/1_13.png",
	"/self_cleaning/1_14.png",
	"/self_cleaning/1_15.png"
};
//管道除菌清洗中
static u8 *self_cleaning_image_name2[6] = {
	"/self_cleaning/2_00.png",
	"/self_cleaning/2_01.png",
	"/self_cleaning/2_02.png",
	"/self_cleaning/2_03.png",
	"/self_cleaning/2_04.png",
	"/self_cleaning/2_05.png"
};
//深度清洁中
static u8 *self_cleaning_image_name3[10] = {
		"/self_cleaning/3_00.png",
		"/self_cleaning/3_01.png",
		"/self_cleaning/3_02.png",
		"/self_cleaning/3_03.png",
		"/self_cleaning/3_04.png",
		"/self_cleaning/3_05.png",
		"/self_cleaning/3_06.png",
		"/self_cleaning/3_07.png",
		"/self_cleaning/3_08.png",
		"/self_cleaning/3_09.png"
};
//滚刷离心风干中 滚刷干燥中
static u8 *self_cleaning_image_name4[13] = {
	"/self_cleaning/4_00.png",
	"/self_cleaning/4_01.png",
	"/self_cleaning/4_02.png",
	"/self_cleaning/4_03.png",
	"/self_cleaning/4_04.png",
	"/self_cleaning/4_05.png",
	"/self_cleaning/4_06.png",
	"/self_cleaning/4_07.png",
	"/self_cleaning/4_08.png",
	"/self_cleaning/4_09.png",
	"/self_cleaning/4_10.png",
	"/self_cleaning/4_11.png",
	"/self_cleaning/4_12.png"
};
//自清洁完成
static u8 *self_cleaning_image_name5[2] = {
	"/self_cleaning/5_00.png",
	"/self_cleaning/5_01.png"
};


//控制串口只发送一次自定义函数
static void ytl_uart_only_sent_once(u8 data2)
{
	grf_printf("ytl_uart_only_sent_once1 == %d\n",uart_only_sent_once);
	if (uart_only_sent_once == data2)
	{
		//自清洁语音播报
		if (data2 == 2)
		{
			//语音播报测试:"滚刷除菌浸泡中"
			switch_language_pack("10_02_self_cleaning");
		}
		else if (data2 == 3)
		{
			//语音播报测试:"滚刷除菌清洗中"
			switch_language_pack("10_03_self_cleaning");
		}
		else if (data2 == 4)
		{
			//语音播报测试:"管道除菌清洗中"
			switch_language_pack("10_04_self_cleaning");
		}
		else if (data2 == 5)
		{
			//语音播报测试:"深度清洁中"
			switch_language_pack("10_05_self_cleaning");
		}
		else if (data2 == 6)
		{
			//语音播报测试:"滚刷离心风干中"
			switch_language_pack("10_06_self_cleaning");
		}
		else if (data2 == 7)
		{
			//语音播报测试:"滚刷干燥中"
			switch_language_pack("10_07_self_cleaning");
		}
		else if (data2 == 8)
		{
			//语音播报测试:"自清洁完成"
			switch_language_pack("10_08_self_cleaning");
		}
		//发送串口数据
		if (ytl_mode_select_uart == 1)
		{
			grf_reg_com_send(0x06, 0xA0, 0x04, 0x01, data2);
			if (data2 == 0x06)
			{
				uart_only_sent_once = data2 +2;
			}
			else
			{
				uart_only_sent_once = data2 +1;
			}
		}
		else if (ytl_mode_select_uart == 2)
		{
			grf_reg_com_send(0x06, 0xA0, 0x04, 0x02, data2);
			uart_only_sent_once = data2 +1;
		}
	}
	grf_printf("ytl_uart_only_sent_once2 == %d\n",uart_only_sent_once);
}


//自定义全局变量
u16 j_self_cleaning_var = 0;  //故障发生时记录当前自清洁的位置
u8 uart_only_sent_once_self_cleaning_var = 2;  //故障发生时记录当前自清洁串口发送到哪个位置
//第一次进入
static void first_display(void)
{
	i = 0;  //控制循环跑动变量
	j = j_self_cleaning_var;  //控制每个动图的时间长短

	//发送故障回来又发一遍指令
	uart_only_sent_once = uart_only_sent_once_self_cleaning_var;
	if (ytl_mode_select_uart == 1) {
		if (uart_only_sent_once == 0x08) {
			uart_only_sent_once -= 2;
		}
		else {
			uart_only_sent_once -= 1;
		}
	}
	else if (ytl_mode_select_uart == 2) {
		uart_only_sent_once -= 1;
	}

	//如果是首次进入就把减的加回来,否则就是发生故障修复之后回到当前界面,就重新再发一遍当前指令
	if (uart_only_sent_once == 1) {
		uart_only_sent_once += 1;
	}
	else {
		ytl_uart_only_sent_once(uart_only_sent_once);
	}
}


//自清洁中间动图显示
void self_cleaning_task_cb()
{
	grf_printf("isCmdCompletedBuf[10] == %d\n", isCmdCompletedBuf[10]);
	if (isCmdCompletedBuf[10])
	{
		i++;
		if (j == 0)
		{
			ytl_uart_only_sent_once(0x02);

			grf_label_set_txt(self_cleaning_control_name_ID2,"#brush_roll_sterilization_soaking");  //滚刷除菌浸泡中
		}
		else if (j == 0.5*k)
		{
			ytl_uart_only_sent_once(0x03);

			grf_label_set_txt(self_cleaning_control_name_ID2,"#brush_roll_sterilization_cleaning");  //滚刷除菌清洗中

		}
		else if (j == k)
		{
			ytl_uart_only_sent_once(0x04);

			grf_label_set_txt(self_cleaning_control_name_ID2,"#pipeline_sterilization_cleaning");  //管道除菌清洗中
		}
		else if (j == 3*k)
		{
			ytl_uart_only_sent_once(0x05);

			grf_label_set_txt(self_cleaning_control_name_ID2,"#deep_cleaning");  //深度清洁中
		}
		else if (j == 4*k)
		{
			ytl_uart_only_sent_once(0x06);

			grf_label_set_txt(self_cleaning_control_name_ID2,"#brush_roll_centrifugal_drying");  //滚刷离心风干中
		}

        //判断是快速还是超强
		if (ytl_mode_select_uart == 1)
		{
			if (j == 5*k)
			{
				ytl_uart_only_sent_once(0x08);

				grf_label_set_txt(self_cleaning_control_name_ID2,"#self_cleaning_completed");  //自清洁完成
				j++;
			}
			else if (j > 5*k && j < 6*k)
			{
				j++;
			}
			else if (j == 6*k)
			{
				//grf_delay(3000);
				grf_view_set_dis_view(GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID);
				isCmdCompletedBuf[10] = GRF_FALSE;
			}
		}
		else if (ytl_mode_select_uart == 2)
		{
			if (j == 5*k)
			{
				ytl_uart_only_sent_once(0x07);

				grf_label_set_txt(self_cleaning_control_name_ID2,"#roller_brush_drying");  //滚刷干燥中(超强4分钟)
			}
			else if (j == 13*k)
			{
				ytl_uart_only_sent_once(0x08);

				grf_label_set_txt(self_cleaning_control_name_ID2,"#self_cleaning_completed");  //自清洁完成
				j++;
			}
			else if (j > 13*k && j < 14*k)
			{
				j++;
			}
			else if (j == 14*k)
			{
				//grf_delay(3000);
				grf_view_set_dis_view(GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID);
				isCmdCompletedBuf[10] = GRF_FALSE;
			}
		}
		if (j >= 0 && j <0.5*k)
		{
			grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name1[i]);
			if (i >= 15) {
				i = 0;
				j++;
			}
		}
		else if (j >= 0.5*k && j < k)
		{
			grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name1[i]);
			if (i >= 15) {
				i = 0;
				j++;
			}
		}
		else if (j >= k && j < 3*k)
		{
			grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name2[i]);
			if (i >= 5) {
				i = 0;
				j++;
			}
		}
		else if (j >= 3*k && j < 4*k)
		{
			grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name3[i]);
			if (i >= 9) {
				i = 0;
				j++;
			}
		}
		else if (j >= 4*k && j < 5*k)
		{
			grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name4[i]);
			if (i >= 12) {
				i = 0;
				j++;
			}
		}

		if (ytl_mode_select_uart == 1)
		{
			if (j == 5*k)
			{
				grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name5[1]);
			}
		}
		else if (ytl_mode_select_uart == 2)
		{
			if (j >= 5*k && j < 13*k)
			{
				grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name4[i]);
				if (i >= 12)
				{
					i = 0;
					j++;
				}
			}
			if (j == 13*k)
			{
				grf_img_set_src(self_cleaning_control_name_ID1, self_cleaning_image_name5[1]);
			}
		}
		j_self_cleaning_var = j;
		uart_only_sent_once_self_cleaning_var = uart_only_sent_once;
		grf_printf("self_cleaning_task_cb i j j_self_cleaning_var uart_only_sent_once_self_cleaning_var== %d %d %d %d\n",i,j,j_self_cleaning_var,uart_only_sent_once_self_cleaning_var);
	}
}


//按键操作
void key_task10_cb(){
	if (ytl_self_cleaning) {
		ytl_self_cleaning = GRF_FALSE;
		grf_printf("取消自清洁\n");
		grf_view_set_dis_view(GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID);  //取消自清洁跳转到请清理污水箱,避免异味
	}
}

void task_create10()
{
	grf_printf("task_create10\n");

	//获取控件
	self_cleaning_control_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW10_SELF_CLEANING_ID,VIEW10_SELF_CLEANING_IMAGE0_ID);
	self_cleaning_control_name_ID2 = grf_ctrl_get_form_id(GRF_VIEW10_SELF_CLEANING_ID,VIEW10_SELF_CLEANING_LABEL0_ID);

	first_display();

	//创建任务
	key_task10 = grf_task_create(key_task10_cb,100,NULL);
	self_cleaning_task = grf_task_create(self_cleaning_task_cb,100,NULL);

	//立即刷新页面
	grf_task_ready(self_cleaning_task);
}

void task_del10()
{
	grf_printf("task_del10\n");
	grf_task_del(key_task10);
	grf_task_del(self_cleaning_task);
}
