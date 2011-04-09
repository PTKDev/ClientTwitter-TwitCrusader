/* 
*	TwitCrusader - Twitter Client For Linux Desktop
*		Copyright (C) 2011  PTKDev, RoxShannon
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
*		Author: Patryk Rzucidlo (PTKDev)
*		Twitter: @ptkdev / @twitcrusader_en
*		WebSite: http://www.twitcrusader.org
*/

#ifndef _TWITCRUSADER_H
#define _TWITCRUSADER_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

//oAuth Input
typedef struct
{       
	GtkWidget *pin;
	
} AuthWidget; 

char *sum_string(char *parm1, char *parm2 );
char* get_param(char** argv, int argc, const char* param);


#endif
