#include "../../apps.h"


//创建任务名
grf_task_t *engineering_test_mode_task18 = NULL;  //工程测试模式任务


//创建控件名
grf_ctrl_t *engineering_test_mode_label0_name_ID1 = NULL;  //创建工程测试模式下方白色色字体说明文字控件名
grf_ctrl_t *engineering_test_mode_label1_pass_fail_name_ID2 = NULL;  //创建工程测试模式中间“测试中”、“PASS”或“FAIL”显示控件名
grf_ctrl_t *engineering_test_mode_label2_key_name_ID3 = NULL;  //创建按键显示文字控件名


//自定义变量
static u8 i = 0;  //控制工程测试模式循环变量


//自定义数组
static u8 *key_display_name_array[9] =
{
	"",
	"开关键",
	"左键",
	"选择键",
	"返回键",
	"帮助键",
	"确认键",
	"自清洁键",
	"功能键",
};


//控制显示时间
static void control_display_time(void)
{
	i++;
	grf_printf("i == %d",i);
	if (i >= 1 && i < 10)
	{
		grf_ctrl_set_hidden(engineering_test_mode_label2_key_name_ID3, GRF_FALSE);
	}
	else if (i == 10)
	{
		grf_ctrl_set_hidden(engineering_test_mode_label2_key_name_ID3, GRF_TRUE);
		i = 0;
		isCmdCompletedBuf[19] = GRF_FALSE;
	}
}


//按键显示自定义调用函数
static void key_display_test(u8 data1,u8 data2)
{
	control_display_time();
	if (data1 == 0x08)
	{
		if (data2 == 0x00 || data2 == 0x01) {
			grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"静音键");
			grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
		}
		else if (data2 == 0x03) {
			grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"恢复出厂设置");
			grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
		}
	}
	else {
		grf_label_set_txt(engineering_test_mode_label2_key_name_ID3, key_display_name_array[data1]);
		grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_BLUE);
	}
}


