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

#include "inc/windows.main.h"

void gtk_window_main(){

	debug_f_start("gtk_window_main");

	gtk_init_window();
	gtk_init_menu();
	gtk_init_menu_bar();
	gtk_init_statusbar();
	gtk_init_toolbar_items();
	gtk_init_toolbar();
	gtk_init_charbar();
	gtk_init_scrolled_window();
	gtk_init_text_area();

	gtk_box_pack_start(GTK_BOX(mainWindow.layout), mainWindow.menu_bar, FALSE, FALSE, 0);

	gtk_table_attach (GTK_TABLE (mainWindow.table), mainWindow.scroll, 0, 3,8, 9, GTK_FILL | GTK_EXPAND,GTK_FILL | GTK_EXPAND, 0, 0);


	gtk_box_pack_end (GTK_BOX (mainWindow.layout), mainWindow.statusbar, FALSE, FALSE, 0);
	gtk_box_pack_end (GTK_BOX (mainWindow.layout), mainWindow.char_bar, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(mainWindow.scroll), mainWindow.text);

	gtk_box_pack_end (GTK_BOX (mainWindow.layout), mainWindow.toolbar, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(mainWindow.layout), mainWindow.table);

	gtk_container_add(GTK_CONTAINER(mainWindow.window), mainWindow.layout);

	/* CALLBACK: exit event */
	g_signal_connect (mainWindow.window, "delete_event", G_CALLBACK (on_quit), NULL);
	g_signal_connect (mainWindow.window, "destroy", G_CALLBACK (on_quit), NULL);


	// Widget Show
	gtk_widget_show_all (mainWindow.window);


	//Exist Config File?
	if(fopen(progPath.configFile, "r")==NULL){

		loadRegDialog();

	}else{

		gtk_refresh_timeline();

	}

	//Show GTK Main
	gtk_main ();

}

void gtk_init_window(){

	debug_f_start("gtk_init_window");

	mainWindow.scroll = gtk_scrolled_window_new(NULL,NULL);
	mainWindow.menu_bar = gtk_menu_bar_new();
	mainWindow.layout = gtk_vbox_new(0, 1);
	mainWindow.statusbar = gtk_statusbar_new ();
	mainWindow.char_bar = gtk_statusbar_new ();
	mainWindow.toolbar = gtk_toolbar_new ();
	mainWindow.table = gtk_table_new (9, 3, TRUE);
	mainWindow.text = gtk_text_view_new();

	/* Set all window options (color, size, position, logo, icon, etc) */
	mainWindow.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW(mainWindow.window), 315, 650);
	gtk_widget_set_size_request (mainWindow.window, 315, 400);
	gtk_window_set_title (GTK_WINDOW(mainWindow.window), TWC);
	gtk_container_set_border_width (GTK_CONTAINER (mainWindow.window), 0);
	gtk_window_set_position(GTK_WINDOW(mainWindow.window), GTK_WIN_POS_CENTER);
	gtk_window_set_icon_from_file (GTK_WINDOW(mainWindow.window), ICON_FAVICON, &mainWindow.error);

}

void gtk_init_menu(){

	debug_f_start("gtk_init_menu");

	menu1[0].name=CONNECT;
	menu1[0].icon=ICON_ADDUSER;
	menu1[0].function=G_CALLBACK (gtk_connect);

	menu1[1].name=DISCONNECT;
	menu1[1].icon=ICON_ADDUSER;
	menu1[1].function=G_CALLBACK (gtk_disconnect);

	menu1[2].name=OPTIONS;
	menu1[2].icon=ICON_SETTINGS;
	menu1[2].function=G_CALLBACK (loadWindowProperties);

	menu1[3].name=QUIT;
	menu1[3].icon=ICON_CLOSE;
	menu1[3].function=G_CALLBACK (on_quit);


	menuAiuto[0].name=UPDATES;
	menuAiuto[0].icon=ICON_UPGRADE;
	menuAiuto[0].function=G_CALLBACK (loadVersionDialog);

	menuAiuto[1].name=ABOUT;
	menuAiuto[1].icon=ICON_STAR;
	menuAiuto[1].function=G_CALLBACK (loadAboutDialog);


	/* GTK Widget: Menu */
	mainWindow.file_menu_obj = gtk_menu_new();
	mainWindow.aiuto_menu_obj = gtk_menu_new();

	int i;

	for(i=0;i<4;i++){
		mainWindow.file_menu_items[i] = gtk_image_menu_item_new_with_label(menu1[i].name);
		mainWindow.file_icon_menu[i] = gtk_image_new_from_file(menu1[i].icon);
		gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (mainWindow.file_menu_items[i]), mainWindow.file_icon_menu[i]);
		g_signal_connect (G_OBJECT (mainWindow.file_menu_items[i]), "activate", menu1[i].function, NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(mainWindow.file_menu_obj), mainWindow.file_menu_items[i]);
	}

	/* SubMenu: Help */
	for(i=0;i<2;i++){
		mainWindow.aiuto_menu_items[i] = gtk_image_menu_item_new_with_label(menuAiuto[i].name);
		mainWindow.aiuto_icon_menu[i] = gtk_image_new_from_file(menuAiuto[i].icon);
		gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (mainWindow.aiuto_menu_items[i]), mainWindow.aiuto_icon_menu[i]);
		g_signal_connect (G_OBJECT (mainWindow.aiuto_menu_items[i]), "activate", menuAiuto[i].function, NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(mainWindow.aiuto_menu_obj), mainWindow.aiuto_menu_items[i]);

	}

	mainWindow.file_menu_root = gtk_menu_item_new_with_label("File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM (mainWindow.file_menu_root), mainWindow.file_menu_obj);
	mainWindow.aiuto_menu_root = gtk_menu_item_new_with_label("Aiuto");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM (mainWindow.aiuto_menu_root), mainWindow.aiuto_menu_obj);

}

