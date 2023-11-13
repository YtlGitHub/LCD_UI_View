#include "../grf_hw.h"
#include "../../apps.h"
#include "../libs/appscc/grf_prj_cc.h"
#if GRF_HW_ENABLE
#include "grf_hw_uart.h"


//自定义静态变量
static grf_bool isCmdCompleted = GRF_FALSE;  //控制命令是否正确,正确就执行下面串口的命令判断及发送
static grf_bool get_battery_quantity = GRF_FALSE;  //开机检查是否收到电量值
static grf_bool get_main_view  = GRF_FALSE;  //开机检查是否收到进入主界面指令
static grf_bool get_charging_view = GRF_FALSE;  //开机检查是否收到进入充电界面指令


//自定义全局变量
u8 cmdBuf[EXTERNAL_BUFFER_SIZE];  //获得指定需要的数据
u8 isCmdCompletedBuf[EXTERNAL_BUFFER_SIZE];  //控制不让程序重复执行
u8 ytl_view_get_cur_id = GRF_VIEW02_CLEANING_ID;  //发生故障界面的视图ID
u8 ytl_volume = 70;  //音量大小

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
u8 ytl2_voice_image_val = 2;  //"语言音量2":音量图标0关1低2中3高

//view4电池电量和清水溶液显示全局变量
u8 ytl_battery_quantity_val = 101;  //电量信息值
grf_bool ytl1_cleaning_method = GRF_FALSE;  //"清洁方式1"：GRF_FALSE清水或GRF_TRUE溶液
grf_bool ytl_water_shortage_val = GRF_TRUE;  //GRF_FALSE缺水或GRF_TRUE水量正常

//view9
u8 ytl_mode_select_uart = 0;  //模式选择变量:0智能除菌1快速2超强

//view11
u8 ytl_fault[EXTERNAL_BUFFER_SIZE];  //0没有故障,1请安装清水箱,2请安装污水箱,3请清理滚刷,4请加清水,5请清理污水箱,6风机故障
u8 ytl_fault_val = 0;  //故障值变量

//view17
grf_bool ytl0_roller_brush_lighting = GRF_TRUE;  //"滚刷照明0"GRF_FALSE关GRF_TRUE开
u8 ytl3_switch_language = 0;  //"切换语言3":0简体中文(zh)1英文(en)2土耳其(Turkish)。。。


//切换语言音频
void switch_language_pack(char filename[])
{
	char sound_array[255];
	if (ytl3_switch_language == 0)
	{
		sprintf(sound_array,"/rodata/sound/zh/%s_zh.wav", filename);
		grf_printf("%s\n",sound_array);
	}
	else if (ytl3_switch_language == 1)
	{
		sprintf(sound_array,"/rodata/sound/en/%s_en.wav", filename);
		grf_printf("%s\n",sound_array);
	}
	//语音播报
	tr660r_wavplay(sound_array,ytl_volume);
}
//按键音
void key_sound_tr660r_wavplay(char filename[])
{
	char sound_array[255];
	sprintf(sound_array,"/rodata/sound/%s.wav", filename);
	grf_printf("%s\n",sound_array);
	tr660r_wavplay(sound_array,ytl_volume);  //按键音
}


#define HEAD_FH 0xA5
#define HEAD_FL 0x5A
#define SEQ 0x00
#define REG_LEN 0x800 //2048
static u16 ctrlreg[REG_LEN] = {0};


static u8 filePath[256];
static u8 filePath_sound[256];


//void tr660r_wavplay(char filename[],int volume){}


