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
 * 		IRC: chat.freenode.net at #teamtwc
 */

#include "include/twitcrusader.h"
#include "include/gtkwindows.h"
#include "include/function.h"
#include "include/twitter.h"
/*
 * Main function and debug function
 * 
 */
int main(int argc, char **argv){

	/* debug */
	if(shellParameters (argc, argv)==1) return 0;
	
	/* Fix Struct Size */
	mollocSizeOF();

	/* Main*/
	windowMain(argc, argv);
	
	freeSizeOF();
	
	return 0;
}
