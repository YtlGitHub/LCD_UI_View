#ifndef __VIEW19_RESTORE_FACTORY_SETTINGS_H_
#define __VIEW19_RESTORE_FACTORY_SETTINGS_H_

typedef enum {
	VIEW19_RESTORE_FACTORY_SETTINGS_NULL,
	VIEW19_RESTORE_FACTORY_SETTINGS_LABEL0_ID = 2,
	VIEW19_RESTORE_FACTORY_SETTINGS_IMAGE0_ID = 1
} view19_restore_factory_settings_ctrls_id_e;

void view19_restore_factory_settings_init(void);
void view19_restore_factory_settings_entry(void);
void view19_restore_factory_settings_exit(void);
//void task_create19(void);
//void task_del19(void);

#endif
