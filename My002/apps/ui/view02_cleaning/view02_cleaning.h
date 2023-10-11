#ifndef __VIEW02_CLEANING_H_
#define __VIEW02_CLEANING_H_

typedef enum {
	VIEW02_CLEANING_NULL,
	VIEW02_CLEANING_IMAGE0_ID = 2,
	VIEW02_CLEANING_LABEL0_ID = 1
} view02_cleaning_ctrls_id_e;


void view02_cleaning_init(void);
void view02_cleaning_entry(void);
void view02_cleaning_exit(void);


#endif
