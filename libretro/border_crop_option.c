static int retro_border_zoom;
static int retro_border_width;
static int retro_border_height;



static int get_border_width()
{
	int width = GB_get_screen_width(&gameboy[0]);

	if (retro_border_zoom && width == 256) {
		width -= retro_border_width * 2;
	}

	return width;
}



static int get_border_height()
{
	int height = GB_get_screen_height(&gameboy[0]);

	if (retro_border_zoom && height == 224) {
		height -= retro_border_height * 2;
	}

	return height;
}



static int get_border_base()
{
	int width = GB_get_screen_width(&gameboy[0]);
	int base = 0;

	if (retro_border_zoom && width == 256) {
		base = retro_border_width + retro_border_height * width;
	}

	return base;
}



static void getvars_border_crop_option()
{
	struct retro_variable var = { "sameboy_border_zoom" };
	struct retro_variable var1 = { "sameboy_border_width" };
	struct retro_variable var2 = { "sameboy_border_height" };


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if (!strcmp(var.value, "disabled"))
			retro_border_zoom = false;

		else if (!strcmp(var.value, "enabled"))
			retro_border_zoom = true;

		geometry_updated = true;
	}


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var1) && var1.value) {
		retro_border_width = atoi(var1.value) / 2;

		geometry_updated = true;
	}


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var2) && var2.value) {
		retro_border_height = atoi(var2.value) / 2;

		geometry_updated = true;
	}
}



RETRO_VARS_T border_zoom_vars = {
	"sameboy_border_zoom",
	"Crop SGB border; disabled|enabled"
};

RETRO_VARS_T border_width_vars = {
	"sameboy_border_width",
	"Crop SGB border width; 0|2|4|6|8|10|12|14|16|18|20|22|24|26|28|30|32|34|36|38|40|42|44|46|48|50|52|54|56|58|60|62|64|66|68|70|72|74|76|78|80|82|84|86|88|90|92|94|96"
};

RETRO_VARS_T border_height_vars = {
	"sameboy_border_height",
	"Crop SGB border height; 0|2|4|6|8|10|12|14|16|18|20|22|24|26|28|30|32|34|36|38|40|42|44|46|48|50|52|54|56|58|60|62|64|66|68|70|72|74|76|78|80"
};



static void setvars_border_crop_option()
{
	if (emulated_devices == 1) {
		retro_setvars_add(&border_zoom_vars);
		retro_setvars_add(&border_width_vars);
		retro_setvars_add(&border_height_vars);
	}
}
