#include "../inc/header.h"

void scroll_to_bottom()
{
    GtkAdjustment *vadjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(messages_scroller));
    gtk_adjustment_set_value(vadjustment, gtk_adjustment_get_upper(vadjustment));
    gtk_widget_show_all(GTK_WIDGET(messages_scroller));
}

gboolean scroll_delayed(GtkWidget *widget)
{
    scroll_to_bottom();
    return G_SOURCE_REMOVE;
}

static gboolean on_enter_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    if (event->keyval == GDK_KEY_Return && (event->state & GDK_CONTROL_MASK) == 0)
    {
        gtk_button_clicked(GTK_BUTTON(user_data));
        return TRUE;
    }
    return FALSE;
}

void delete_chat(GtkMenuItem *menuitem, gpointer data)
{
    g_print("Button 'Delete chat'\n");
    GtkWidget *dialog;
    gint result;

    gchar *value;
    GtkTreeIter iter;
    GtkTreeModel *model;

    dialog = gtk_dialog_new_with_buttons("Warning",
                                         GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL,
                                         "_Yes",
                                         GTK_RESPONSE_OK,
                                         "_No",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    // Додавання елементів управління до діалогового вікна
    GtkWidget *label = gtk_label_new("\nAre you sure you want to delete this chat?\nThis action will also delete all messages of this chat.\n");
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    // Відображення діалогового вікна
    gtk_widget_show_all(dialog);

    // Відображення діалогового вікна та отримання коду відповіді
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    // Обробка відповіді користувача
    switch (result)
    {
    case GTK_RESPONSE_OK:
        g_print("Yes button clicked\n");
        del_chat(selected_chat);
        gtk_tree_selection_unselect_all(chats_selection);
        gtk_label_set_text(GTK_LABEL(chat_label), "Select a chat to begin!");
        break;
    case GTK_RESPONSE_CANCEL:
        g_print("No button clicked\n");
        break;
    default:
        g_print("Exit button clicked\n");
        break;
    }

    // Закриття діалогового вікна
    gtk_widget_destroy(dialog);
}

gboolean on_chats_list_button_press_event(GtkWidget *treeview, GdkEventButton *event, gpointer data)
{
    GtkTreePath *path;
    GtkTreeViewColumn *column;
    GtkTreeModel *model;
    if (event->button == GDK_BUTTON_SECONDARY)
    {

        if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint)event->x, (gint)event->y, &path, &column, NULL, NULL) && gtk_tree_selection_get_selected(GTK_TREE_SELECTION(chats_selection), &model, NULL))
        {
            GtkWidget *menu = GTK_WIDGET(data);
            gtk_widget_show_all(menu);
            if (GTK_IS_MENU(menu))
            {
                gtk_menu_popup_at_pointer(GTK_MENU(menu), NULL);
            }
        }
    }
    if (event->button == GDK_BUTTON_PRIMARY)
    {
        if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint)event->x, (gint)event->y, &path, &column, NULL, NULL) && gtk_tree_selection_get_selected(GTK_TREE_SELECTION(chats_selection), &model, NULL))
        {
            // nothin
        }
        else
        {
            if (!being_edited)
            {
                gtk_tree_selection_unselect_all(messages_selection);
            }
        }
    }

    return FALSE;
}

void copy_message(GtkMenuItem *menuitem, gpointer data)
{
    // code to edit the selected message
    g_print("Button 'Copy message'\n");
    GtkClipboard *clipboard;
    clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    gtk_clipboard_clear(clipboard);
    gtk_clipboard_set_text(clipboard, selected_message_text, -1);
}

void edit_message(GtkMenuItem *menuitem, gpointer data)
{
    // code to edit the selected message
    g_print("Button 'Edit message'\n");
    being_edited = true;
    strcpy(message_old, message_buffer);
    gtk_editable_delete_text(GTK_EDITABLE(messages_entry), 0, -1);
    gtk_entry_set_text(GTK_ENTRY(messages_entry), selected_message_text);
    gtk_widget_show(edit_label);
}

