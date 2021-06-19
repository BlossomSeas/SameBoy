static int retro_input_lag;

static int retro_input_lag_count;
static int retro_input_lag_total;

static int retro_input_lag_frame;
static int retro_input_lag_last;



void retro_input_lag_reset()
{
	retro_input_lag_count = 0;
	retro_input_lag_total = 0;

	retro_input_lag_last = retro_input_lag_frame;
}



void retro_input_lag_write(GB_gameboy_t *gb)
{
	// same game frame
	if (retro_input_lag_frame == retro_input_lag_last)
		return;


	// LCD off
	if (!(gb->io_registers[GB_IO_LCDC] & 0x80))
		return;



	retro_input_lag_count++;
	retro_input_lag_last = retro_input_lag_frame;


	/* ===================================================== */


	// Report when ready
	if (retro_input_lag_total < retro_input_lag)
		return;


	// Game running behind
	if (retro_input_lag_count < retro_input_lag) {
		static char tmp[512];

		sprintf(tmp, "lag: %d / %d", retro_input_lag_count, retro_input_lag);

		printf("%s\n", tmp);
		retro_osd_message_add(tmp);
	}


	retro_input_lag_reset();
}



static void retro_input_lag_vblank()
{
	retro_input_lag_total++;
	retro_input_lag_frame++;
}



static void getvars_input_lag_logger()
{
	struct retro_variable var = { "sameboy_input_lag_monitor" };


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		retro_input_lag = atoi(var.value);

		retro_input_lag_reset();
	}
}



static RETRO_VARS_T input_lag_vars = {
	"sameboy_input_lag_monitor",
	"Detect in-game slowdown (joypad lag); 0|5|10|15|25|30|50|60|75|120|180|240|300"
};



static void setvars_input_lag_logger()
{
	retro_setvars_add(&input_lag_vars);
}
