#ifndef __VIEW13_HELP1_H_
#define __VIEW13_HELP1_H_

typedef enum {
	VIEW13_HELP1_NULL,
	VIEW13_HELP1_IMAGE12_ID = 30,
	VIEW13_HELP1_CONTAINER10_ID = 38,
	VIEW13_HELP1_IMAGE14_ID = 36,
	VIEW13_HELP1_CONTAINER8_ID = 32,
	VIEW13_HELP1_IMAGE16_ID = 41,
	VIEW13_HELP1_CONTAINER6_ID = 21,
	VIEW13_HELP1_LABEL9_ID = 31,
	VIEW13_HELP1_LABEL5_ID = 19,
	VIEW13_HELP1_IMAGE7_ID = 20,
	VIEW13_HELP1_LABEL7_ID = 24,
	VIEW13_HELP1_IMAGE9_ID = 25,
	VIEW13_HELP1_CONTAINER1_ID = 4,
	VIEW13_HELP1_LABEL3_ID = 12,
	VIEW13_HELP1_CONTAINER3_ID = 10,
	VIEW13_HELP1_LABEL1_ID = 6,
	VIEW13_HELP1_IMAGE3_ID = 11,
	VIEW13_HELP1_LABEL13_ID = 43,
	VIEW13_HELP1_IMAGE5_ID = 15,
	VIEW13_HELP1_IMAGE1_ID = 5,
	VIEW13_HELP1_LABEL11_ID = 37,
	VIEW13_HELP1_IMAGE13_ID = 33,
	VIEW13_HELP1_CONTAINER9_ID = 35,
	VIEW13_HELP1_IMAGE11_ID = 28,
	VIEW13_HELP1_IMAGE15_ID = 39,
	VIEW13_HELP1_CONTAINER7_ID = 29,
	VIEW13_HELP1_IMAGE17_ID = 42,
	VIEW13_HELP1_CONTAINER5_ID = 17,
	VIEW13_HELP1_IMAGE8_ID = 22,
	VIEW13_HELP1_LABEL4_ID = 16,
	VIEW13_HELP1_LABEL6_ID = 23,
	VIEW13_HELP1_CONTAINER0_ID = 1,
	VIEW13_HELP1_LABEL2_ID = 9,
	VIEW13_HELP1_CONTAINER2_ID = 7,
	VIEW13_HELP1_LABEL0_ID = 3,
	VIEW13_HELP1_CONTAINER4_ID = 13,
	VIEW13_HELP1_LABEL14_ID = 44,
	VIEW13_HELP1_LABEL10_ID = 34,
	VIEW13_HELP1_IMAGE0_ID = 2,
	VIEW13_HELP1_IMAGE6_ID = 18,
	VIEW13_HELP1_IMAGE4_ID = 14,
	VIEW13_HELP1_IMAGE2_ID = 8,
	VIEW13_HELP1_LABEL12_ID = 40
} view13_help1_ctrls_id_e;

void view13_help1_init(void);
void view13_help1_entry(void);
void view13_help1_exit(void);
//.c文件里面自定义函数
void task_create13();
void task_del13();

#endif