void gtk_refresh_menu(){
	debug_f_start("gtk_refresh_menu");

}
void gtk_init_statusbar(){

	debug_f_start("gtk_init_statusbar");


	/* Status Bar */

	StatusBar.message = GTK_STATUSBAR(mainWindow.statusbar);
	gtk_statusbar_set_has_resize_grip (StatusBar.message, TRUE);

	if(strcmp(user.screenName, " ") == 0 && strcmp(user.id, " ") == 0 ){
		mainWindow.statusLabel=PROFILE_DISCONNECTED;
	}else{
		mainWindow.statusLabel=PROFILE_CONNECTED;
	}

	gtk_statusbar_push (StatusBar.message, 0, mainWindow.statusLabel);

}

void gtk_init_toolbar(){

	debug_f_start("gtk_init_toolbar");

	/* GTK Widget: Twitter Menu */
	gtk_toolbar_set_style (GTK_TOOLBAR (mainWindow.toolbar), GTK_TOOLBAR_ICONS);
	gtk_toolbar_get_icon_size (GTK_TOOLBAR (mainWindow.toolbar));

}

void gtk_init_toolbar_items(){

	debug_f_start("gtk_init_toolbar_items");

	/* Twitter Menu: Buttons */


	tool_button[0].icon=ICON_UPDATE;
	tool_button[0].function=GTK_SIGNAL_FUNC(gtk_refresh_timeline);

	tool_button[1].icon=ICON_HOME;
	tool_button[1].function=GTK_SIGNAL_FUNC(show_home_timeline);

	tool_button[2].icon=ICON_MENTION;
	tool_button[2].function=GTK_SIGNAL_FUNC(mentions_timeline);

	tool_button[3].icon=ICON_DM;
	tool_button[3].function=GTK_SIGNAL_FUNC(foo);

	tool_button[4].icon=ICON_FAVORITES;
	tool_button[4].function=GTK_SIGNAL_FUNC(foo);

	tool_button[5].icon=ICON_LINK;
	tool_button[5].function=GTK_SIGNAL_FUNC(foo);

	tool_button[6].icon=ICON_PHOTO;
	tool_button[6].function=GTK_SIGNAL_FUNC(foo);

	int i;
	for(i=0; i<7;i++){
		mainWindow.tool_bar[i] = gtk_button_new();
		mainWindow.tool_icon_menu[i] = gtk_image_new_from_file(tool_button[i].icon);
		gtk_button_set_image(GTK_BUTTON(mainWindow.tool_bar[i]),mainWindow.tool_icon_menu[i]);
		gtk_container_add (GTK_CONTAINER (mainWindow.toolbar), mainWindow.tool_bar[i]);
		gtk_signal_connect_object (GTK_OBJECT (mainWindow.tool_bar[i]), "clicked", tool_button[i].function, NULL);
	}

}

void gtk_refresh_toolbar_items(){

	debug_f_start("gtk_refresh_toolbar_items");

}

void gtk_init_charbar(){

	debug_f_start("gtk_init_charbar");

	/* Status Bar: Twitter 140char */
	gtk_statusbar_set_has_resize_grip (GTK_STATUSBAR(mainWindow.char_bar), FALSE);
	gtk_statusbar_push (GTK_STATUSBAR(mainWindow.char_bar), 0, "140");

}

