#ifndef HEADER_H
#define HEADER_H

#define NAME_LENGTH 20
#define PASS_LENGTH 16
#define CHAT_NAME_LENGTH 42
#define MESSAGE_LENGTH 1024

#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <uuid/uuid.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <pthread.h>
#include <errno.h>
#include <sys/signal.h>
#include <sys/stat.h>

enum
{
    USER_ID_COLUMN,
    USER_NAME_COLUMN,
    N_USERS_COLUMNS
};

enum
{
    CHAT_ID_COLUMN,
    CHAT_CHATNAME_COLUMN,
    CHAT_SENDER_COLUMN,
    CHAT_RECEIVER_COLUMN,
    CHAT_CHATS_COLUMN,
    N_CHATS_COLUMNS
};

enum
{
    MESSAGE_ID_COLUMN,
    MESSAGE_TIME_COLUMN,
    MESSAGE_SENDER_COLUMN,
    MESSAGE_TEXT_COLUMN,
    MESSAGE_IS_EDITED_COLUMN,
    N_MESSAGES_COLUMNS
};

extern GtkBuilder *builder;
extern GError *error;

// login window
extern GtkWidget *login_window;
extern GtkStack *stack;
extern GtkWidget *child;
extern gboolean remember_is_toggled;

// login window buttons
extern GtkWidget *login_button;
extern GtkWidget *remember_button;
extern GtkWidget *signup_button;
extern GtkWidget *register_button;
extern GtkWidget *goback_button;

// login window entries
extern GtkWidget *name_entry;
extern GtkWidget *pass_entry;
extern GtkWidget *register_name_entry;
extern GtkWidget *register_pass_entry;
extern GtkWidget *register_confirm_entry;

// login window labels
extern GtkWidget *error_label;
extern GtkWidget *info_label;

// chat window
extern GtkWidget *chat_window;

// chat window labels
extern GtkWidget *name_label;
extern GtkWidget *chat_label;
extern GtkWidget *edit_label;
extern GtkWidget *add_chat_label;

// chat window buttons
extern GtkWidget *logout_button;
extern GtkWidget *newchat_button;
extern GtkWidget *enter_button;

// chats tree
extern GtkSearchEntry *chats_entry;
extern GtkTreeView *chats_list;
extern GtkListStore *chats_store;
extern GtkTreeSelection *chats_selection;

// messages tree
extern GtkWidget *messages_entry;
extern GtkTreeView *messages_list;
extern GtkListStore *messages_store;
extern GtkTreeSelection *messages_selection;
extern GtkScrolledWindow *messages_scroller;

// add_chat subwindow
extern GtkWidget *add_chat_window;

extern GtkWidget *new_chat_error;
extern GtkSearchEntry *users_entry;
extern GtkTreeView *users_list;
extern GtkListStore *users_store;
extern GtkTreeSelection *users_selection;

extern GtkWidget *menu_window;
extern GtkWidget *menu_label;
extern GtkImage *profile_image;
extern GtkWidget *change_password_button;
extern GtkWidget *delete_account;
extern GtkWidget *change_image_button;

extern GtkWidget *change_password_window;
extern GtkWidget *change_password_dialog;
extern GtkWidget *current_password_entry;
extern GtkWidget *new_password_entry;
extern GtkWidget *confirm_password_entry;
extern GtkWidget *change_password_error_label;
extern GtkWidget *save_button;
extern GtkWidget *cancel_change_button;

extern GtkWidget *change_image_window;
extern GtkImage *profile_image1;
extern GtkWidget *choose_file_button;
extern GtkWidget *save_choose_button;
extern GtkWidget *cancel_choose_button;

extern GtkLabel *menu_name_label;

extern char username[NAME_LENGTH];
extern char password[PASS_LENGTH];
static char confirm[PASS_LENGTH] = "";

extern char selected_username[NAME_LENGTH];
extern char selected_chat[CHAT_NAME_LENGTH];
extern char message_buffer[MESSAGE_LENGTH];
extern char message_old[MESSAGE_LENGTH];
extern char selected_message_text[MESSAGE_LENGTH];
extern char selected_message_sender[NAME_LENGTH];
extern int selected_chat_id;
extern int selected_message_id;
extern bool being_edited;
extern struct sockaddr_in addr;
extern bool is_reconecting;

extern int client_fd;
extern guint timer_id;

extern GtkWidget *reconnect;

void show_login_window(void);

void on_log_in_clicked(GtkButton *b, gpointer data);
void on_sign_up_clicked(GtkButton *b, gpointer data);
void on_register_clicked(GtkButton *b, gpointer data);
void on_go_back_clicked(GtkButton *b, gpointer data);

void on_name_login_changed(GtkEntry *e);
void on_password_login_changed(GtkEntry *e);
void on_name_register_changed(GtkEntry *e);
void on_password_register_changed(GtkEntry *e);
void on_password_confirm_changed(GtkEntry *e);

void show_chat_window(void);

void on_menu_clicked(GtkButton *b, gpointer data);
void on_log_out_clicked(GtkButton *b, gpointer data);
void on_change_password_clicked(GtkButton *button, gpointer user_data);
void on_cancel_change_clicked(GtkButton *b, gpointer data);
void on_save_clicked(GtkButton *button, gpointer user_data);
int change_password(char *username, char *new_password);
void on_delete_account_clicked(GtkButton *button, gpointer user_data);
void load_image(const char *filename, GtkImage *image, int width, int height);
void on_save_choose_clicked(GtkButton *button, gpointer data);
void on_choose_file_clicked(GtkButton *button, gpointer user_data);
void on_change_image_clicked(GtkButton *button, gpointer user_data);
void on_cancel_choose_clicked(GtkButton *button, gpointer user_data);

void on_search_entry_search_changed(GtkSearchEntry *search_entry, gpointer data);

int add_user(char *username, char *password);
int del_user(char *username);
int get_user(char *username, char *password);
int check_username(char *username);
int fill_users_list(const gchar *search, char *username, GtkListStore *users_store);

int add_chat(char *sender, char *receiver);
int del_chat(char *chatname);
int check_chat(char *sender, char *receiver);
int fill_chats_list(const gchar *search, GtkListStore *chats_store);

int add_message(char *chatname, char *sender, char *message);
int del_message(char *chatname, int message_id);
int update_message(char *chatname, int message_id, char *new_text);
int fill_messages_list(const char *chatname, GtkListStore *messages_store);

gboolean contains_non_english_letters(const gchar *str);

int users_callback(void *model, int argc, char **argv, char **azColName);
int chats_callback(void *model, int argc, char **argv, char **azColName);
int messages_callback(void *model, int argc, char **argv, char **azColName);

void on_edit_menu_item_clicked(GtkMenuItem *menuitem, gpointer user_data);
void on_delete_menu_item_clicked(GtkMenuItem *menuitem, gpointer user_data);
gboolean on_messages_list_button_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data);

void show_reconnect();

char *to_serv(char *str1, char *str2);
char *to_serv_x2(char *str1, char *str2, char *str3, char *str4);
char **unpack_mess_v3(char *str, int size, int size_2);
char *mx_strnew(const int size);
char *mx_itoa(int number);
void *reconnect_c(void *arg);
int Send(int sockfd, const void *buf, size_t len, int flags);

#endif
