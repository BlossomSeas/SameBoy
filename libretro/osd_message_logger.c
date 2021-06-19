static char retro_osd_message[4096];


#define _retroenv environ_cb



void retro_osd_message_add(char *str)
{
	if (retro_osd_message[0] != '\0')
		strcat(retro_osd_message, "\n");


	strcat(retro_osd_message, str);
}



static void retro_osd_message_send()
{
	if (retro_osd_message[0] == '\0')
		return;


	struct retro_message msg = { retro_osd_message, 120+30 };
	_retroenv(RETRO_ENVIRONMENT_SET_MESSAGE, &msg);
	
	
	retro_osd_message[0] = '\0';
}
