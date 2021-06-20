int retro_overclock_count;

int retro_overclock_active;
int retro_overclock_vreset;
int retro_overclock_hreset;
int retro_overclock_vblank;



void retro_set_display_overclock(int mode)
{
	if (!retro_overclock_active)
		return;


	// negative = pending
	switch (mode) {
		case 1: retro_overclock_count -= retro_overclock_vreset; break;
		case 2: retro_overclock_count -= retro_overclock_hreset; break;
		case 3: retro_overclock_count -= retro_overclock_vblank; break;
	}
}



static void getvars_display_overclock_option()
{
	struct retro_variable var = { "sameboy_display_overclock_active" };
	struct retro_variable var1 = { "sameboy_display_overclock_vreset" };
	struct retro_variable var2 = { "sameboy_display_overclock_hreset" };
	struct retro_variable var3 = { "sameboy_display_overclock_vblank" };


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		if (strcmp("enabled", var.value) == 0 ) {
			retro_overclock_active = true;
		}

		else if (strcmp("disabled", var.value) == 0 ) {
			retro_overclock_active = false;
		}
	}

	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var1) && var1.value) {
		retro_overclock_vreset = atoi(var1.value);
	}

	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var2) && var2.value) {
		retro_overclock_hreset = atoi(var2.value);
	}

	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var3) && var3.value) {
		retro_overclock_vblank = atoi(var3.value);
	}
}



static RETRO_VARS_T system_overclock_active_vars = {
	"sameboy_display_overclock_active",
	"Display overclock; disabled|enabled"
};

static RETRO_VARS_T system_overclock_vreset_vars = {
	"sameboy_display_overclock_vreset",
	"Vertical reset overclock; 0|25|50|100|150|200|300|400|500|600|700|800|900|1000|2000|3000|4000|5000|6000|7000|8000|9000|10000|20000|30000|40000|50000|60000|70000|80000|90000|100000|500000|1000000"
};

static RETRO_VARS_T system_overclock_hreset_vars = {
	"sameboy_display_overclock_hreset",
	"Horizontal reset overclock; 0|10|20|35|50|75|100|125|150|175|200|300|400|500|600|700|800|900|1000"
};

static RETRO_VARS_T system_overclock_vblank_vars = {
	"sameboy_display_overclock_vblank",
	"Vertical blank overlock; 0|25|50|100|150|200|300|400|500|600|700|800|900|1000|2000|3000|4000|5000|6000|7000|8000|9000|10000|20000|30000|40000|50000|60000|70000|80000|90000|100000|500000|1000000"
};



static void setvars_display_overclock_option()
{
	retro_setvars_add(&system_overclock_active_vars);

	retro_setvars_add(&system_overclock_vreset_vars);
	retro_setvars_add(&system_overclock_hreset_vars);
	retro_setvars_add(&system_overclock_vblank_vars);
}