void delete_message(GtkMenuItem *menuitem, gpointer data)
{
    // code to delete the selected message
    g_print("Button 'Delete message'\n");
    GtkWidget *dialog;
    gint result;

    // Створення діалогового вікна
    dialog = gtk_dialog_new_with_buttons("Warning",
                                         GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL,
                                         "_Yes",
                                         GTK_RESPONSE_OK,
                                         "_No",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    // Додавання елементів управління до діалогового вікна
    GtkWidget *label = gtk_label_new("\nAre you sure you want to delete this message?\n");
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), label);

    // Відображення діалогового вікна
    gtk_widget_show_all(dialog);

    // Відображення діалогового вікна та отримання коду відповіді
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    // Обробка відповіді користувача
    switch (result)
    {
    case GTK_RESPONSE_OK:
        g_print("Yes button clicked\n");
        del_message(selected_chat, selected_message_id);
        gtk_tree_selection_unselect_all(messages_selection);
        break;
    case GTK_RESPONSE_CANCEL:
        g_print("No button clicked\n");
        break;
    default:
        g_print("Exit button clicked\n");
        break;
    }

    // Закриття діалогового вікна
    gtk_widget_destroy(dialog);
}

gboolean on_messages_list_button_press_event(GtkWidget *treeview, GdkEventButton *event, gpointer data)
{
    GtkTreePath *path;
    GtkTreeViewColumn *column;
    GtkTreeModel *model;

    if (event->button == GDK_BUTTON_SECONDARY)
    {

        if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint)event->x, (gint)event->y, &path, &column, NULL, NULL) && gtk_tree_selection_get_selected(GTK_TREE_SELECTION(messages_selection), &model, NULL))
        {
            GtkWidget *menu = GTK_WIDGET(data);
            GList *children = gtk_container_get_children(GTK_CONTAINER(menu));
            GtkWidget *copy_item = GTK_WIDGET(g_list_nth_data(children, 0));
            GtkWidget *edit_item = GTK_WIDGET(g_list_nth_data(children, 1));
            GtkWidget *delete_item = GTK_WIDGET(g_list_nth_data(children, 2));
            g_list_free(children);
            // Show/hide "Edit" and "Delete" options based on whether the selected message was sent by the user
            if (strcmp(selected_message_sender, username) != 0)
            {
                gtk_widget_show(copy_item);
                gtk_widget_hide(edit_item);
                gtk_widget_hide(delete_item);
                if (GTK_IS_MENU(menu))
                {
                    gtk_menu_popup_at_pointer(GTK_MENU(menu), NULL);
                }
            }
            else
            {
                gtk_widget_show_all(menu);
                if (GTK_IS_MENU(menu))
                {
                    gtk_menu_popup_at_pointer(GTK_MENU(menu), NULL);
                }
            }
        }
    }
    if (event->button == GDK_BUTTON_PRIMARY)
    {
        if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint)event->x, (gint)event->y, &path, &column, NULL, NULL) && gtk_tree_selection_get_selected(GTK_TREE_SELECTION(messages_selection), &model, NULL))
        {
            // nothin
        }
        else
        {
            if (!being_edited)
            {
                gtk_tree_selection_unselect_all(messages_selection);
            }
        }
    }

    return FALSE;
}