//工程测试模式任务
void engineering_test_mode_task18_cb()
{
	//grf_printf("cmdBuf[0] == %02x,cmdBuf[1] == %02x\n",cmdBuf[0],cmdBuf[1]);
	if (isCmdCompletedBuf[19])
	{
		grf_printf("cmdBuf[0] == %02x,cmdBuf[1] == %02x,cmdBuf[2] == %02x\n",cmdBuf[0],cmdBuf[1],cmdBuf[2]);
		if (cmdBuf[0] == 0xD0)
		{
			switch (cmdBuf[1])
			{
				case 0xf0:
					grf_printf("FAIL\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "FAIL");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_RED);
					break;
				case 0xf1:
					grf_printf("PASS\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "PASS");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_GREEN);
					break;
				case 0x00:
					grf_printf("按键测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "按键测试");
					break;
				case 0x01:
					grf_printf("风机测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "风机测试");
					break;
				case 0x02:
					grf_printf("电解水测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "电解水测试");
					break;
				case 0x03:
					grf_printf("清水箱污水箱在位测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "清水箱污水箱在位测试");
					break;
				case 0x04:
					grf_printf("清水箱有水无水测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "清水箱有水无水测试");
					break;
				case 0x05:
					grf_printf("污浊度测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "污浊度测试");
					break;
				case 0x06:
					grf_printf("污水箱满测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "污水箱满测试");
					break;
				case 0x07:
					grf_printf("机器倾斜开关测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "机器倾斜开关测试");
					break;
				case 0x08:
					grf_printf("滚刷测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "滚刷测试");
					break;
				case 0x09:
					grf_printf("水泵测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "水泵测试");
					break;
				case 0x10:
					grf_printf("左右轮测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "左右轮测试");
					break;
				case 0x11:
					grf_printf("LED灯照明测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "LED灯照明测试");
					break;
				case 0x12:
					grf_printf("洗地机老化测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "洗地机老化测试");
					break;
				case 0x13:
					grf_printf("洗地机充电测试\n");
					grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "请放回底座查看充电是否正常");
					grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
					grf_label_set_txt(engineering_test_mode_label0_name_ID1, "洗地机充电测试");
					break;
			}
			isCmdCompletedBuf[19] = GRF_FALSE;
		}
		else if(cmdBuf[0] == 0x80)
		{
			if (cmdBuf[1] == 0x09)
			{
				grf_delay(1000);
				grf_ctrl_set_hidden(engineering_test_mode_label0_name_ID1, GRF_FALSE);
				grf_printf("按键测试\n");
				grf_label_set_txt(engineering_test_mode_label1_pass_fail_name_ID2, "测试中");
				grf_label_set_txt_color(engineering_test_mode_label1_pass_fail_name_ID2,GRF_COLOR_YELLOW);
				grf_label_set_txt(engineering_test_mode_label0_name_ID1, "按键测试");
				isCmdCompletedBuf[19] = GRF_FALSE;
			}
			else {
				grf_printf("按键显示测试\n");
				key_display_test(cmdBuf[1],cmdBuf[2]);
			}
		}
		else if(cmdBuf[0] == 0xF0)
		{
			control_display_time();
			if (cmdBuf[1] == 0x01)  //发送电量显示
			{
				u8 battery_quantity[10];
				sprintf(battery_quantity, "%d" "%s",ytl_battery_quantity_val, "%");
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,battery_quantity);
			}
			if (cmdBuf[1] == 0x02)  //是否缺水
			{
				if (cmdBuf[2] == 0x00)  //缺水
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"缺水");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x01)  //不缺水
				{
					grf_printf("不缺水\n");
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"水量正常");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
			}
		}
		else if(cmdBuf[0] == 0xB0)
		{
			control_display_time();
			if (cmdBuf[1] == 0x01)  //充电界面
			{
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"充电界面");
				grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
			}
			if (cmdBuf[1] == 0x02)  //脱离充电
			{
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"脱离充电");
				grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
			}
			if (cmdBuf[1] == 0x03)  //竖起机身停止清扫
			{
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"竖起机身停止清扫");
				grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
			}
			if (cmdBuf[1] == 0x04)  //倾斜机身开始清扫
			{
				grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"倾斜机身开始清扫");
				grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
			}
		}
		else if(cmdBuf[0] == 0x9A)  //脏污程度
		{
			if (cmdBuf[1] == 0x01)  //充电界面
			{
				control_display_time();
				if (cmdBuf[2] == 0x00)  //脏污程度(蓝色)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"脏污程度(蓝色)");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x01)  //脏污程度(轻度1)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"脏污程度(轻度1)");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x02)  //脏污程度(轻度2)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"脏污程度(轻度2)");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x03)  //脏污程度(重度1)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"脏污程度(重度1)");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
				if (cmdBuf[2] == 0x04)  //脏污程度(重度2)
				{
					grf_label_set_txt(engineering_test_mode_label2_key_name_ID3,"脏污程度(重度2)");
					grf_label_set_txt_color(engineering_test_mode_label2_key_name_ID3,GRF_COLOR_ORANGE);
				}
			}
		}
	}
}


void task_create18()
{
	grf_printf("task_create18\n");

	//获取控件
	engineering_test_mode_label0_name_ID1 = grf_ctrl_get_form_id(GRF_VIEW18_ENGINEERING_TEST_MODE_ID, VIEW18_ENGINEERING_TEST_MODE_LABEL0_ID);
	engineering_test_mode_label1_pass_fail_name_ID2 = grf_ctrl_get_form_id(GRF_VIEW18_ENGINEERING_TEST_MODE_ID, VIEW18_ENGINEERING_TEST_MODE_LABEL1_ID);
	engineering_test_mode_label2_key_name_ID3 = grf_ctrl_get_form_id(GRF_VIEW18_ENGINEERING_TEST_MODE_ID, VIEW18_ENGINEERING_TEST_MODE_LABEL2_ID);

	//创建任务
	engineering_test_mode_task18 = grf_task_create(engineering_test_mode_task18_cb,100,NULL);  //创建工程测试模式任务

	//立即执行
	//grf_task_ready(engineering_test_mode_task18);
}


void task_del18(void)
{
	grf_printf("task_del18\n");
	grf_task_del(engineering_test_mode_task18);
}
