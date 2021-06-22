static void getvars_color_correction()
{
	struct retro_variable var = { "sameboy_color_correction_mixing" };


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		extern uint8_t scale_channel_with_curve_mix(int scale);

		int retro_color_mixing = atoi(var.value);
		scale_channel_with_curve_mix(retro_color_mixing);
	}



	if (emulated_devices == 1) { 
		struct retro_variable var = { "sameboy_color_correction_mode" };

	
		if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
			if (strcmp(var.value, "gbc") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC);
			}

			else if (strcmp(var.value, "sgb") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_SGB);
			}

			else if (strcmp(var.value, "gba") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBA);
			}

			else if (strcmp(var.value, "gbc % rgb") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC_MIX_RGB);
			}

			else if (strcmp(var.value, "gbc % sgb") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC_MIX_SGB);
			}

			else if (strcmp(var.value, "gbc % gba") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC_MIX_GBA);
			}
		}
	}

	else {
		struct retro_variable var = { "sameboy_color_correction_mode_1" };
		struct retro_variable var2 = { "sameboy_color_correction_mode_2" };

	
		if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
			if (strcmp(var.value, "gbc") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC);
			}

			else if (strcmp(var.value, "sgb") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_SGB);
			}

			else if (strcmp(var.value, "gba") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBA);
			}

			else if (strcmp(var.value, "gbc % rgb") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC_MIX_RGB);
			}

			else if (strcmp(var.value, "gbc % sgb") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC_MIX_SGB);
			}

			else if (strcmp(var.value, "gbc % gba") == 0) {
				GB_set_color_correction_mode(&gameboy[0], GB_COLOR_CORRECTION_GBC_MIX_GBA);
			}
		}


		if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var2) && var2.value) {
			if (strcmp(var2.value, "gbc") == 0) {
				GB_set_color_correction_mode(&gameboy[1], GB_COLOR_CORRECTION_GBC);
			}

			else if (strcmp(var2.value, "sgb") == 0) {
				GB_set_color_correction_mode(&gameboy[1], GB_COLOR_CORRECTION_SGB);
			}

			else if (strcmp(var2.value, "gba") == 0) {
				GB_set_color_correction_mode(&gameboy[1], GB_COLOR_CORRECTION_GBA);
			}

			else if (strcmp(var2.value, "gbc % rgb") == 0) {
				GB_set_color_correction_mode(&gameboy[1], GB_COLOR_CORRECTION_GBC_MIX_RGB);
			}

			else if (strcmp(var2.value, "gbc % sgb") == 0) {
				GB_set_color_correction_mode(&gameboy[1], GB_COLOR_CORRECTION_GBC_MIX_SGB);
			}

			else if (strcmp(var2.value, "gbc % gba") == 0) {
				GB_set_color_correction_mode(&gameboy[1], GB_COLOR_CORRECTION_GBC_MIX_GBA);
			}
		}
	}
}



static RETRO_VARS_T color_correction_vars_0 = {
	"sameboy_color_correction_mode",
	"Color correction; emulate hardware|preserve brightness|reduce contrast|off|gbc|gbc|sgb|gba|gbc % rgb|gbc % sgb|gbc % gba|correct curves"
};

static RETRO_VARS_T color_correction_vars_1 = {
	"sameboy_color_correction_mode_1",
	"Color correction for Game Boy #1; emulate hardware|preserve brightness|reduce contrast|off|gbc|sgb|gba|gbc % rgb|gbc % sgb|gbc % gba|correct curves"
};

static RETRO_VARS_T color_correction_vars_2 = {
	"sameboy_color_correction_mode_2",
	"Color correction for Game Boy #2; emulate hardware|preserve brightness|reduce contrast|off|gbc|sgb|gba|gbc % rgb|gbc % sgb|gbc % gba|correct curves"
};

static RETRO_VARS_T color_correction_mixing_vars = {
	"sameboy_color_correction_mixing",
	"Color correction mixing ratio; 100|0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31|32|33|34|35|36|37|38|39|40|41|42|43|44|45|46|47|48|49|50|51|52|53|54|55|56|57|58|59|60|61|62|63|64|65|66|67|68|69|70|71|72|73|74|75|76|77|78|79|80|81|82|83|84|85|86|87|88|89|90|91|92|93|94|95|96|97|98|99"
};



static void setvars_color_correction()
{
	if (emulated_devices == 1) {
		retro_setvars_erase("sameboy_color_correction_mode");
		retro_setvars_add(&color_correction_vars_0);

		retro_setvars_add(&color_correction_mixing_vars);
	}

	else {
		retro_setvars_edit(&color_correction_vars_1);
		retro_setvars_edit(&color_correction_vars_2);
	}
}
