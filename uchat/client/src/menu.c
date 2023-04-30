#include "../inc/header.h"

void on_menu_clicked(GtkButton *b, gpointer data)
{
    g_print("button 'Menu'\n");

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "resources/chat.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    menu_window = GTK_WIDGET(gtk_builder_get_object(builder, "menu_window"));
    menu_label = GTK_WIDGET(gtk_builder_get_object(builder, "menu_label"));
    menu_name_label = GTK_LABEL(gtk_builder_get_object(builder, "menu_name_label"));
    profile_image = GTK_IMAGE(gtk_builder_get_object(builder, "profile_image"));
    logout_button = GTK_WIDGET(gtk_builder_get_object(builder, "log_out"));
    change_password_button = GTK_WIDGET(gtk_builder_get_object(builder, "change_password"));
    change_image_button = GTK_WIDGET(gtk_builder_get_object(builder, "change_image"));
    delete_account = GTK_WIDGET(gtk_builder_get_object(builder, "delete_account"));

    gtk_window_set_title(GTK_WINDOW(menu_window), "Menu");

    gtk_builder_connect_signals(builder, NULL);

    load_image("resources/basic.png", profile_image, 150, 150);
    gtk_label_set_text(menu_name_label, username);

    gtk_widget_show_all(menu_window);

    g_object_unref(builder);
}

void on_log_out_clicked(GtkButton *b, gpointer data)
{
    g_print("button 'Log out'\n");

    GtkWidget *dialog;
    gint result;

    dialog = gtk_dialog_new_with_buttons("Warning",
                                         GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL,
                                         "_Yes",
                                         GTK_RESPONSE_OK,
                                         "_No",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    GtkWidget *label = gtk_label_new("\nAre you sure you want to log out?\n");
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    gtk_widget_show_all(dialog);
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    switch (result)
    {
    case GTK_RESPONSE_OK:
        g_print("Yes button clicked\n");
        remove("resources/cash.bin");
        gtk_widget_hide(chat_window);
        gtk_tree_selection_unselect_all(chats_selection);
        gtk_tree_selection_unselect_all(messages_selection);
        g_source_remove(timer_id);
        show_login_window();
        gtk_widget_destroy(menu_window);
        break;
    case GTK_RESPONSE_CANCEL:
        g_print("No button clicked\n");
        break;
    default:
        g_print("Exit button clicked\n");
        break;
    }

    gtk_widget_destroy(dialog);
}

void on_change_password_clicked(GtkButton *button, gpointer user_data)
{
    g_print("button 'Change password'\n");

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "resources/chat.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    change_password_window = GTK_WIDGET(gtk_builder_get_object(builder, "change_password_window"));
    gtk_window_set_title(GTK_WINDOW(change_password_window), "Change password");
    change_password_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "change_password_dialog"));
    current_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "current_password"));
    new_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "new_password"));
    confirm_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "confirm_new_password"));
    change_password_error_label = GTK_WIDGET(gtk_builder_get_object(builder, "change_password_error_label"));
    cancel_change_button = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_change"));
    save_button = GTK_WIDGET(gtk_builder_get_object(builder, "save"));

    gtk_builder_connect_signals(builder, NULL);

    gtk_entry_set_text(GTK_ENTRY(new_password_entry), "");
    gtk_entry_set_text(GTK_ENTRY(confirm_password_entry), "");

    gtk_widget_show_all(change_password_window);

    g_object_unref(builder);
}

void update_cash_bin(const char *username, const char *new_password)
{
    FILE *file = fopen("resources/cash.bin", "r+b");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    while (!feof(file))
    {
        char line[1024];
        fgets(line, 1024, file);

        char *u = strtok(line, "|");
        char *p = strtok(NULL, "\n");

        if (u && p && strcmp(u, username) == 0)
        {
            fseek(file, -strlen(u) - strlen(p) - 1, SEEK_CUR);
            fprintf(file, "%s|%s", username, new_password);
            break;
        }
    }

    fclose(file);
}

