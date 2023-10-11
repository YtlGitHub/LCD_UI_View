#include "../grf_hw.h"
#include "../../apps.h"
#include "../libs/appscc/grf_prj_cc.h"
#if GRF_HW_ENABLE
#include "grf_hw_uart.h"


//自定义静态变量
static grf_bool isCmdCompleted = GRF_FALSE;  //控制命令是否正确,正确就执行下面串口的命令判断及发送


//自定义全局变量
u8 cmdBuf[EXTERNAL_BUFFER_SIZE];  //获得指定需要的数据
u8 isCmdCompletedBuf[EXTERNAL_BUFFER_SIZE];  //控制不让程序重复执行
u8 ytl_view_get_cur_id = GRF_VIEW02_CLEANING_ID;  //发生故障界面的视图ID


//view1
grf_bool ytl_Power = GRF_FALSE;   //电源键
grf_bool ytl_back = GRF_FALSE;  //返回键
grf_bool ytl_confirmation = GRF_FALSE;   //进入/确认键
grf_bool ytl_right = GRF_FALSE;   //右键
static u8 ytl_right_v = GRF_FALSE;   //快速点击右键,计算前后两次按键的间隔(连续接受串口太快,丢掉太快的串口)
grf_bool ytl_self_cleaning = GRF_FALSE;   //自清洁键
grf_bool ytl_mute = GRF_FALSE;   //静音键
grf_bool ytl_help = GRF_FALSE;   //帮助键

//view2
grf_bool ytl_erected = GRF_FALSE;  //是否竖起，GRF_FALSE竖起，GRF_TRUE倾斜
u8 ytl_dirty_degree = 0; //脏污程度，0蓝色、1轻度1、2轻度2、3重度1、4重度2

//view3
u8 ytl2_voice_image_val = 1;  //"语言音量2":音量图标0关1低2中3高

//view4电池电量和清水溶液显示全局变量
u8 ytl_battery_quantity_val = 0;  //电量信息值
grf_bool ytl1_cleaning_method = GRF_FALSE;  //"清洁方式1"：GRF_FALSE清水或GRF_TRUE溶液
grf_bool ytl_water_shortage_val = GRF_TRUE;  //GRF_FALSE缺水或GRF_TRUE水量正常

//view9
u8 ytl_mode_select_uart = 0;  //模式选择变量:0智能除菌1快速2超强

//view11
u8 ytl_fault[EXTERNAL_BUFFER_SIZE];  //0没有故障,1请安装清水箱,2请安装污水箱,3请清理滚刷,4请加清水,5请清理污水箱,6风机故障
u8 ytl_fault_val = 0;  //故障值变量

//view17
grf_bool ytl0_roller_brush_lighting = GRF_FALSE;  //"滚刷照明0"GRF_FALSE关GRF_TRUE开
u8 ytl3_switch_language = 0;  //"切换语言3":0简体中文1英文


#define HEAD_FH 0x5A
#define HEAD_FL 0xA5
#define SEQ 0x00
#define REG_LEN 0x800 //2048
static u16 ctrlreg[REG_LEN] = {0};


static u8 filePath[256];

//快速按选择键时,控制太快的按键失灵掉
void control_key_failure(void)
{
	ytl_right_v++;
	grf_printf("ytl_right_v == %d\n",ytl_right_v);
	if (ytl_right_v <= 3) {
		ytl_right = GRF_FALSE;
	}

	if (ytl_right_v > 3 && ytl_right) {
		ytl_right_v = 0;
	}
}

s32 read_data_para(u16 addr,u8* databuf,u32 len)
{
	const u8* cfgfile = filePath;
	grf_printf("read_data_para-cfgfile == %s\n",cfgfile);
	u32 reallen = 0;
	s8 ret = 0;

	FILE*   datafp=NULL;
	datafp = fopen(cfgfile,"rb");
	if(datafp==NULL)
	{
		grf_printf("open data.bin fail\n");
		fclose(datafp);
		return 0;
	}
	ret =fseek(datafp,addr,SEEK_SET);
	if(ret==0){//寻址成功
		reallen = fread(databuf,1,len,datafp);
	}
	else{
		grf_printf("The location exceeds the file size,addr=0x%04x\n",addr);
	}
	fclose(datafp);

	return reallen;
}

