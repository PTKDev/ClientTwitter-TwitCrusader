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
#include "inc/windows.updates.h"

/* GtkUpdatesDialogCreate() Function 
 *
 * Developer Guide (Italian): http://dev.it.twitcrusader.org/sourcecode-guide-gtk_updates_window_create-function/
 * 
 */
void gtk_window_update()
{

	GtkWidget *dialog;
	char* msg;
	asprintf(&msg,"%s: %s\n%s: %s%s", LAST_VERSION, download_version(), CURRENT_VERSION, TWC_VERSION, TWC_VERSION_STATUS);
	dialog=gtk_message_dialog_new(NULL,GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,msg);
	g_signal_connect_swapped (dialog, "response",G_CALLBACK (gtk_widget_destroy),dialog);
	gtk_dialog_run(GTK_DIALOG(dialog));


}