void on_save_clicked(GtkButton *button, gpointer user_data)
{
    const char *new_password = gtk_entry_get_text(GTK_ENTRY(new_password_entry));
    const char *confirm_password = gtk_entry_get_text(GTK_ENTRY(confirm_password_entry));
    const char *current_password = gtk_entry_get_text(GTK_ENTRY(current_password_entry));

    if (strcmp(new_password, confirm_password) != 0)
    {
        gtk_label_set_text(GTK_LABEL(change_password_error_label), "Passwords do not match");
        return;
    }
    else if (strcmp(current_password, password) != 0)
    {
        gtk_label_set_text(GTK_LABEL(change_password_error_label), "Incorrect current password");
        return;
    }
    else if (strlen(new_password) < 8)
    {
        gtk_label_set_text(GTK_LABEL(change_password_error_label), "Password must be at least 8 characters long!");
        return;
    }
    else if (contains_non_english_letters(new_password))
    {
        gtk_label_set_text(GTK_LABEL(change_password_error_label), "Password must not contain forbidden symbols!");
        return;
    }

    change_password(username, (char *)new_password);
    update_cash_bin(username, new_password);

    gtk_entry_set_text(GTK_ENTRY(new_password_entry), "");
    gtk_entry_set_text(GTK_ENTRY(confirm_password_entry), "");
    gtk_widget_destroy(change_password_window);
}

void on_cancel_change_clicked(GtkButton *b, gpointer data)
{
    g_print("button 'Cancel'\n");
    gtk_widget_destroy(change_password_window);
}

void on_delete_account_clicked(GtkButton *button, gpointer user_data)
{
    g_print("button 'Delete account'\n");

    GtkWidget *dialog;
    gint result;

    dialog = gtk_message_dialog_new(
        GTK_WINDOW(user_data),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_OK_CANCEL,
        "Are you sure you want to delete your account? This action cannot be undone.");

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    result = gtk_dialog_run(GTK_DIALOG(dialog));

    switch (result)
    {
    case GTK_RESPONSE_OK:
        g_print("Yes button clicked\n");
        remove("resources/cash.bin");
        del_user(username);
        gtk_widget_hide(chat_window);
        gtk_tree_selection_unselect_all(chats_selection);
        gtk_tree_selection_unselect_all(messages_selection);
        g_source_remove(timer_id);
        show_login_window();
        gtk_widget_destroy(menu_window);
        break;
    case GTK_RESPONSE_CANCEL:
        g_print("No button clicked\n");
        break;
    default:
        g_print("Exit button clicked\n");
        break;
    }

    gtk_widget_destroy(dialog);
}

void load_image(const char *filename, GtkImage *image, int width, int height)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), scaled_pixbuf);
    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);
}

void on_change_image_clicked(GtkButton *button, gpointer user_data)
{
    g_print("button 'Change image'\n");

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "resources/chat.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    change_image_window = GTK_WIDGET(gtk_builder_get_object(builder, "change_image_window"));
    choose_file_button = GTK_WIDGET(gtk_builder_get_object(builder, "choose_file"));
    save_choose_button = GTK_WIDGET(gtk_builder_get_object(builder, "save_choose"));
    cancel_choose_button = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_choose"));
    profile_image1 = GTK_IMAGE(gtk_builder_get_object(builder, "profile_image1"));

    gtk_builder_connect_signals(builder, NULL);

    //g_signal_connect(choose_file_button, "clicked", G_CALLBACK(on_choose_file_clicked), NULL);
    //g_signal_connect(save_choose_button, "clicked", G_CALLBACK(on_save_choose_clicked), NULL);
    //g_signal_connect(cancel_choose_button, "clicked", G_CALLBACK(on_cancel_choose_clicked), NULL);

    load_image("resources/profile_image.png", profile_image1, 150, 150);

    gtk_widget_show_all(change_image_window);
    g_object_unref(builder);
}

void on_choose_file_clicked(GtkButton *button, gpointer user_data)
{
    g_print("button 'Choose file'\n");

    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(change_image_window), GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        load_image(filename, profile_image1, 150, 150);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void on_save_choose_clicked(GtkButton *button, gpointer user_data)
{
    g_print("button 'Save'\n");

    GdkPixbuf *pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(profile_image1));
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 150, 150, GDK_INTERP_BILINEAR);
    char *filename = "resources/profile_image.png";
    gdk_pixbuf_save(scaled_pixbuf, filename, "png", NULL, NULL);
    load_image("resources/profile_image.png", profile_image, 150, 150);

    // Save the image path to the database

    gtk_widget_destroy(change_image_window);
}

void update_profile_image()
{
    load_image("resources/profile_image.png", profile_image, 150, 150);

    // Update the image path in the database

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(menu_window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Profile image updated");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_cancel_choose_clicked(GtkButton *button, gpointer user_data)
{
    g_print("button 'Cancel'\n");
    gtk_widget_destroy(change_image_window);
}
