int retro_sprite_limit = 10;



static void getvars_sprite_limit_option()
{
	struct retro_variable var = { "sameboy_sprite_limit" };


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		retro_sprite_limit = atoi(var.value);
	}
}



RETRO_VARS_T sprite_limit_vars = {
	"sameboy_sprite_limit",
	"Sprites per scanline; 10|11|12|13|14|15|16|17|18|19|20|25|30|35|40"
};



static void setvars_sprite_limit_option()
{
	retro_setvars_add(&sprite_limit_vars);
}
