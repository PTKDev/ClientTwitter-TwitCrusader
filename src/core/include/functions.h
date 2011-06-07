/*
 *	TwitCrusader - Twitter Client For Linux Desktop
 *		Copyright (C) 2011  TwitCrusader Team
 *
 *		This program is free software: you can redistribute it and/or modify
 *		it under the terms of the GNU General Public License as published by
 *		the Free Software Foundation, either version 3 of the License, or
 *		(at your option) any later version.
 *
 *		This program is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License
 *		along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *		WebSite: http://www.twitcrusader.org/
 * 		Development Guidelines: http://dev.twitcrusader.org/
 *		Follow on Twitter: @teamtwc
 * 		IRC: chat.freenode.net at #teamtwc
 * 		E-mail: teamtwc@twitcrusader.org
 * 
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#define _GNU_SOURCE
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "config.h"

#define TWC_VERSION "2011"
#define TWC_VERSION_STATUS "-Nightly"
#define TWC_UPDATES_URL "http://www.twitcrusader.org/version-nightly.php"

int debug;
void mallocSizeOF();
void freeSizeOF(void);
char *sumStrings(char *parm1, char *parm2 );
char* getParameters(char** argv, int argc, const char* param);
int shellParameters (int argc, char **argv);
void createDir();
char* downloadVersion();

#endif /* FUNCTION_H_ */
