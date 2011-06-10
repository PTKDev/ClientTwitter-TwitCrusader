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

#include "main.h"
/*
 * Main function and debug function
 * 
 */
int main(int argc, char **argv){

	pthread_t tid[2];
	int error;

	/* debug */
	if(shellParameters (argc, argv)==1) return 0;
	
	/* Fix Struct Size */
	mallocUsers();

	createDir();

	/* Main*/
	error = pthread_create(&tid[0], NULL, updateGtk, (void *)argv);

	error = pthread_create(&tid[1], NULL, windowMain, (void *)argv);

	error = pthread_join(tid[0], NULL);
	error = pthread_join(tid[1], NULL);
	
	freeSizeUsers();
	
	return 0;
}
