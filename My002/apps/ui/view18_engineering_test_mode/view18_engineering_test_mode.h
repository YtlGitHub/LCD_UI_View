#ifndef __VIEW18_ENGINEERING_TEST_MODE_H_
#define __VIEW18_ENGINEERING_TEST_MODE_H_

typedef enum {
	VIEW18_ENGINEERING_TEST_MODE_NULL,
	VIEW18_ENGINEERING_TEST_MODE_LABEL0_ID = 1,
	VIEW18_ENGINEERING_TEST_MODE_LABEL1_ID = 2,
	VIEW18_ENGINEERING_TEST_MODE_LABEL2_ID = 3
} view18_engineering_test_mode_ctrls_id_e;

void view18_engineering_test_mode_init(void);
void view18_engineering_test_mode_entry(void);
void view18_engineering_test_mode_exit(void);
void task_create18();
void task_del18();

#endif