static gboolean chats_store_update()
{

    static GtkTreePath *selected_chat_path = NULL;
    static GtkTreePath *selected_message_path = NULL;

    GtkTreeModel *chat_model;
    GtkTreeModel *message_model;
    GtkTreeIter chat_iter;
    GtkTreeIter message_iter;

    // Get the selected chat and its path
    if (gtk_tree_selection_get_selected(chats_selection, &chat_model, &chat_iter))
    {
        selected_chat_path = gtk_tree_model_get_path(chat_model, &chat_iter);
    }
    else
    {
        selected_chat_path = NULL;
    }

    // Get the selected message and its path
    if (gtk_tree_selection_get_selected(messages_selection, &message_model, &message_iter))
    {
        selected_message_path = gtk_tree_model_get_path(message_model, &message_iter);
    }
    else
    {
        selected_message_path = NULL;
    }

    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(messages_scroller));

    gdouble current_position = gtk_adjustment_get_value(adjustment);
    gdouble maximum_position = gtk_adjustment_get_upper(adjustment) - gtk_adjustment_get_page_size(adjustment);

    // Update the GtkListStore and GtkTreeView for chats
    gtk_list_store_clear(messages_store);
    gtk_list_store_clear(chats_store);
    fill_chats_list(username, chats_store);
    gtk_tree_view_set_model(chats_list, GTK_TREE_MODEL(chats_store));

    if (current_position >= maximum_position - 10)
    {
        g_timeout_add(100, (GSourceFunc)scroll_delayed, messages_scroller);
    }

    // Select the previously selected chat and message if they still exist
    if (selected_chat_path && gtk_tree_model_get_iter(chat_model, &chat_iter, selected_chat_path))
    {
        gtk_tree_selection_select_iter(chats_selection, &chat_iter);
    }
    if (selected_message_path && gtk_tree_model_get_iter(message_model, &message_iter, selected_message_path))
    {
        gtk_tree_selection_select_iter(messages_selection, &message_iter);
    }

    // Free the paths
    if (selected_chat_path)
    {
        gtk_tree_path_free(selected_chat_path);
    }
    if (selected_message_path)
    {
        gtk_tree_path_free(selected_message_path);
    }

    // Return TRUE to keep the timer running
    return TRUE;
}

