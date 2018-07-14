/*
 * Copyright (C) 2018 iTX Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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