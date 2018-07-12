#include "Util.h"

String Util::getUptime()
{
	long time = millis() / 1000;
	int seconds = floor(time % 60);
	int minutes = 0;
	int hours = 0;
	int days = 0;
	long aDay = 86400L;
	if (time >= 60)
	{
		minutes = floor((time % 3600) / 60);
		if (time >= 3600)
		{
			hours = floor((time % aDay) / 3600);
			if (time >= aDay)
			{
				days = floor(time / aDay);
			}
		}
	}
	String uptime = (minutes != 0 ? (hours != 0 ? (days != 0 ? (String(days) + " d ")
															 : "") +
													  (String(hours) + " h ")
												: "") +
										(String(minutes) + " m ")
								  : "") +
					(String(seconds) + " s");
	return uptime;
}