void show_chat_window(void)
{

    builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, "resources/chat.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    // chats_store
    chats_list = GTK_TREE_VIEW(gtk_builder_get_object(builder, "chats_list"));
    chats_store = gtk_list_store_new(N_CHATS_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    fill_chats_list(username, chats_store);

    // Set the GtkListStore as the model for the TreeView
    gtk_tree_view_set_model(chats_list, GTK_TREE_MODEL(chats_store));

    // Create the GtkTreeViewColumns for each column of data
    GtkTreeViewColumn *chat_col0 = gtk_tree_view_column_new_with_attributes("ID", gtk_cell_renderer_text_new(), "text", CHAT_ID_COLUMN, NULL);
    gtk_tree_view_append_column(chats_list, chat_col0);
    gtk_tree_view_column_set_visible(chat_col0, FALSE);

    GtkTreeViewColumn *chat_col1 = gtk_tree_view_column_new_with_attributes("Chatname", gtk_cell_renderer_text_new(), "text", CHAT_CHATNAME_COLUMN, NULL);
    gtk_tree_view_append_column(chats_list, chat_col1);
    gtk_tree_view_column_set_visible(chat_col1, FALSE);

    GtkTreeViewColumn *chat_col2 = gtk_tree_view_column_new_with_attributes("Sender", gtk_cell_renderer_text_new(), "text", CHAT_SENDER_COLUMN, NULL);
    gtk_tree_view_append_column(chats_list, chat_col2);
    gtk_tree_view_column_set_visible(chat_col2, FALSE);

    GtkTreeViewColumn *chat_col3 = gtk_tree_view_column_new_with_attributes("Receiver", gtk_cell_renderer_text_new(), "text", CHAT_RECEIVER_COLUMN, NULL);
    gtk_tree_view_append_column(chats_list, chat_col3);
    gtk_tree_view_column_set_visible(chat_col3, FALSE);

    GtkTreeViewColumn *chat_col4 = gtk_tree_view_column_new_with_attributes("Chats:", gtk_cell_renderer_text_new(), "text", CHAT_CHATS_COLUMN, NULL);
    gtk_tree_view_append_column(chats_list, chat_col4);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(chats_list), FALSE);

    // context menu for chats
    GtkWidget *chats_menu = gtk_menu_new();

    GtkWidget *delete_item_chat = gtk_menu_item_new_with_label("Delete chat");
    g_signal_connect(delete_item_chat, "activate", G_CALLBACK(delete_chat), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(chats_menu), delete_item_chat);

    // Set up the TreeView to show the context menu
    gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(chats_list), FALSE);
    gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(chats_list), FALSE);
    gtk_tree_view_set_enable_search(GTK_TREE_VIEW(chats_list), FALSE);
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(chats_list), GTK_TREE_VIEW_GRID_LINES_NONE);
    gtk_tree_view_set_hover_selection(GTK_TREE_VIEW(chats_list), FALSE);
    g_signal_connect(chats_list, "button-press-event", G_CALLBACK(on_chats_list_button_press_event), chats_menu);

    // messages_store
    messages_list = GTK_TREE_VIEW(gtk_builder_get_object(builder, "messages_list"));
    messages_store = gtk_list_store_new(N_MESSAGES_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    // Set the GtkListStore as the model for the TreeView
    gtk_tree_view_set_model(messages_list, GTK_TREE_MODEL(messages_store));

    GtkTreeViewColumn *msg_col0 = gtk_tree_view_column_new_with_attributes("ID:", gtk_cell_renderer_text_new(), "text", MESSAGE_ID_COLUMN, NULL);
    gtk_tree_view_append_column(messages_list, msg_col0);
    gtk_tree_view_column_set_visible(msg_col0, FALSE);

    GtkTreeViewColumn *msg_col1 = gtk_tree_view_column_new_with_attributes("Time:", gtk_cell_renderer_text_new(), "text", MESSAGE_TIME_COLUMN, NULL);
    gtk_tree_view_append_column(messages_list, msg_col1);

    GtkTreeViewColumn *msg_col2 = gtk_tree_view_column_new_with_attributes("Sender:", gtk_cell_renderer_text_new(), "text", MESSAGE_SENDER_COLUMN, NULL);
    gtk_tree_view_append_column(messages_list, msg_col2);

    GtkTreeViewColumn *msg_col3 = gtk_tree_view_column_new_with_attributes("Message:", gtk_cell_renderer_text_new(), "text", MESSAGE_TEXT_COLUMN, NULL);
    gtk_tree_view_append_column(messages_list, msg_col3);

    gtk_tree_view_column_set_expand(msg_col3, TRUE);
    gtk_tree_view_column_set_max_width(msg_col3, G_MAXINT);

    GtkTreeViewColumn *msg_col4 = gtk_tree_view_column_new_with_attributes("", gtk_cell_renderer_text_new(), "text", MESSAGE_IS_EDITED_COLUMN, NULL);
    gtk_tree_view_append_column(messages_list, msg_col4);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(messages_list), FALSE);

    // context menu for messages
    GtkWidget *messages_menu = gtk_menu_new();

    GtkWidget *copy_item = gtk_menu_item_new_with_label("Copy message");
    g_signal_connect(copy_item, "activate", G_CALLBACK(copy_message), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(messages_menu), copy_item);

    GtkWidget *edit_item = gtk_menu_item_new_with_label("Edit message");
    g_signal_connect(edit_item, "activate", G_CALLBACK(edit_message), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(messages_menu), edit_item);

    GtkWidget *delete_item = gtk_menu_item_new_with_label("Delete message");
    g_signal_connect(delete_item, "activate", G_CALLBACK(delete_message), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(messages_menu), delete_item);

    // Set up the TreeView to show the context menu
    gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(messages_list), FALSE);
    gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(messages_list), FALSE);
    gtk_tree_view_set_enable_search(GTK_TREE_VIEW(messages_list), FALSE);
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(messages_list), GTK_TREE_VIEW_GRID_LINES_NONE);
    gtk_tree_view_set_hover_selection(GTK_TREE_VIEW(messages_list), FALSE);
    g_signal_connect(messages_list, "button-press-event", G_CALLBACK(on_messages_list_button_press_event), messages_menu);

    chat_window = GTK_WIDGET(gtk_builder_get_object(builder, "chat"));
    g_signal_connect(chat_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(chat_window), "TALKIO");

    gtk_builder_connect_signals(builder, NULL);

    name_label = GTK_WIDGET(gtk_builder_get_object(builder, "name_label"));
    gtk_label_set_text(GTK_LABEL(name_label), username);

    chat_label = GTK_WIDGET(gtk_builder_get_object(builder, "chat_label"));
    edit_label = GTK_WIDGET(gtk_builder_get_object(builder, "edit_label"));

    logout_button = GTK_WIDGET(gtk_builder_get_object(builder, "log_out"));
    newchat_button = GTK_WIDGET(gtk_builder_get_object(builder, "new_chat"));
    enter_button = GTK_WIDGET(gtk_builder_get_object(builder, "enter_button"));

    g_signal_connect(chat_window, "key-press-event", G_CALLBACK(on_enter_press), enter_button);

    gtk_builder_connect_signals(builder, NULL);

    chats_selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "chats_selection"));
    messages_selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "messages_selection"));
    messages_scroller = GTK_SCROLLED_WINDOW(gtk_builder_get_object(builder, "messages_scroller"));
    messages_entry = GTK_WIDGET(gtk_builder_get_object(builder, "messages_entry"));

    timer_id = g_timeout_add(1000, (GSourceFunc)chats_store_update, chats_store);

    gtk_widget_show_all(chat_window);
    gtk_widget_hide(edit_label);
}

