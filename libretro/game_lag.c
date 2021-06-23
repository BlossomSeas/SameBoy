static int retro_game_lag;

static int retro_game_lag_count;
static int retro_game_lag_total;

static int retro_game_lag_frame;
static int retro_game_lag_last;



void retro_game_lag_reset()
{
	retro_game_lag_count = 0;
	retro_game_lag_total = 0;

	retro_game_lag_last = retro_game_lag_frame;
}



void retro_game_lag_write(GB_gameboy_t *gb)
{
	// same game frame
	if (retro_game_lag_frame == retro_game_lag_last)
		return;


	// LCD off
	if (!(gb->io_registers[GB_IO_LCDC] & 0x80))
		return;


	// record joypad read
	retro_game_lag_count++;
	retro_game_lag_last = retro_game_lag_frame;


	/* ===================================================== */


	// Report when ready
	if (retro_game_lag_total < retro_game_lag)
		return;


	// Game running behind
	if (retro_game_lag_count < retro_game_lag) {
		static char tmp[512];

		sprintf(tmp, "lag: %d / %d", retro_game_lag_count, retro_game_lag);

		printf("%s\n", tmp);
		retro_osd_message_add(tmp);
	}


	retro_game_lag_reset();
}



static void retro_game_lag_vblank()
{
	retro_game_lag_total++;
	retro_game_lag_frame++;
}



static void getvars_game_lag()
{
	struct retro_variable var = { "sameboy_game_lag" };


	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		retro_game_lag = atoi(var.value);

		retro_game_lag_reset();
	}
}



static RETRO_VARS_T game_lag_vars = {
	"sameboy_game_lag",
	"Detect in-game slowdown; 0|5|10|15|25|30|50|60|75|120|180|240|300"
};



static void setvars_game_lag()
{
	retro_setvars_add(&game_lag_vars);
}