s32 write_data_para(u16 addr,u8* databuf,u32 len)
{
    s8 ret = 0;
	u32 reallen = 0;
	FILE*   datafp=NULL;
	const u8* cfgfile = filePath;

	datafp = fopen(cfgfile,"wb");
	// grf_printf("addr=%d,databuf=%x,len=%d\n",addr,databuf,len);
//	if(datafp == NULL){
//	//首先认为文件没有创建
//		datafp = fopen(cfgfile,"wb");
//	}
	if(datafp==NULL)
	{
		grf_printf("create tgus_para.bin fail\n");
		fclose(datafp);
		return GRF_FALSE;
	}
	else{
		grf_printf("create %s success!\n",filePath);
	}
	ret = fseek(datafp,addr,SEEK_SET);
	if(ret!=0){//如果写入的地址超过了文件的总大小,先用0扩大文件,然后再写入数据
		u32 endlen,offset;
		u8 *data_p=NULL;
		fseek(datafp,0,SEEK_END);
		endlen = ftell(datafp);
		offset = addr-endlen;
		data_p = malloc(offset);
		if(!data_p){
			grf_printf("data_p malloc fail\n");
		}
		else{
            memset(data_p,0, offset);
		    fwrite(data_p,1,offset,datafp);
		}
		free(data_p);
		//grf_printf("endlen=%d offset=%d \n",endlen,offset);
	}
	reallen = fwrite(databuf,1,len,datafp);
	fclose(datafp);
	return reallen;
}

//开机
void power_on(void)
{
	grf_printf("UART:语音播报开机\n");
	u8 readdatabuf[4] = {0,0,1,0};
	FILE *pFile=NULL;

    grf_printf("grf_dir_get_ddisk() == %s\n",grf_dir_get_ddisk());
    grf_printf("grf_dir_get_tfdisk() == %s\n",grf_dir_get_tfdisk());
    grf_printf("grf_dir_get_udisk() == %s\n",grf_dir_get_udisk());

    sprintf(filePath, "%s" "%s", grf_dir_get_ddisk(),"grf_app/res/Myfile.bin");
    grf_printf("filePath == %s\n",filePath);

    pFile = fopen(filePath , "rb"); //判断当前路径是否可以打开文件读操作
    if (pFile == NULL) {
    	sprintf(filePath, "%s" "%s", grf_dir_get_udisk(),"res/Myfile.bin");
    	grf_printf("pFile == NULL     filePath == %s\n",filePath);
	}
    fclose(pFile);

//    pFile = fopen(filePath , "rb"); //打开文件读操作
//    fread(read , 1 , sizeof(read) , pFile); //从文件中读数据
    read_data_para(0,readdatabuf,sizeof(readdatabuf));//读取bin保存的数据

    ytl0_roller_brush_lighting = readdatabuf[0];
	ytl1_cleaning_method = readdatabuf[1];
	ytl2_voice_image_val = readdatabuf[2];
	ytl3_switch_language = readdatabuf[3];

	grf_printf("滚刷照明：%d\n", ytl0_roller_brush_lighting);
	grf_printf("清洁方式：%d\n", ytl1_cleaning_method);
	grf_printf("语音音量：%d\n", ytl2_voice_image_val);
	grf_printf("切换语言：%d\n", ytl3_switch_language);

	//滚刷照明
	if (ytl0_roller_brush_lighting)
	{
		//发送串口数据
		grf_reg_com_send(0x05, 0xC0, 0x01, 0x01, 0);
	}
	else
	{
		//发送串口数据
		grf_reg_com_send(0x05, 0xC0, 0x01, 0x00, 0);
	}

	//切换语言
    if (ytl3_switch_language == 0) {
    	grf_lang_set("zh");
	}
    else if (ytl3_switch_language == 1) {
    	grf_lang_set("en");
	}
}

//保存系统设置变量
void save_system_settings_var(void)
{
	u8 writedatabuf[4] = {0};  //保存数据
	writedatabuf[0] = ytl0_roller_brush_lighting;
	writedatabuf[1] = ytl1_cleaning_method;
	writedatabuf[2] = ytl2_voice_image_val;
	writedatabuf[3] = ytl3_switch_language;

	grf_printf("滚刷照明：%d\n", writedatabuf[0]);
	grf_printf("清洁方式：%d\n", writedatabuf[1]);
	grf_printf("语音音量：%d\n", writedatabuf[2]);
	grf_printf("切换语言：%d\n", writedatabuf[3]);

//	const u8* cfgfile = filePath;
//  pFile = fopen(cfgfile , "wb");  //打开文件写操作
//  fwrite(writedatabuf , 1 , sizeof(writedatabuf) , pFile);  //把数据写到文件 myfile.bin
//  fclose(pFile);  //关闭文件
	write_data_para(0,writedatabuf,sizeof(writedatabuf));//写数据到bin
}