void on_chats_selection_changed(GtkTreeSelection *s, gpointer data)
{
    gchar *value;
    GtkTreeIter iter;
    GtkTreeModel *model;
    char a[NAME_LENGTH] = "";

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(s), &model, &iter) == FALSE)
        return;

    gtk_tree_model_get(model, &iter, CHAT_CHATNAME_COLUMN, &value, -1);
    strcpy(selected_chat, value);

    gtk_list_store_clear(messages_store);
    fill_messages_list(selected_chat, messages_store);

    gtk_tree_model_get(model, &iter, CHAT_SENDER_COLUMN, &value, -1);
    strcpy(a, value);
    if (strcmp(a, username) == 0)
    {
        gtk_tree_model_get(model, &iter, CHAT_RECEIVER_COLUMN, &value, -1);
        strcpy(a, value);
    }

    gtk_tree_model_get(model, &iter, CHAT_ID_COLUMN, &value, -1);
    if (selected_chat_id != atoi(value))
    {
        selected_chat_id = atoi(value);
        gtk_label_set_text(GTK_LABEL(chat_label), a);
        g_timeout_add(100, (GSourceFunc)scroll_delayed, messages_scroller);
        if (being_edited)
        {
            gtk_entry_set_text(GTK_ENTRY(messages_entry), message_old);
            gtk_widget_hide(edit_label);
            being_edited = false;
        }
        else
        {
            gtk_entry_set_text(GTK_ENTRY(messages_entry), message_buffer);
        }
    }
}

void on_new_chat_clicked(GtkButton *b, gpointer data)
{
    g_print("button 'Add chat'\n");

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "resources/chat.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    users_list = GTK_TREE_VIEW(gtk_builder_get_object(builder, "users_list"));
    users_store = gtk_list_store_new(N_USERS_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);

    // Set the GtkListStore as the model for the TreeView
    gtk_tree_view_set_model(users_list, GTK_TREE_MODEL(users_store));

    // Create the GtkTreeViewColumns for each column of data
    GtkTreeViewColumn *user_col0 = gtk_tree_view_column_new_with_attributes("ID", gtk_cell_renderer_text_new(), "text", USER_ID_COLUMN, NULL);
    gtk_tree_view_append_column(users_list, user_col0);
    gtk_tree_view_column_set_visible(user_col0, FALSE);

    GtkTreeViewColumn *user_col1 = gtk_tree_view_column_new_with_attributes("Users", gtk_cell_renderer_text_new(), "text", USER_NAME_COLUMN, NULL);
    gtk_tree_view_append_column(users_list, user_col1);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(users_list), FALSE);

    add_chat_window = GTK_WIDGET(gtk_builder_get_object(builder, "add_chat"));
    gtk_window_set_title(GTK_WINDOW(add_chat_window), "New Chat");

    gtk_builder_connect_signals(builder, NULL);

    users_selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "users_selection"));

    add_chat_label = GTK_WIDGET(gtk_builder_get_object(builder, "add_chat_label"));
    users_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "users_entry"));
    selected_username[0] = '\0';

    gtk_widget_show_all(add_chat_window);
}

