#ifndef __VIEW10_SELF_CLEANING_H_
#define __VIEW10_SELF_CLEANING_H_

typedef enum {
	VIEW10_SELF_CLEANING_NULL,
	VIEW10_SELF_CLEANING_IMAGE0_ID = 1,
	VIEW10_SELF_CLEANING_LABEL0_ID = 2
} view10_self_cleaning_ctrls_id_e;

void view10_self_cleaning_init(void);
void view10_self_cleaning_entry(void);
void view10_self_cleaning_exit(void);
extern u16 j_self_cleaning_var;
extern u8 uart_only_sent_once_self_cleaning_var;

#endif
