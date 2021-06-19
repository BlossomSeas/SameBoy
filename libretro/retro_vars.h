#include "osd_message_logger.c"
#include "input_lag_logger.c"


#include "color_correction_option.c"
#include "master_volume_option.c"
#include "border_crop_option.c"
#include "fast_boot_option.c"
#include "display_overclock_option.c"
#include "sprite_limit_option.c"



static void retro_getvars_build()
{
	if (retro_vars_env_type == RETRO_VARS_FRONT) {
		getvars_color_correction_option();
		getvars_master_volume_option();
		getvars_border_crop_option();
		getvars_fast_boot_option();
		getvars_display_overclock_option();
		getvars_input_lag_logger();
		getvars_sprite_limit_option();
	}
}



static void retro_setvars_build()
{
	setvars_front();


	setvars_color_correction_option();


	/* ================================== */


	setvars_back();


	setvars_fast_boot_option();


	setvars_dummy_option();


	/* ================================== */



	retro_setvars_move("sameboy_border");
	setvars_border_crop_option();


	setvars_dummy_option();


	/* ================================== */


	setvars_display_overclock_option();


	setvars_dummy_option();


	/* ================================== */


	setvars_sprite_limit_option();
	setvars_input_lag_logger();
	setvars_master_volume_option();
}
