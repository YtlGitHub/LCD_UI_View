#ifndef __VIEW06_STERILIZATION_H_
#define __VIEW06_STERILIZATION_H_

typedef enum {
	VIEW06_STERILIZATION_NULL,
	VIEW06_STERILIZATION_LABEL0_ID = 1,
	VIEW06_STERILIZATION_IMAGE0_ID = 2
} view06_sterilization_ctrls_id_e;

void view06_sterilization_init(void);
void view06_sterilization_entry(void);
void view06_sterilization_exit(void);

#endif
