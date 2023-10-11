#ifndef __VIEW12_HELP_H_
#define __VIEW12_HELP_H_

typedef enum {
	VIEW12_HELP_NULL,
	VIEW12_HELP_IMAGE1_ID = 2,
	VIEW12_HELP_LABEL0_ID = 3,
	VIEW12_HELP_LABEL1_ID = 4,
	VIEW12_HELP_QRCODE0_ID = 5,
	VIEW12_HELP_IMAGE0_ID = 1
} view12_help_ctrls_id_e;

void view12_help_init(void);
void view12_help_entry(void);
void view12_help_exit(void);
//.c文件里面自定义函数
void task_create12();
void task_del12();

#endif