void on_create_chat_clicked(GtkButton *b, gpointer data)
{
    g_print("button 'Create chat'\n");
    if (check_chat(username, selected_username))
    {
        gtk_label_set_text(GTK_LABEL(add_chat_label), (const gchar *)"This chat already exists!");
    }
    else if (selected_username[0] == '\0')
    {
        gtk_label_set_text(GTK_LABEL(add_chat_label), (const gchar *)"Select a user to proceed!");
    }
    else
    {
        add_chat(username, selected_username);
        gtk_widget_hide(add_chat_window);
    }
}

void on_cancel_clicked(GtkButton *b, gpointer data)
{
    g_print("button 'Cancel'\n");
    gtk_widget_hide(add_chat_window);
}

void on_users_entry_search_changed(GtkSearchEntry *s)
{
    const gchar *search;
    GtkTreeIter iter;

    GtkTreeModel *model = gtk_tree_view_get_model(users_list);

    search = gtk_entry_get_text(GTK_ENTRY(s));

    gtk_label_set_text(GTK_LABEL(add_chat_label), (const gchar *)"Find a user to chat with");

    if (search[0] == '\0')
    {
        gtk_list_store_clear(users_store);
        selected_username[0] = '\0';
    }
    else
    {
        gtk_list_store_clear(users_store);
        fill_users_list(search, username, users_store);
    }
}

void on_users_selection_changed(GtkWidget *s)
{
    gchar *value;
    GtkTreeIter iter;
    GtkTreeModel *model;

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(s), &model, &iter) == FALSE)
        return;

    gtk_tree_model_get(model, &iter, USER_NAME_COLUMN, &value, -1);
    strcpy(selected_username, value);
}

void on_messages_entry_changed(GtkEntry *e)
{
    sprintf(message_buffer, "%s", gtk_entry_get_text(e));
}

void on_messages_selection_changed(GtkWidget *s)
{
    gchar *value;
    GtkTreeIter iter;
    GtkTreeModel *model;

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(s), &model, &iter) == FALSE)
        return;

    gtk_tree_model_get(model, &iter, MESSAGE_TEXT_COLUMN, &value, -1);
    strcpy(selected_message_text, value);
    gtk_tree_model_get(model, &iter, MESSAGE_SENDER_COLUMN, &value, -1);
    strcpy(selected_message_sender, value);
    gtk_tree_model_get(model, &iter, MESSAGE_ID_COLUMN, &value, -1);

    if (selected_message_id != atoi(value))
    {
        selected_message_id = atoi(value);
        if (being_edited)
        {
            gtk_entry_set_text(GTK_ENTRY(messages_entry), message_old);
            gtk_widget_hide(edit_label);
            being_edited = false;
        }
        else
        {
            gtk_entry_set_text(GTK_ENTRY(messages_entry), message_buffer);
        }
    }
}

void on_enter_button_clicked(GtkButton *b, gpointer data)
{
    g_print("button 'Enter'\n");
    if (message_buffer[0] != '\0' && selected_chat[0] != '\0')
    {
        if (being_edited)
        {
            if (strcmp(selected_message_text, message_buffer) != 0)
            {
                update_message(selected_chat, selected_message_id, message_buffer);
            }
            gtk_entry_set_text(GTK_ENTRY(messages_entry), message_old);
            gtk_widget_hide(edit_label);
            being_edited = false;
        }
        else
        {
            add_message(selected_chat, username, message_buffer);
            gtk_editable_delete_text(GTK_EDITABLE(messages_entry), 0, -1);
            g_timeout_add(600, (GSourceFunc)scroll_delayed, messages_scroller);
        }
    }
}

void show_reconnect()
{
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "resources/chat.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    reconnect = GTK_WIDGET(gtk_builder_get_object(builder, "reconnect"));
    GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
    GdkPixbufAnimation *animation;

    gtk_window_set_title(GTK_WINDOW(reconnect), "Reconnecting...");

    animation = gdk_pixbuf_animation_new_from_file("resources/funi.gif", NULL);
    gtk_image_set_from_animation(GTK_IMAGE(image), animation);
}
