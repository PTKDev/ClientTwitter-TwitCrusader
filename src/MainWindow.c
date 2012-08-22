/*
 *	TwitCrusader - Twitter Client For Linux Desktop
 *	Copyright (C) 2012 - Patryk Rzucidlo <ptkdev@gmail.com>
 *	Orazio Briante <orazio.briante@hotmail.it>
 *
 *
 * This Program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *		WebSite: http://www.twitcrusader.org/
 * 		Development Guidelines: http://dev.twitcrusader.org/
 * 
 *		Follow on Twitter: @teamtwc
 * 		IRC: chat.freenode.net at #teamtwc
 * 		E-mail: teamtwc@twitcrusader.org
 */

#include <twc/twc.h>

#include <twitc/twitc.h>

#include <twc/preference.h>

#include <twc/icons.h>
#include <twc/MainWindow.h>
#include <twc/Credits.h>
#include <twc/Version.h>
#include <twc/Property.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#ifdef __cplusplus
extern "C"
{
#endif

  static GtkWidget *window = NULL;
  static GtkWidget *toolbar = NULL;
  static GtkWidget *charBar = NULL;
  static GtkWidget *statusbar = NULL;
  static GtkWidget *table = NULL;
  static GtkWidget *box = NULL;
  static GtkWidget *scroll = NULL;
  static GtkWidget *scrolled_window = NULL;
  static GtkWidget *tableTW = NULL;

  static gboolean iconified = FALSE;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  static ProgramPath_t *progPath = NULL;
  static user_t *user = NULL;
  static twitterURLS_t *twitterURLS = NULL;
  static byte_t swTimeline = 1;

  extern void
  init_charbar(string_t);

  extern void
  startMainWindow();

  extern void
  refreshWindow();

  extern void
  updateTimeline();

  extern void
  homeTimeline();

  extern void
  mentionsTimeline();

  extern void
  loadWindowProperty();

  static void
  foo()
  {

  }

  void
  Connect()
  {
    if (!user)

      user = readUserFile(progPath->configFile);

  }

  void
  StartGUI()
  {
    if (!progPath)
      progPath = initProgPath(PROG_PATH, AVATAR_DIR, CONFIG_DIR, CONFIG_FILE,
          PREFERENCE_FILE);

    if (!twitterURLS)
      twitterURLS = initURLS(OAUTH_URL_DEFAULT, API_URL_DEFAULT,
          SEARCH_URL_DEFAULT);

    Connect();

    if (!user)
      {
        startRegistrationWindow(window);
        Connect();
      }

    if (user)
      {
        if (!window)
          {
            startMainWindow();
            updateTimeline();
          }
        else
          {
            if (iconified)
              {
                gtk_window_deiconify(GTK_WINDOW (window) );
                refreshWindow();

                iconified = FALSE;
              }
            else
              {
                gtk_widget_hide(window);

                iconified = TRUE;

              }

          }
      }
  }

  void
  updateStatusBar(GtkTextBuffer * buffer, GtkStatusbar * charbar)
  {
    GtkTextIter iter;

    /* Get message from statusbar and position */
    gtk_statusbar_pop(charbar, 0);

    gtk_text_buffer_get_iter_at_mark(buffer, &iter,
        gtk_text_buffer_get_insert(buffer));

    /*Count input char */
    gint totChar = 139 - gtk_text_iter_get_line_offset(&iter);
    totChar = totChar - gtk_text_iter_get_line(&iter);

    gchar *msg = g_strdup_printf("%d", totChar + 1);
    if (totChar <= 0)
      {
        msg = g_strdup_printf("%d", 0);
        gtk_text_buffer_backspace(buffer, &iter, TRUE, TRUE);
      }

    /* Push numer of char to statusbar */
    gtk_statusbar_push(GTK_STATUSBAR (charBar), 0, msg);
    g_free(msg);

  }

  /*
   * Get Buffer from TextArea and send tweet if user press ENTER on keyboard
   *
   */
  gboolean
  gtkSendTweet(GtkWidget * TextArea, GdkEventKey * pKey, GtkTextBuffer * buffer)
  {

    GtkTextIter start, end;

    /* Get start position of cursor and final position */
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    /* Casting buffer to char */
    string_t msg = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);

    if (msg)
      {
        /* If user press ENTER on keyboard Send Tweet and clean TextArea */
        if (pKey->keyval == GDK_KEY_Return)
          {

            //SendTweet
            if (updateStatus(twitterURLS, user, msg))
              {
                gtk_statusbar_push(GTK_STATUSBAR (statusbar), 0,
                    "Tweet correctly sent..");
                gtk_text_buffer_delete(buffer, &start, &end);

                return TRUE;
              }

            gtk_statusbar_push(GTK_STATUSBAR (statusbar), 0,
                "Tweet was not sent..");
            gtk_text_buffer_delete(buffer, &start, &end);

          }
      }

    return FALSE;
  }

  void
  refreshWindow()
  {
    gtk_widget_show_all(window);
    gtk_widget_realize(window);
  }

  void
  init_main_window()
  {
    if (!window)
      {
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW (window), PROG_NAME);
        gtk_window_set_default_size(GTK_WINDOW (window), 315, 650);
        gtk_widget_set_size_request(window, 315, 400);
        gtk_container_set_border_width(GTK_CONTAINER (window), 0);
        gtk_window_set_position(GTK_WINDOW (window), GTK_WIN_POS_CENTER);

        gtk_window_set_destroy_with_parent(GTK_WINDOW (window), TRUE);

        GError *error = NULL;
        gtk_window_set_icon_from_file(GTK_WINDOW (window),
            ICONS_DIR "" ICON_FAVICON, &error);

        if (error)
          {
            error((string_t) error->message);
            g_error_free(error);
            error = NULL;
          }
      }

  }

  void
  init_toolbar()
  {

    if (!toolbar)
      {
        toolbar = gtk_toolbar_new();

        const string_t titles[] =
            { "Update", "Home", "Mentions", "Direct Messages", "Favorites", "Link",
                "Photo" };

        const string_t icons[] =
            { ICONS_DIR "" ICON_UPDATE, ICONS_DIR "" ICON_HOME,
                ICONS_DIR "" ICON_MENTION, ICONS_DIR "" ICON_DM,
                ICONS_DIR "" ICON_FAVORITES, ICONS_DIR "" ICON_LINK,
                ICONS_DIR "" ICON_PHOTO };

        const voidPtr_t functions[] =
            { updateTimeline, homeTimeline, mentionsTimeline, foo, foo, foo, foo };

        int i;
        for (i = 0; i < 5; i++)
          {
            GtkWidget *icon = gtk_image_new_from_file(icons[i]);
            GtkToolItem *item = gtk_tool_button_new(icon, titles[i]);

            gtk_toolbar_insert(GTK_TOOLBAR (toolbar), item, i);
            g_signal_connect(G_OBJECT (item), "clicked",
                G_CALLBACK (functions[i]), NULL);

          }
        gtk_toolbar_set_style(GTK_TOOLBAR (toolbar), GTK_TOOLBAR_ICONS);
        gtk_toolbar_get_icon_size(GTK_TOOLBAR (toolbar) );
      }
  }

  void
  init_statusbar(string_t msg)
  {
    if (!statusbar)
      {
        statusbar = gtk_statusbar_new();
        gtk_toolbar_set_style(GTK_TOOLBAR (toolbar), GTK_TOOLBAR_ICONS);

        gtk_statusbar_push(GTK_STATUSBAR (statusbar), 0, msg);
      }
  }

  void
  init_charbar(string_t msg)
  {
    if (!charBar)
      {
        charBar = gtk_statusbar_new();
        gtk_toolbar_set_style(GTK_TOOLBAR (toolbar), GTK_TOOLBAR_ICONS);
        gtk_statusbar_push(GTK_STATUSBAR (charBar), 0, msg);
      }
  }

  void
  init_text_area()
  {
    if (!scroll)
      {
        scroll = gtk_scrolled_window_new(NULL, NULL );

        // TextArea
        GtkWidget *text = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW (text), TRUE);

        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (text), GTK_WRAP_WORD_CHAR);

        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (text) );
        gtk_text_buffer_set_text(buffer, "\0", -1);

        g_signal_connect(buffer, "changed", G_CALLBACK (updateStatusBar),
            charBar);
        g_signal_connect(text, "key-press-event", G_CALLBACK (gtkSendTweet),
            buffer);

        gtk_container_add(GTK_CONTAINER (scroll), text);
      }

  }

  void
  init_box()
  {
    if (!box)
      box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  }

  string_t downloadAvatar(string_t url)
  {

    string_t avatarName=NULL;

    if(url)
      {

        debug("url: %s", url);
        string_t filename = fileNameFromUrl(url);

        if(filename)
          {
            asprintf(&avatarName, "%s/%s",progPath->avatarDir, filename);

            if(avatarName){
                debug("avatarName %s",avatarName);

                FILE *fp=fopen(avatarName,"r");
                if(!fp)
                  getFileCURL(url, avatarName);


                if(fp)
                  fclose(fp);

            }
          }

      }


    return avatarName;
  }


  void
  init_timeline(timeline_t timeline)
  {
    gtk_container_remove(GTK_CONTAINER(table),scrolled_window);
    scrolled_window = gtk_scrolled_window_new(NULL, NULL );
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled_window),
        GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);

    tableTW = gtk_table_new(1, 3, TRUE);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW
        (scrolled_window), tableTW);



    int cols = 0, rows = 0;

    for (cols = 0; cols < MAX_NUM_TWEETS; rows = rows + 4, cols++)
      {

        if(timeline.statuses[cols].user.profile_image_url)
          {
            GdkPixbuf *image=NULL;

            string_t avatarName=downloadAvatar(timeline.statuses[cols].user.profile_image_url);

            if(avatarName)
              image = gdk_pixbuf_new_from_file_at_scale(
                  avatarName, AVATAR_SIZE, AVATAR_SIZE, TRUE,
                  NULL );

            else
              image = gdk_pixbuf_new_from_file_at_scale(
                  ICONS_DIR "" ICON_DEFAULT_PROFILE, AVATAR_SIZE, AVATAR_SIZE, TRUE,
                  NULL );

            GtkWidget *avatar = gtk_image_new_from_pixbuf(image);
            gtk_table_attach(GTK_TABLE (tableTW), avatar, 0, 1, rows, rows + 3,
                GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 0);

            g_object_unref (image);
          }

        if (timeline.statuses[cols].user.profile_image
            || timeline.statuses[cols].user.screen_name
            || timeline.statuses[cols].text || timeline.statuses[cols].created_at)
          {
            string_t tweet = NULL;
            asprintf(&tweet, "@%s:\n%s\n[%s]\n",
                timeline.statuses[cols].user.screen_name,
                timeline.statuses[cols].text, timeline.statuses[cols].created_at);
            debug ("TIMELINE: %s", tweet);

            GtkWidget *gtweet = gtk_text_view_new();
            gtk_text_view_set_editable(GTK_TEXT_VIEW (gtweet), FALSE);
            gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW (gtweet), FALSE);
            GtkTextBuffer *tweetBuf = gtk_text_view_get_buffer(
                GTK_TEXT_VIEW (gtweet) );
            gtk_text_buffer_set_text(tweetBuf, tweet, -1);
            gtk_table_attach(GTK_TABLE (tableTW), gtweet, 1, 10, rows, rows + 3,
                GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 0);
          }
        else
          rows = rows - 4;
      }

    gtk_table_attach(GTK_TABLE (table), scrolled_window, 0, 3, 0, 7,
        GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);

    refreshWindow();

  }

  void
  init_table()
  {
    if (!table)
      {
        table = gtk_table_new(9, 3, TRUE);
      }
  }

  void
  startMainWindow()
  {
    if (!window)
      {

        init_main_window();
        init_table();
        init_statusbar(PROG_NAME);
        init_toolbar();
        init_charbar("140");
        init_text_area();
        init_box();

        gtk_box_pack_end(GTK_BOX (box), statusbar, FALSE, FALSE, 0);
        //gtk_box_pack_end (GTK_BOX (box), toolbar, FALSE, FALSE, 0);
        gtk_box_pack_end(GTK_BOX (box), charBar, FALSE, FALSE, 0);

        gtk_table_attach(GTK_TABLE (table), toolbar, 0, 3, 7, 8,
            GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
        gtk_table_attach(GTK_TABLE (table), scroll, 0, 3, 8, 9,
            GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
        gtk_box_pack_end(GTK_BOX (box), table, TRUE, TRUE, 0);

        gtk_container_add(GTK_CONTAINER (window), box);

        g_signal_connect(G_OBJECT (window), "delete-event",
            G_CALLBACK (gtk_widget_hide), NULL);

      }

    gtk_widget_show_all(window);
  }

  static void
  leftClick(GtkStatusIcon * icon, gpointer data)
  {

    StartGUI();
  }

  void
  onQuit()
  {

    if (user)
      uninitUser(user);

    if (progPath)
      uninitProgPath(progPath);

    gtk_main_quit();
  }

  static void
  rightClick(GtkStatusIcon * icon, guint button, guint activate_time,
      gpointer data)
  {

    GtkWidget *menu;

    const string_t titles[] =
        { "Update", "Settings", "Version", "About", "Quit" };
    const string_t icons[] =
        { ICONS_DIR "" ICON_UPDATE_TRAYICON, ICONS_DIR "" ICON_SETTINGS,
            ICONS_DIR "" ICON_UPGRADE, ICONS_DIR "" ICON_STAR,
            ICONS_DIR "" ICON_CLOSE };
    const voidPtr_t functions[] =
        { updateTimeline, loadWindowProperty, startVersionWindow,
            startCreditsDialog, onQuit };

    menu = gtk_menu_new();

    int i;
    for (i = 0; i < 5; i++)
      {
        GtkWidget *item = gtk_image_menu_item_new_with_label(titles[i]);
        GtkWidget *icon = gtk_image_new_from_file(icons[i]);
        gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM (item), icon);
        g_signal_connect(G_OBJECT (item), "activate", G_CALLBACK (functions[i]),
            NULL);
        gtk_menu_shell_append(GTK_MENU_SHELL (menu), item);
      }

    gtk_widget_show_all(menu);
    gtk_menu_popup(GTK_MENU (menu), NULL, NULL, gtk_status_icon_position_menu,
        icon, button, activate_time);
  }

  void
  startTrayIcon()
  {

    GtkStatusIcon *icon;

    icon = gtk_status_icon_new_from_file(ICONS_DIR "" ICON_FAVICON);

    g_signal_connect(G_OBJECT (icon), "activate", G_CALLBACK (leftClick), NULL);
    g_signal_connect(G_OBJECT (icon), "popup-menu", G_CALLBACK (rightClick),
        NULL);

  }

  void
  switchTimeline()
  {
    timelineType_t timelineType;

    switch (swTimeline)
    {

    case 0:
      timelineType = public_timeline;
      break;

    case 1:
      timelineType = home_timeline;
      break;

    case 2:
      timelineType = mentions;
      break;

    case 3:
      timelineType = friends_timeline;
      break;

    case 4:
      timelineType = user_timeline;
      break;

    default:
      timelineType = public_timeline;
      break;
    }

    string_t rawTimeline = getRawTimeline(twitterURLS, timelineType, user);
    timeline_t timeline = readTimeLine(rawTimeline);

    init_timeline(timeline);

    int i = 0;
    for (i = 0; i < MAX_NUM_TWEETS; i++)
      {
        uninitStatus(timeline.statuses[i]);
      }

  }

  void
  updateTimeline()
  {
    switchTimeline();
  }

  void
  homeTimeline()
  {

    swTimeline = 1;
    switchTimeline();
  }

  void
  mentionsTimeline()
  {

    swTimeline = 2;
    switchTimeline();
  }

  void
  loadWindowProperty()
  {
    startWindowProperties(user, window);

    user_t *old = user;
    user = NULL;
    Connect();

    uninitUser(old);
  }

#ifdef __cplusplus
}
#endif