void gtk_init_text_area(){

	debug_f_start("gtk_init_text_area");

	// TextArea + Scrollbar
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(mainWindow.scroll),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);

	gtk_text_view_set_editable(GTK_TEXT_VIEW(mainWindow.text), TRUE);

	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(mainWindow.text), GTK_WRAP_WORD_CHAR);
	mainWindow.tweetBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (mainWindow.text));
	gtk_text_buffer_set_text (mainWindow.tweetBuffer, "", -1);

	g_signal_connect(mainWindow.tweetBuffer, "changed", G_CALLBACK(updateStatusBar), mainWindow.char_bar);
	g_signal_connect(mainWindow.text, "key-press-event", G_CALLBACK(gtkSendTweet), mainWindow.tweetBuffer);


}

void gtk_init_menu_bar(){

	debug_f_start("gtk_init_menu_bar");

	gtk_menu_bar_append(GTK_MENU_BAR (mainWindow.menu_bar), mainWindow.file_menu_root);
	gtk_menu_bar_append(GTK_MENU_BAR (mainWindow.menu_bar), mainWindow.aiuto_menu_root);

}

void gtk_init_scrolled_window(){

	debug_f_start("gtk_init_scrolled_window");


	int cols=0, rows=0;
	mainWindow.table_into = gtk_table_new (1, 3, TRUE);
	mainWindow.scrolled_window = gtk_scrolled_window_new (NULL, NULL);

	/* Scrolled */
	for (cols=0; cols < 20; rows = rows + 4, cols++) {
		mainWindow.avatar = gtk_image_new_from_file (timeline[cols].user.profile_image);
		mainWindow.nick = gtk_label_new (timeline[cols].user.screen_name);
		mainWindow.tweet = gtk_label_new (timeline[cols].text);

		gtk_table_attach (GTK_TABLE (mainWindow.table_into), mainWindow.avatar, 0, 1,rows, rows + 4, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 0);
		gtk_label_set_justify(GTK_LABEL(mainWindow.nick),GTK_JUSTIFY_LEFT);
		mainWindow.align = gtk_alignment_new(0.0, 0.5, 0.0, 0.0);
		gtk_container_add(GTK_CONTAINER(mainWindow.align), mainWindow.nick);
		gtk_table_attach (GTK_TABLE (mainWindow.table_into), mainWindow.align, 1, 10,rows, rows + 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 0);


		gtk_label_set_justify(GTK_LABEL(mainWindow.tweet),GTK_JUSTIFY_LEFT);
		gtk_label_set_line_wrap(GTK_LABEL(mainWindow.tweet), TRUE);
		mainWindow.align = gtk_alignment_new(0.0, 0.5, 0.0, 0.0);
		gtk_container_add(GTK_CONTAINER(mainWindow.align), mainWindow.tweet);
		gtk_table_attach (GTK_TABLE (mainWindow.table_into ), mainWindow.align, 1, 10,rows + 1, rows + 4, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 0);
	}

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (mainWindow.scrolled_window),GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (mainWindow.scrolled_window), mainWindow.table_into);

	gtk_table_attach (GTK_TABLE (mainWindow.table), mainWindow.scrolled_window, 0, 3, 0, 8, GTK_FILL,GTK_FILL, 0, 0);


}

/*
 * Get Buffer from TextArea and send tweet if user press ENTER on keyboard
 *
 */
gboolean gtkSendTweet(GtkWidget *TextArea, GdkEventKey *pKey, GtkTextBuffer *tweetBuffer){

	debug_f_start("gtkSendTweet");


	GtkTextIter start,
	end;
	char *msg = NULL;
	int send = 1;

	/* Get start position of cursor and final position */
	gtk_text_buffer_get_start_iter (tweetBuffer, &start);
	gtk_text_buffer_get_end_iter (tweetBuffer, &end);

	/* Casting buffer to char */
	msg = gtk_text_buffer_get_text(tweetBuffer, &start, &end, TRUE);

	/* If user press ENTER on keyboard Send Tweet and clean TextArea*/
	if(pKey->keyval == GDK_Return){

		gtk_statusbar_push (GTK_STATUSBAR(StatusBar.message), 0, "Invio In Corso...");

		//SendTweet
		send = SendTweet(msg);

		if(send == 0 || send == 1){
			gtk_statusbar_push (GTK_STATUSBAR(StatusBar.message), 0, "Tweet Non Inviato!");
		} else {
			gtk_statusbar_push (GTK_STATUSBAR(StatusBar.message), 0, "Tweet Inviato!");
			gtk_text_buffer_delete(tweetBuffer, &start, &end);
		}

		//Clean TextArea


		return 1; // fix cursor (return to previous line)
	}

	return 0;

}

