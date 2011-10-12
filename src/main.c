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
 * 
 *		Follow on Twitter: @teamtwc
 * 		IRC: chat.freenode.net at #teamtwc
 * 		E-mail: teamtwc@twitcrusader.org
 * 
 */

/* Headers */
#include "main.h"

/* Main() Function 
 *
 * Developer Guide: http://dev.it.twitcrusader.org/sourcecode-guide-main-function/
 * 
 * Compile This Software With:
 * $ gcc -Wall -DICONS_DIR=\""../img"\" -o twc main.c main.h core/inc/sys.h core/inc/file.h core/inc/url.h gui/windows.main.c gui/inc/windows.main.h gui/windows.credits.c gui/inc/windows.credits.h gui/windows.updates.c gui/inc/windows.updates.h tools/debugger.c tools/inc/debugger.h gui/inc/icons.h `pkg-config --cflags --libs gtk+-2.0 oauth libxml-2.0`
 * 
 */
int main(int argc, char *argv[]){

	printf("\n\nTwitCrusader - Twitter Client For Linux Desktop\n");
	printf("Copyright (C) 2011  TwitCrusader Team\n\n");

	if(shell_parameters (argc, argv)==1) return 0;

	debug_f_start("main");

	bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);


	notify_init(TWC);

	g_type_init();

	if(g_thread_supported() ){
		g_thread_init(NULL);
		gdk_threads_init(); // Called to initialize internal mutex "gdk_threads_mutex".

		debug_var_char("g_thread:","supported");
	}else{
		debug_var_char("g_thread:","not supported");
	}

	gtk_init (&argc, &argv);
	notify_system(START);

	/* Fix Struct Size */
	malloc_users();

	create_dir();

	read_preference_file();


	gtk_window_main(NULL);

	/*if( (twcThread.action = g_thread_create((GThreadFunc)gtk_refresh_timeline, (void *)argv, TRUE, &twcThread.err_action)) == NULL){

		g_error_free ( twcThread.err_action ) ;
	}

	if( (twcThread.window = g_thread_create((GThreadFunc)gtk_window_main, (void *)argv, TRUE, &twcThread.err_window)) == NULL){

		g_error_free ( twcThread.err_window ) ;
	}
	g_thread_join(twcThread.action);
	g_thread_join(twcThread.window);
	 */

	free_size_preference();
	free_size_users();


	notify_uninit();

	return 0;

}