//快速按选择键时,控制太快的按键失灵掉
void control_key_failure(void)
{
	if (ytl_right_v <= 2) {
		ytl_right_v++;
		ytl_right = GRF_FALSE;
		grf_printf("ytl_right_v == %d\n",ytl_right_v);
	}
	else if (ytl_right_v > 2 && ytl_right) {
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
void volume_size(void)  //音量大小
{
    if (ytl2_voice_image_val == 0) {
		ytl_volume = 0;
	}
    else if (ytl2_voice_image_val == 1) {
    	ytl_volume = 60;
	}
    else if (ytl2_voice_image_val == 2) {
    	ytl_volume = 70;
	}
    else if (ytl2_voice_image_val == 3) {
    	ytl_volume = 80;
	}
}
//开机
void power_on(void)
{
	grf_reg_com_send(0x04, 0x90, 0x02, 0, 0);  //获取电量
	u8 readdatabuf[4] = {1,0,2,0};  //下标为：0滚刷照明，1清洁方式，2语言音量，3切换语言
	FILE *pFile=NULL;

//    grf_printf("grf_dir_get_ddisk() == %s\n",grf_dir_get_ddisk());
//    grf_printf("grf_dir_get_tfdisk() == %s\n",grf_dir_get_tfdisk());
//    grf_printf("grf_dir_get_udisk() == %s\n",grf_dir_get_udisk());

    sprintf(filePath, "%s" "%s", grf_dir_get_ddisk(),"Myfile.bin");
    //grf_printf("filePath == %s\n",filePath);

    /*
    pFile = fopen(filePath , "rb"); //判断当前路径是否可以打开文件读操作
    if (pFile == NULL) {
    	sprintf(filePath, "%s" "%s", grf_dir_get_udisk(),"res/Myfile.bin");
    	//grf_printf("pFile == NULL     filePath == %s\n",filePath);
	}
    fclose(pFile);
    */

//    pFile = fopen(filePath , "rb"); //打开文件读操作
//    fread(read , 1 , sizeof(read) , pFile); //从文件中读数据
    read_data_para(0,readdatabuf,sizeof(readdatabuf));//读取bin保存的数据

    ytl0_roller_brush_lighting = readdatabuf[0];
	ytl1_cleaning_method = readdatabuf[1];
	ytl2_voice_image_val = readdatabuf[2];
	ytl3_switch_language = readdatabuf[3];

	/*
	grf_printf("滚刷照明：%d\n", ytl0_roller_brush_lighting);
	grf_printf("清洁方式：%d\n", ytl1_cleaning_method);
	grf_printf("语音音量：%d\n", ytl2_voice_image_val);
	grf_printf("切换语言：%d\n", ytl3_switch_language);
	*/

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
    volume_size();  //音量大小
    grf_printf("ytl_volume == %d",ytl_volume);

    key_sound_tr660r_wavplay("dingdong");  //开机音效
    grf_delay(1150);  //等待叮咚音效播报完
	//语音播报"正在开机中"
    switch_language_pack("00_01StartingUp");
}

//保存系统设置变量
void save_system_settings_var(void)
{
	u8 writedatabuf[4] = {0};  //保存数据  //下标为：0滚刷照明，1清洁方式，2语言音量，3切换语言
	writedatabuf[0] = ytl0_roller_brush_lighting;
	writedatabuf[1] = ytl1_cleaning_method;
	writedatabuf[2] = ytl2_voice_image_val;
	writedatabuf[3] = ytl3_switch_language;

//	grf_printf("滚刷照明：%d\n", writedatabuf[0]);
//	grf_printf("清洁方式：%d\n", writedatabuf[1]);
//	grf_printf("语音音量：%d\n", writedatabuf[2]);
//	grf_printf("切换语言：%d\n", writedatabuf[3]);

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

//*********YuKe**********
//      FH FL seq len cmd data1 data2 crc
//      A5 5A 01  05  F0    01   14  0A
s32 grf_reg_com_send(u8 len, u8 cmd, u8 date0, u8 date1, u8 date2)
{
	//grf_printf("grf_reg_com_send:\nlen == %02x,\ncmd == %02x,\ndate0 == %02x,\ndate1 == %02x,\ndate2 == %02x\n", len, cmd, date0, date1, date2);
    u8 txdata[EXTERNAL_BUFFER_SIZE] = {0};
    u32 i=0,j=0,sum=0;;
    txdata[i++] = HEAD_FH;
    txdata[i++] = HEAD_FL;
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

    for (u8 i = 0; i < len+3; ++i) {
    	 grf_printf("txdata[%d] == 0x%02x\n",i,txdata[i]);
	}
    grf_printf("j == %d\n",j);
    grf_drv_uart_send(txdata,j+1);
}

//s32 grf_reg_com_send(u16 addr,u16 len)
//{
//    u8 txdata[257] = {0};
//    u32 i=0,j=0;
//    txdata[i++] = HEAD_FH;
//    txdata[i++] = HEAD_FL;
//    txdata[i++] = 0;
//    txdata[i++] = addr>>8;
//    txdata[i++] = (addr&0x00ff);
//    txdata[i++] = len;
//    for(j=0;j<len;j++){
//        txdata[i++] = (ctrlreg[addr+j]>>8);
//        txdata[i++] = (ctrlreg[addr+j]&0x00ff);
//    }
//    grf_drv_uart_send(txdata,i);
//}

#define UART_LASTBUFF 1
#if UART_LASTBUFF
#define RX_BUF_LEN   1024
static u8 RX_HAND_BUF[RX_BUF_LEN];
#endif


static void USARTy_IRQHandler(u16* databuf,u32 datalen)
{
	if(datalen>=7)  //最短的指令为7个
	{
		grf_printf("datalen 111111111111111111111111111111 %d\n",datalen);
		for(u8 i=0;i<datalen;i++)
		{
			grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
		}
		//求校验和
		u8 crc = 0;
		for (u8 i = 0; i < datalen - 1; i++)
		{
			crc += databuf[i];
		}
		//校验和除256求余
		crc %= 256;
		grf_printf("8bit:sum == %02x\n", crc);

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
			isCmdCompleted = GRF_TRUE;

			grf_printf("datalen 222222222222222222222222222222222 %d\n",datalen);

			for(u8 i=0;i<datalen;i++)
			{
				grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
			}

			cmdBuf[0] = databuf[4];
			cmdBuf[1] = databuf[5];
			cmdBuf[2] = databuf[6];
			cmdBuf[3] = databuf[7];
			for (int i = 0; i <= 4; ++i)
			{
				//grf_printf("cmdBuf[%d] = %02x;\n",i,cmdBuf[i]);
			}

			for (u8 i = 0; i <= EXTERNAL_BUFFER_SIZE; ++i)
			{
				isCmdCompletedBuf[i] = GRF_TRUE;
				//grf_printf("isCmdCompletedBuf[%d] = %d;\n",i,isCmdCompletedBuf[i]);
			}

			grf_printf("++++++\n");

		}
		else
		{
			grf_printf("ERROR! Invalid command\n");
		}
	}
	grf_printf("isCmdCompleted == %d\n",isCmdCompleted);
	if (isCmdCompleted)
	{
		isCmdCompleted = GRF_FALSE;
		if (cmdBuf[0] == 0xE0 ||
			cmdBuf[0] == 0xB0 ||
			cmdBuf[0] == 0xF0 ||
			(cmdBuf[0] == 0x80 && cmdBuf[1] != 0x04))
		{
			//grf_printf("如果是按得这几个键，就按实际的命令发送，否则就检查是否有故障，有故障就执行故障界面，没有就按实际的界面跳转\n");
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
				ytl_Power = GRF_FALSE;   //电源键
				ytl_back = GRF_FALSE;  //返回键
				ytl_confirmation = GRF_FALSE;   //进入/确认键
				ytl_right = GRF_FALSE;   //右键即选择键
				ytl_self_cleaning = GRF_FALSE;   //自清洁键
				ytl_mute = GRF_FALSE;   //静音键
				ytl_help = GRF_FALSE;   //帮助键
				if (cmdBuf[1] != 0x01 && cmdBuf[1] != 0x09)
				{
					key_sound_tr660r_wavplay("dongPart002");  //按键音效
				}
				if (cmdBuf[1] == 0x01)
				{
					if (cmdBuf[2] == 0x00)
					{
						switch_language_pack("00_02");  //已关机,请放回底座自清洁
					}
					else if (cmdBuf[2] == 0x01)
					{
						//开机
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
					//如果是脱离充电状态,按自清洁键,就语音播报:"请放回底座自清洁"
					if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
							ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
							ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID)
					{
						//语音播报:"请放回底座自清洁"
						switch_language_pack("08_02_self_cleaning_key");
					}
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
						//语音播报:"已进入工程测试模式。"
						switch_language_pack("18_00_engineering_mode");
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
					grf_printf("UART1:B0-0x01\n");
					get_charging_view = GRF_TRUE;
					get_main_view = GRF_FALSE;
					if (get_battery_quantity) {
						grf_printf("UART2:B0-0x01\n");
						if (ytl_view_get_cur_id == GRF_VIEW02_CLEANING_ID ||
							ytl_view_get_cur_id == GRF_VIEW05_STERILIZATION_FLUID_PREPARATION_ID ||
							ytl_view_get_cur_id == GRF_VIEW07_WATER_SUCTION_ID ||
							//ytl_view_get_cur_id == GRF_VIEW10_01_PLEASE_CLEAN_THE_DIRTY_WATER_TANK_ID ||
							ytl_view_get_cur_id == GRF_VIEW18_ENGINEERING_TEST_MODE_ID ||
							ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID)
						{
							grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
						}
					}
				}
				else if (cmdBuf[1] == 0x02)
				{
					grf_printf("UART1:B0-0x02\n");
					get_main_view = GRF_TRUE;
					get_charging_view = GRF_FALSE;
					if (get_battery_quantity) {
						grf_printf("UART2:B0-0x02\n");
						if (ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID) {
							grf_view_set_dis_view(GRF_VIEW02_CLEANING_ID);
						}
					}
				}
				else if (cmdBuf[1] == 0x03)
				{
					grf_printf("UART:B0-0x03\n");
					if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID) {
						grf_printf("UART:B0-0x03(竖起停止工作)\n");
						ytl_erected = GRF_FALSE;
					}
				}
				else if (cmdBuf[1] == 0x04)
				{
					grf_printf("UART:B0-0x04\n");
					if (ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID) {
						grf_printf("UART:B0-0x04(倾斜开始工作)\n");
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
						//获取电量
						ytl_battery_quantity_val = cmdBuf[2];
						get_battery_quantity = GRF_TRUE;
						grf_printf("ytl_battery_quantity_val ==================================== %d\n",ytl_battery_quantity_val);
						//语音播报
						if (ytl_view_get_cur_id != GRF_VIEW08_CHARGING_ID && ytl_view_get_cur_id != GRF_VIEW20_LOGO_ID)
						{
							if (ytl_battery_quantity_val == 20) {
								switch_language_pack("04_01_20%");  //电池电量不足
							}
							else if (ytl_battery_quantity_val == 10) {
								switch_language_pack("04_02_10%");  //电量过低请充电
							}
						}
						//判断进入智能除菌还是充电界面
						if (ytl_view_get_cur_id == GRF_VIEW20_LOGO_ID)
						{
							if (get_main_view)
							{
								get_main_view = GRF_FALSE;
								grf_view_set_dis_view(GRF_VIEW02_CLEANING_ID);
							}
							else if (get_charging_view)
							{
								get_charging_view = GRF_FALSE;
								grf_view_set_dis_view(GRF_VIEW08_CHARGING_ID);
							}
						}
					}
					else {
					}
				}
				if (cmdBuf[1] == 0x02)
				{
					if (cmdBuf[2] == 0x00)
					{
						ytl_water_shortage_val = GRF_FALSE;
						//语音播报:清水箱缺水,请加水。
						switch_language_pack("04_03_WaterShortage");
					}
					else if(cmdBuf[2] == 0x01)
					{
						ytl_water_shortage_val = GRF_TRUE;
					}
				}
				grf_reg_com_send(0x06, cmdBuf[0], cmdBuf[1], cmdBuf[2], 0x00);
				break;
		}
	}
}


void grf_reg_set_user(u16 addr,u16* data,u32 datalen)
{
    //user code
	grf_printf("test\n");
	grf_printf("addr == 0x%04x\n",addr);
	grf_printf("datalen == %d\n",datalen);
	for(u8 i=0;i<8;i++){
		grf_printf("data[%d]=0x%02x\n",i,data[i]);
	}
	USARTy_IRQHandler(data,datalen);
}

static s32 grf_reg_s_set(u16 addr,u8* data,u8 len)
{
    if(addr>REG_LEN){
        return GRF_FAIL;
    }
    u8 i=0;
    for(i=0;i<len;i++){
        //ctrlreg[addr+i] = (data[i*2]<<8)+data[1+i*2];
    	ctrlreg[addr+i] = data[i];
        grf_printf("ctrlreg[%d] = %02X\n",addr+i,ctrlreg[addr+i]);
    }
    grf_reg_set_user(addr,ctrlreg+addr,len);
    return GRF_OK;
}


static s32 grf_comm_handle(u8* data)
{
	for(u8 i=0;i<data[3]+3;i++){
		grf_printf("data[%d]=0x%02x\n",i,data[i]);
	}

//	u8 cmd = data[3];
//	u8 len = data[2];
	u8 len = data[3]+3;
    //u16 addr = (data[4]<<8)+data[5];
	u16 addr = (data[2]);
    u32 i=0;
    grf_printf("addr == 0x%04x\n",addr);
    grf_printf("len == %d\n",len);
    if(addr>REG_LEN){
        return GRF_FAIL;
    }
    /*
    switch (cmd)
    {
        case 0x82: //写寄存器
        {
            u32 regcount = (len-3)>>1;
            grf_printf("regcount == %d\n",regcount);
            grf_reg_s_set(addr,data,regcount);
        }
        break;
        case 0x83: //读寄存器
        	grf_reg_com_send(addr,data[6]);
        break;
    }
    */

    u32 regcount = len;
    grf_printf("regcount == %d\n",regcount);
    grf_reg_s_set(addr,data,regcount);
    return GRF_OK;
}


static void recive_data_handle(u8* databuf,u32 datalen)
{
	u16 i=0;
	static u16 last_data_num=0;
#if UART_LASTBUFF
	if(last_data_num + datalen > RX_BUF_LEN){
		datalen = datalen-last_data_num;
	}
	if(last_data_num){
		memcpy(RX_HAND_BUF+last_data_num,databuf,datalen);
		databuf=RX_HAND_BUF;
		datalen+=last_data_num;
		last_data_num = 0;
	}
#endif

#if 0
	grf_printf("datalen == %d #ifaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n",datalen);
	for(i=0;i<datalen;i++){
		grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
	}
#endif
	grf_printf("datalen == %d #endif1aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n",datalen);
//	for(u8 i=0;i<datalen;i++){
//		grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
//	}
	//把多余的长度去掉,不然会导致一直在发送多余的指令,导致显示卡顿
	if (datalen > (databuf[3]+3)<<1)
	{
		datalen = (databuf[3]+3)<<1;
		grf_printf("datalen == %d #endif2aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n",datalen);
//		for(u8 i=0;i<datalen;i++){
//			grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
//		}
	}
	else {
		for(u8 i=0;i<datalen;i++){
			grf_printf("databuf[%d]=0x%02x\n",i,databuf[i]);
		}
	}
	if(datalen>=7){//最短的指令为7个
		for(i=0;i<=datalen-7;i++)
        {
			if((databuf[i]==HEAD_FH) && (databuf[i+1]==HEAD_FL))
			{
    			if(databuf[i+3] <= (datalen-i-3)){
                    if(grf_comm_handle(databuf+i)==GRF_OK){
                        i += (databuf[i+3])+2;
                    }
    			}
		        else{
                    last_data_num = datalen-i;
                    break;
		        }
			}
		}
	}
	else{
		last_data_num = datalen;
	}

#if UART_LASTBUFF
	if(last_data_num<=256 && last_data_num!=0)
	{
		u8  last_data_buf[256] = {0};
		memcpy(last_data_buf,databuf+i,last_data_num);
		memcpy(RX_HAND_BUF,last_data_buf,last_data_num);
	}else{
		last_data_num=0;
	}
#else
	last_data_num = 0;
#endif


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
        grf_drv_uart_rev_set_bfun(recive_data_handle,1024);
    }
}


#endif



