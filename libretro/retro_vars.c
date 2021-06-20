#include <memory.h>



/* ======================================== */
#define RETRO_CORE_OPTIONS_VERSION 0
/* ======================================== */



#define RETRO_VARS_FRONT 1
#define RETRO_VARS_BACK 2

#define RETRO_VARS_NORMAL 1
#define RETRO_VARS_SPECIAL 2



#if (RETRO_CORE_OPTIONS_VERSION == 0)
  #define RETRO_VARS_T struct retro_variable

#else
  #define RETRO_VARS_T struct retro_core_option_definition

#endif



static RETRO_VARS_T retro_vars_front[100];
static RETRO_VARS_T retro_vars_back[100];
static RETRO_VARS_T retro_vars_build[300];


static RETRO_VARS_T *retro_vars_front_ptr;
static RETRO_VARS_T *retro_vars_back_ptr;
static RETRO_VARS_T *retro_vars_list_ptr;


static RETRO_VARS_T retro_vars_erased = { "@__erased_key__@" };



static int retro_vars_env_type;
static int retro_vars_load_type;



static void retro_setvars_copy(RETRO_VARS_T *dst, RETRO_VARS_T *src)
{
#if (RETRO_CORE_OPTIONS_VERSION == 0)

	dst->key = src->key;
	dst->value = src->value;

#else

	dst->key = src->key;
	dst->desc = src->desc;
	dst->info = src->info;
	memcpy(dst->values, src->values, sizeof(src->values));
	dst->default_value = src->default_value;

#endif
}



static void retro_setvars_erase(char *key)
{
	RETRO_VARS_T *list = retro_vars_list_ptr;


	while (list->key) {
		if (strcmp(list->key, key) == 0) {
			list->key = retro_vars_erased.key;
			return;
		}

		list++;
	}
}



static void retro_setvars_edit(RETRO_VARS_T *item)
{
	RETRO_VARS_T *list = retro_vars_list_ptr;


	while (list->key) {
		if (strcmp(list->key, item->key) == 0) {
			retro_setvars_copy(list, item);
			return;
		}

		list++;
	}
}



static void retro_setvars_add(RETRO_VARS_T *item)
{
	RETRO_VARS_T *list = NULL;


	if (retro_vars_env_type == RETRO_VARS_FRONT) {
		list = retro_vars_front_ptr++;
	}

	else if (retro_vars_env_type == RETRO_VARS_BACK) {
		list = retro_vars_back_ptr++;
	}


	retro_setvars_copy(list, item);
}



static void retro_setvars_move(char *key)
{
	RETRO_VARS_T *list = retro_vars_list_ptr;


	while (list->key) {
		if (strcmp(list->key, key) == 0) {
			retro_setvars_add(list);
			retro_setvars_erase(key);
			return;
		}

		list++;
	}
}



static void retro_setvars_write()
{
	RETRO_VARS_T *dst, *src;


#define RETRO_SETVARS_COPY(x) \
	src = x; \
	\
	while (src->key) { \
		if (strcmp(src->key, retro_vars_erased.key) != 0) { \
			retro_setvars_copy(dst, src); \
			\
			dst++; \
		} \
		\
		src++; \
	}


	dst = &retro_vars_build[0];


	RETRO_SETVARS_COPY(&retro_vars_front[0]);
	RETRO_SETVARS_COPY(retro_vars_list_ptr);
	RETRO_SETVARS_COPY(&retro_vars_back[0]);


#undef RETRO_SETVARS_COPY
}



static void setvars_dummy_option()
{
	RETRO_VARS_T retro_dummy_option_new =

#if (RETRO_CORE_OPTIONS_VERSION == 0)

	{ "dummy_option", "------------------------------------------------------------------------; -" };

#else

	{
	  "dummy_option",
	  "------------------------------------------------------------------------",
	  "",
	  {
		{ "dummy", " " },
		{ NULL, NULL },
	  },
	  "dummy"
	};

#endif


	retro_setvars_add(&retro_dummy_option_new);
}



static void retro_setvars_init()
{
	if (retro_vars_env_type != -1)
		return;



	// nuke compiler warnings
	retro_setvars_add(NULL);
	retro_setvars_edit(NULL);
	retro_setvars_erase("");
	retro_setvars_move("");

	setvars_dummy_option();
}



static void setvars_front()
{
	retro_vars_env_type = RETRO_VARS_FRONT;
}



static void setvars_back()
{
	retro_vars_env_type = RETRO_VARS_BACK;
}



/* ============================================================= */



#include "retro_vars.h"



static void retro_setvars(int mode, RETRO_VARS_T *list)
{
	retro_vars_front_ptr = &retro_vars_front[0];
	retro_vars_back_ptr = &retro_vars_back[0];

	retro_vars_load_type = mode;
	retro_vars_list_ptr = list;


	retro_setvars_init();
	retro_setvars_build();
	retro_setvars_write();
}



static void retro_getvars(int mode)
{
	retro_vars_env_type = mode;


	retro_getvars_build();
}



static void retro_setvars_normal(RETRO_VARS_T *list)
{
	retro_setvars(RETRO_VARS_NORMAL, list);
}



static void retro_setvars_special(RETRO_VARS_T *list)
{
	retro_setvars(RETRO_VARS_SPECIAL, list);
}



static void retro_getvars_front()
{
	retro_getvars(RETRO_VARS_FRONT);
}



static void retro_getvars_back()
{
	retro_getvars(RETRO_VARS_BACK);
}