//void WR_test()
//{
//    u8 readdatabuf[12] = {0};
//    u8 writedatabuf[12] = {'h','e','l','l','o','g','i','r','a','f','f','e'};
//
//    sprintf(filePath, "%s" "%s", grf_dir_get_ddisk(),"grf_app/res/Myfile.bin");
//    grf_printf("filePath == %s\n",filePath);
//
//    write_data_para(0,&writedatabuf,12);//写数据到bin
//	read_data_para(0,&readdatabuf,12);//读取bin保存的数据
//    for(int i=0;i<12;i++)
//    {
//        grf_printf("databuf[%d]=0x%2x\n",i, readdatabuf[i]);
//    }
//}


//*********write reg**********
//TX - FL FH seq len cmd data0 data1
//     A5 5A 01  04  80
//RX - 无

//*********read reg**********
//TX -  FH FL len cmd addr reglen
//      5A A5 04  83  0001  02
//RX -  FH FL len cmd addr reglen data0 data1
//      5A A5 08  82  0001  02    FFFF  FFFF
s32 grf_reg_com_send(u8 len, u8 cmd, u8 date0, u8 date1, u8 date2)
{
	grf_printf("grf_reg_com_send:\nlen == %02x,\ncmd == %02x,\ndate0 == %02x,\ndate1 == %02x,\ndate2 == %02x\n", len, cmd, date0, date1, date2);
    u8 txdata[EXTERNAL_BUFFER_SIZE] = {0};
    u32 i=0,j=0,sum=0;;
    txdata[i++] = HEAD_FL;
    txdata[i++] = HEAD_FH;
    txdata[i++] = SEQ;
    txdata[i++] = len;
    txdata[i++] = cmd;
    txdata[i++] = date0;
    txdata[i++] = date1;
    txdata[i++] = date2;

	for (j = 0; j < len + 2; j++)
	{
		sum += txdata[j];
	}
	txdata[j] = sum % 256;  //校验和除以256求余
    grf_drv_uart_send(txdata,j+1);
}

#define UART_LASTBUFF 1
#if UART_LASTBUFF
#define RX_BUF_LEN   1024
static u8 RX_HAND_BUF[RX_BUF_LEN];
#endif