/*
 * Count char from TextArea
 * Tweet have 140 to 0 char
 *
 */
void updateStatusBar(GtkTextBuffer *buffer,GtkStatusbar *statusbar){

	debug_f_start("updateStatusBar");


	gchar *msg;
	gint tot_char;
	GtkTextIter iter;

	/* Get message from statusbar and position */
	gtk_statusbar_pop(statusbar, 0);
	gtk_text_buffer_get_iter_at_mark(buffer,&iter, gtk_text_buffer_get_insert(buffer));

	/*Count input char */
	tot_char = 139 - gtk_text_iter_get_line_offset(&iter);
	tot_char = tot_char - gtk_text_iter_get_line(&iter);
	msg = g_strdup_printf("%d", tot_char+1);
	if(tot_char <= 0){
		msg = g_strdup_printf("%d", 0);
		gtk_text_buffer_backspace(buffer, &iter, TRUE, TRUE);
	}

	/* Push numer of char to statusbar */
	gtk_statusbar_push(statusbar, 0, msg);
	g_free(msg);

}

void loadAboutDialog(){

	debug_f_start("loadAboutDialog");

	gtk_credits_dialog();
}
void loadVersionDialog(){

	debug_f_start("loadVersionDialog");

	gtk_window_update();

}
void loadWindowProperties(){

	debug_f_start("loadWindowProperties");

	gtk_window_properties();
}
void loadRegDialog(){

	debug_f_start("loadRegDialog");

	gtk_window_register();

}

void clear_statusbar(){

	debug_f_start("clear_statusbar");


}

void show_home_timeline(){

	debug_f_start("show_home_timeline");

	if(strcmp(user.screenName, " ") != 0 && strcmp(user.id, " ") != 0 ){
		mainWindow.selected_timeline=1;
		gtk_refresh_timeline();
	}

}
void mentions_timeline(){

	debug_f_start("mentions_timeline");

	if(strcmp(user.screenName, " ") != 0 && strcmp(user.id, " ") != 0 ){
		mainWindow.selected_timeline=2;
		gtk_refresh_timeline();
	}

}
void show_private_message(){

	debug_f_start("show_private_message");

	if(strcmp(user.screenName, " ") != 0 && strcmp(user.id, " ") != 0 ){

	}
}

void gtk_refresh_timeline(){

	debug_f_start("gtk_refresh_timeline");


	int error;

	error=switchTimeLine(mainWindow.selected_timeline);

	if(error==0){
		downloadsAvatars();
	}

	gtk_refresh();
}

void gtk_refresh(){

	debug_f_start("gtk_refresh");

	gtk_refresh_menu();
	gtk_init_statusbar();
	gtk_init_scrolled_window();
	gtk_refresh_toolbar_items();
	gtk_widget_show_all(mainWindow.window);
	gtk_widget_queue_draw(mainWindow.window);
}

void foo(){

	debug_f_start("foo");

}

void gtk_connect(){

	debug_f_start("gtk_connect");

	if(readUserFile()==0){
		mainWindow.logged=1;
		mainWindow.selected_timeline=1;
		gtk_refresh_timeline();
	}
}
void gtk_disconnect(){

	debug_f_start("gtk_disconnect");

	disconnect();

	mainWindow.logged=0;
	mainWindow.selected_timeline=0;

	gtk_refresh_timeline();

}

void downloadsAvatars(){

	debug_f_start("downloadsAvatars");


	pthread_t tid;
	int i, error=0;

	for(i=0; i<MAX_NUM_TWEETS; i++){
		char *argv[2];
		argv[0]=timeline[i].user.profile_image_url;
		argv[1]=timeline[i].user.profile_image;

		error = pthread_create(&tid, NULL, pull_one_url, (void *)argv);


			if(0 != error){
				debug_var_int("Can't Start Thread Number",i);
			}
			else{
				debug_var_int("Start Thread Number",i);
				debug_var_char("Thread argument",argv[0]);
		}

		error = pthread_join(tid, NULL);
		debug_var_int("Stop Thread Number",i);

	}
}


void on_quit(){

	debug_f_start("on_quit");

	notifySystem(QUIT);
	gtk_main_quit();
}

