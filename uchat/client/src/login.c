#include "../inc/header.h"

void show_login_window(void) {

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "resources/login.glade", &error) == 0) {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return;
    }

    login_window = GTK_WIDGET(gtk_builder_get_object(builder, "login"));
    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_title(GTK_WINDOW(login_window), "Login");

    gtk_builder_connect_signals(builder, NULL);

    error_label = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));
    info_label = GTK_WIDGET(gtk_builder_get_object(builder, "label4"));

    login_button = GTK_WIDGET(gtk_builder_get_object(builder, "log_in"));
    remember_button = GTK_WIDGET(gtk_builder_get_object(builder, "remember_me"));
    signup_button = GTK_WIDGET(gtk_builder_get_object(builder, "sign_up"));
    register_button = GTK_WIDGET(gtk_builder_get_object(builder, "register"));
    goback_button = GTK_WIDGET(gtk_builder_get_object(builder, "go_back"));
    
    name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "name_login"));
    pass_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_login"));
    register_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "name_register"));
    register_pass_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_register"));
    register_confirm_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_confirm"));

    gtk_widget_show(login_window);
}

void on_remember_toggled(GtkCheckButton *b) {
    remember_is_toggled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
}

void on_log_in_clicked(GtkButton *b, gpointer data) {
    g_print ("button 'Log in'\n");

    gtk_widget_hide(error_label);

    if (get_user(username, password) == 1) {
        if (remember_is_toggled) {
            FILE *fp;
            fp = fopen("resources/cash.bin", "w");
            if (fp == NULL) {
                printf("failed to open cash.bin\n");
            }
            else {
                char * str = to_serv(username,password);
                fputs(str, fp);
                free(str);
            }
            fclose(fp);
        }
        gtk_widget_hide(login_window);
        show_chat_window();
    }
    else {
        if (is_reconecting) {
            gtk_label_set_text(GTK_LABEL(error_label), (const gchar*) "No connection to the server!");
        }
        else {
            gtk_label_set_text(GTK_LABEL(error_label), (const gchar*) "Incorrect input data!");
        }
        gtk_widget_show(error_label);
    }
}

void on_sign_up_clicked(GtkButton *b, gpointer data) {
    g_print ("button 'Sign up'\n");

    gtk_window_set_title(GTK_WINDOW(login_window), "Sign up");

    gtk_widget_hide(error_label);
    
    gtk_editable_delete_text(GTK_EDITABLE(name_entry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(pass_entry), 0, -1);

    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));

    child = GTK_WIDGET(gtk_builder_get_object(builder, "page2"));

    gtk_stack_set_visible_child (stack, child);
}

void on_register_clicked(GtkButton *b, gpointer data) {
    g_print ("button 'Register'\n");
    
    gtk_widget_show(info_label);

    if (strlen(username) < 6) {
        gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "Username must be at least 6 characters long!");
    }
    else if (contains_non_english_letters(username)) {
        gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "Username must not contain forbidden symbols!");
    }
    else if (strlen(password) < 8) {
        gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "Password must be at least 8 characters long!");
    }
    else if (contains_non_english_letters(password)) {
        gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "Password must not contain forbidden symbols!");
    }
    else if (strcmp(password, confirm) != 0) {
        gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "Passwords must be identical!");
    }
    else {
        if (check_username(username)) {
            gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "   This user already exists!");
        }
        else {
            add_user(username, password);
            if (is_reconecting) {
                gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "No connection to the server!");
            }
            else {
                gtk_label_set_text(GTK_LABEL(info_label), (const gchar*) "   Registrated successfully!");
            }
        }
    }
}

void on_go_back_clicked(GtkButton *b, gpointer data) {
    g_print ("button 'Go back'\n");

    gtk_window_set_title(GTK_WINDOW(login_window), "Login");

    gtk_editable_delete_text(GTK_EDITABLE(register_name_entry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(register_pass_entry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(register_confirm_entry), 0, -1);

    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));

    child = GTK_WIDGET(gtk_builder_get_object(builder, "page1"));

    gtk_stack_set_visible_child (stack, child);
}

void on_name_login_changed(GtkEntry *e) {
    sprintf(username, "%s", gtk_entry_get_text(e));
    gtk_widget_hide(error_label);
}

void on_password_login_changed(GtkEntry *e) {
    sprintf(password, "%s", gtk_entry_get_text(e));
    gtk_widget_hide(error_label);
}

void on_name_register_changed(GtkEntry *e) {
    sprintf(username, "%s", gtk_entry_get_text(e));
    gtk_widget_hide(info_label);
}

void on_password_register_changed(GtkEntry *e) {
    sprintf(password, "%s", gtk_entry_get_text(e));
    gtk_widget_hide(info_label);
}

void on_password_confirm_changed(GtkEntry *e) {
    sprintf(confirm, "%s", gtk_entry_get_text(e));
    gtk_widget_hide(info_label);
}