static void recive_data_handle(u8* databuf,u32 datalen)
{
	grf_printf("[static void recive_data_handle(u8* %02xdatabuf,u32 %ddatalen)])\n",databuf,datalen);
	for(int i=0;i<datalen;i++)
	{
		grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
	}

	if(datalen>=7)  //最短的指令为7个
	{
		//求校验和
		u8 crc = 0;
		for (int i = 0; i < datalen - 1; i++)
		{
			crc += databuf[i];
		}
		//校验和除256求余
		crc %= 256;
		printf("8bit:sum == %02x\n", crc);

		//帧头:0xA55A
		//seq;0x01
		//数据长度len;0x04
		//cmd:0x80
		//数据data;
		//校验和crc;
		if (0xA5 == databuf[0] &&
			0x5A == databuf[1] &&
			crc == databuf[datalen - 1])
		{
			grf_printf("==================kaishi=====================\n");
			cmdBuf[0] = databuf[4];
			cmdBuf[1] = databuf[5];
			cmdBuf[2] = databuf[6];
			cmdBuf[3] = databuf[7];

			isCmdCompleted = GRF_TRUE;

			for (u8 i = 0; i <= EXTERNAL_BUFFER_SIZE; ++i)
			{
				isCmdCompletedBuf[i] = GRF_TRUE;
				grf_printf("isCmdCompletedBuf[%d] = %d;\n",i,isCmdCompletedBuf[i]);
			}

			printf("++++++\n");
			for (int i = 0; i <= 4; ++i)
			{
				grf_printf("cmdBuf[%d] = %02x;\n",i,cmdBuf[i]);
			}
		}
		else
		{
			printf("ERROR! Invalid command\n");
		}
	}
	if (isCmdCompleted)
	{
		grf_printf("isCmdCompleted == %d\n",isCmdCompleted);
		ytl_Power = GRF_FALSE;   //电源键
		ytl_back = GRF_FALSE;  //返回键
		ytl_confirmation = GRF_FALSE;   //进入/确认键
		ytl_right = GRF_FALSE;   //右键即选择键
		ytl_self_cleaning = GRF_FALSE;   //自清洁键
		ytl_mute = GRF_FALSE;   //静音键
		ytl_help = GRF_FALSE;   //帮助键

		if (cmdBuf[0] == 0xE0 ||
			cmdBuf[0] == 0xB0 ||
			cmdBuf[0] == 0xF0 ||
			(cmdBuf[0] == 0x80 && cmdBuf[1] != 0x04))
		{
			grf_printf("如果是按得这几个键，就按实际的命令发送，否则就检查是否有故障，有故障就执行故障界面，没有就按实际的界面跳转\n");
		}
		else
		{
			for (u8 i = 1; i < 7; ++i)
			{
				if(ytl_fault[i])
				{
					cmdBuf[0] = 0xE0;
					cmdBuf[1] = i;
					break;
				}
			}
		}
		switch(cmdBuf[0])
		{
			case 0x80:
				if (cmdBuf[1] == 0x01)
				{
					if (cmdBuf[2] == 0x00)
					{
						grf_printf("UART:语音播报关机\n");
					}
					else if (cmdBuf[2] == 0x01)
					{
						//开机
					   printf("File :%s\n", __FILE__ );
					   printf("Date :%s\n", __DATE__ );
					   printf("Time :%s\n", __TIME__ );
					   printf("Line :%d\n", __LINE__ );
					   printf("ANSI :%d\n", __STDC__ );
					}
				}
				else if (cmdBuf[1] == 0x03)
				{
					grf_printf("UART:右键\n");
					ytl_right = GRF_TRUE;
					//grf_delay(800);
				}
				else if (cmdBuf[1] == 0x04)
				{
					grf_printf("UART:返回键\n");
					ytl_back = GRF_TRUE;
				}
				else if (cmdBuf[1] == 0x05)
				{
					grf_printf("UART:帮助键\n");
					ytl_help = GRF_TRUE;
				}
				else if (cmdBuf[1] == 0x06)
				{
					grf_printf("UART:确认键\n");
					ytl_confirmation = GRF_TRUE;
				}
				else if (cmdBuf[1] == 0x07)
				{
					grf_printf("UART:自清洁键\n");
					ytl_self_cleaning = GRF_TRUE;
				}
				else if (cmdBuf[1] == 0x08)
				{
					grf_printf("UART:静音键\n");
					ytl_mute = GRF_TRUE;
					if (cmdBuf[2] == 0x01)
					{
						key_task17_cb();  //语音音量
					}
					else if(cmdBuf[2] == 0x03)
					{
						if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
							ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
							ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID)
						{
							grf_view_set_dis_view(GRF_VIEW19_RESTORE_FACTORY_SETTINGS_ID);  //恢复出厂设置
						}
					}
				}
				//进入工程测试模式
				else if (cmdBuf[1] == 0x09)
				{
					grf_printf("UART:工程测试模式\n");
					//设置只能在清扫界面,发送工程测试模式指令才可以进入工程测试模式
					if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID) {
						grf_view_set_dis_view(GRF_VIEW18_ENGINEERING_TEST_MODE_ID);
					}
				}
				break;
			case 0x81:  //语言选择
				if (cmdBuf[1] == 0x00)
				{
					grf_printf("UART:英文模式\n");
					grf_lang_set("en");
				}
				else if (cmdBuf[1] == 0x01) {
					grf_printf("UART:中文模式\n");
					grf_lang_set("zh");
				}
				break;
			case 0xB0:
				if (cmdBuf[1] == 0x01)
				{
					grf_printf("UART:充电模式\n");
					if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
						ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
						ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID ||
						ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID ||
						ytl_view_get_cur_id == GRF_VIEW18_ENGINEERING_TEST_MODE_ID ||
						ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID)
					{
						grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
					}
				}
				else if (cmdBuf[1] == 0x02)
				{
					grf_printf("UART:脱离充电\n");
					if (ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID) {
						grf_view_set_dis_view(GRF_VIEW02_CLEANING_ID);
					}
				}
				else if (cmdBuf[1] == 0x03)
				{
					if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID) {
						grf_printf("UART:竖起停止工作\n");
						ytl_erected = GRF_FALSE;
					}
				}
				else if (cmdBuf[1] == 0x04)
				{
					if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID) {
						grf_printf("UART:倾斜开始工作\n");
						ytl_erected = GRF_TRUE;
					}

				}
				//发送串口数据
				grf_reg_com_send(0x05, cmdBuf[0], cmdBuf[1], 0x00, 0x00);
				break;
			case 0x9A:
				if (cmdBuf[1] == 0x01)
				{
					if (cmdBuf[2] == 0x00)
					{
						grf_printf("UART:脏污程度(蓝色)\n");
						ytl_dirty_degree = 0;
					}
					else if (cmdBuf[2] == 0x01)
					{
						grf_printf("UART:脏污程度(轻度1)\n");
						ytl_dirty_degree = 1;
					}
					else if (cmdBuf[2] == 0x02)
					{
						grf_printf("UART:脏污程度(轻度2)\n");
						ytl_dirty_degree = 2;
					}
					else if (cmdBuf[2] == 0x03)
					{
						grf_printf("UART:脏污程度(重度1)\n");
						ytl_dirty_degree = 3;
					}
					else if (cmdBuf[2] == 0x04)
					{
						grf_printf("UART:脏污程度(重度2)\n");
						ytl_dirty_degree = 4;
					}
				}
				grf_reg_com_send(0x06, cmdBuf[0], cmdBuf[1], cmdBuf[2], 0x00);
				break;
			case 0xE0:
				if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID && ytl_view_get_cur_id != GRF_VIEW19_RESTORE_FACTORY_SETTINGS_ID) {
					if (cmdBuf[1] == 0x00)
					{
						ytl_fault[cmdBuf[2]] = GRF_FALSE;
						//故障修复指令:屏 -> Host

						grf_reg_com_send(0x06, cmdBuf[0], cmdBuf[1], cmdBuf[2], 0x00);
						for (u8 i = 1; i < 7; ++i)
						{
							if(ytl_fault[i])
							{
								ytl_fault_val = i;
								break;
							}
						}
					}
					else if(cmdBuf[1] >= 0x01 && cmdBuf[1] <= 0x06)
					{
						ytl_fault[cmdBuf[1]] = GRF_TRUE;
						ytl_fault[11] = GRF_FALSE;
						ytl_fault[12] = GRF_FALSE;
						ytl_fault[13] = GRF_FALSE;
						ytl_fault[14] = GRF_FALSE;
						ytl_fault[15] = GRF_FALSE;
						ytl_fault[16] = GRF_FALSE;
						ytl_fault_val = cmdBuf[1];

						//如果在自清洁请清理污水箱避免异味界面,发送故障就直接跳转到充电界面
						if (ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID)
						{
							grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
						}
						//如果不在充电界面就可以跳转到故障界面,否则在充电界面就不跳转故障界面,
						else if (ytl_view_get_cur_id != GRF_VIEW08_CHARGING_ID)
						{
							grf_view_set_dis_view(GRF_VIEW11_FAULT_ID);
						}
					}
					else
					{
						grf_printf("故障指令有误:cmdBuf[1] == %2x\n",cmdBuf[1]);
					}
				}
				break;
			case 0xF0:
				if (cmdBuf[1] == 0x01)
				{
					if (cmdBuf[2] >= 0 && cmdBuf[2] <= 100)
					{
						ytl_battery_quantity_val = cmdBuf[2];
					}
					else {
					}
				}
				if (cmdBuf[1] == 0x02)
				{
					if (cmdBuf[2] == 0x00)
					{
						ytl_water_shortage_val = GRF_FALSE;
					}
					else if(cmdBuf[2] == 0x01)
					{
						ytl_water_shortage_val = GRF_TRUE;
					}
				}
				grf_reg_com_send(0x06, cmdBuf[0], cmdBuf[1], cmdBuf[2], 0x00);
				break;
			isCmdCompleted = GRF_FALSE;
		}
	}
}


void grf_uart_init(void)
{
    grf_uart_cfg_t cfg_t = {0};
    cfg_t.port = 11;
    cfg_t.speed_e = UART_SPEED_115200;
    cfg_t.bit_e = UART_BIT_8;
    cfg_t.parity_e = UART_PARITY_NONE;
    cfg_t.stop_e = UART_STOP_1;
    s32 ret = grf_drv_uart_open(cfg_t);
    if(ret == GRF_OK)
    {
    	grf_printf("[ret == GRF_OK])\n");
        grf_drv_uart_rev_set_bfun(recive_data_handle,1024);
    }
}


#endif



