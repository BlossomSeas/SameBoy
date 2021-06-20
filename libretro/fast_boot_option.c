int retro_fast_boot;



static void getvars_fast_boot_option()
{
	struct retro_variable var = { "sameboy_fast_boot_option" };


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if (strcmp(var.value, "disabled") == 0)
			retro_fast_boot = 0;

		else if (strcmp(var.value, "enabled") == 0)
			retro_fast_boot = 1;
	}
}



static RETRO_VARS_T fast_bios_vars = {
	"sameboy_fast_boot_option",
	"Skip BIOS boot; disabled|enabled"
};



static void setvars_fast_boot_option()
{
	retro_setvars_add(&fast_bios_vars);
}
