#ifndef __VIEW01_H_
#define __VIEW01_H_

typedef enum {
	VIEW01_NULL,
	VIEW01_CONTAINER0_ID = 2,
	VIEW01_LABEL4_ID = 7,
	VIEW01_LABEL0_ID = 1,
	VIEW01_LABEL3_ID = 5,
	VIEW01_IMAGE0_ID = 3,
	VIEW01_IMAGE2_ID = 4,
	VIEW01_IMAGE1_ID = 6,
	VIEW01_IMAGE3_ID = 8,
	VIEW01_IMAGE4_ID = 9
} view01_ctrls_id_e;


void view01_init(void);
void view01_entry(void);
void view01_exit(void);
//.c文件里面自定义函数
void task_create01();
void task_del01();

#endif
