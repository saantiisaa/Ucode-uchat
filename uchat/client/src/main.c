#include "../inc/header.h"

GtkBuilder *builder;
GError *error = NULL;

// login window
GtkWidget *login_window;
GtkStack *stack;
GtkWidget *child;
gboolean remember_is_toggled = FALSE;

GtkWidget *login_button;
GtkWidget *remember_button;
GtkWidget *signup_button;
GtkWidget *register_button;
GtkWidget *goback_button;

GtkWidget *name_entry;
GtkWidget *pass_entry;
GtkWidget *register_name_entry;
GtkWidget *register_pass_entry;
GtkWidget *register_confirm_entry;

GtkWidget *error_label;
GtkWidget *info_label;

// chat window
GtkWidget *chat_window;

GtkWidget *name_label;
GtkWidget *chat_label;
GtkWidget *edit_label;
GtkWidget *add_chat_label;

GtkWidget *logout_button;
GtkWidget *newchat_button;
GtkWidget *enter_button;

// chats
GtkSearchEntry *chats_entry;
GtkTreeView *chats_list;
GtkListStore *chats_store;
GtkTreeSelection *chats_selection;

// messages
GtkWidget *messages_entry;
GtkTreeView *messages_list;
GtkListStore *messages_store;
GtkTreeSelection *messages_selection;
GtkScrolledWindow *messages_scroller;

// subwindow
GtkWidget *add_chat_window;

GtkWidget *new_chat_error;
// users
GtkSearchEntry *users_entry;
GtkTreeView *users_list;
GtkTreeSelection *users_selection;
GtkListStore *users_store;

GtkWidget *menu_window;
GtkWidget *menu_label;
GtkImage *profile_image;
GtkWidget *change_password_button;
GtkWidget *delete_account;
GtkWidget *change_image_button;
GtkWidget *change_password_window;
GtkWidget *change_password_dialog;
GtkWidget *current_password_entry;
GtkWidget *new_password_entry;
GtkWidget *confirm_password_entry;
GtkWidget *change_password_error_label;
GtkWidget *save_button;
GtkWidget *cancel_change_button;
GtkWidget *change_image_window;
GtkImage *profile_image1;
GtkWidget *choose_file_button;
GtkWidget *save_choose_button;
GtkWidget *cancel_choose_button;
GtkLabel *menu_name_label;

char username[NAME_LENGTH] = "";
char password[PASS_LENGTH] = "";
char selected_username[NAME_LENGTH] = "";
char selected_chat[CHAT_NAME_LENGTH] = "";
char message_buffer[MESSAGE_LENGTH] = "";
char selected_message_text[MESSAGE_LENGTH] = "";
char selected_message_sender[NAME_LENGTH] = "";
char message_old[MESSAGE_LENGTH] = "";
int selected_chat_id;
int selected_message_id;
bool being_edited = false;
struct sockaddr_in addr = {0};
bool is_reconecting = false;

int client_fd;
guint timer_id;

GtkWidget *reconnect;

int Socket(int domain, int type, int protocol)
{
    int res = socket(domain, type, protocol);
    if (res == -1)
    {
        printf("Error");
        exit(1);
    }
    return res;
}
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if (bind(sockfd, addr, addrlen) == -1)
    {
        printf("Error2");
        exit(1);
    }
}
void Listen(int domain, int num)
{
    if (listen(domain, num) == -1)
    {
        printf("Error3");
        exit(1);
    }
}
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int res = accept(sockfd, addr, addrlen);
    if (res == -1)
    {
        printf("Error4");
        exit(1);
    }
    return res;
}
void Connect(int domain, const struct sockaddr *addr, socklen_t addrlen)
{
    int res = connect(domain, addr, addrlen);
    if (res == -1)
    {
        perror("Error6");
        exit(1);
    }
}
void Inet_pton(int domain, const char *src, char *dst)
{
    int res = inet_pton(domain, src, dst);
    if (res == 0 || res == -1)
    {
        printf("Error7");
        exit(1);
    }
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        write(2, "usage: ./uchat [IP address] [port]\n", 36);
        return 1;
    }
    int hton = atoi(argv[2]);

    gtk_init(&argc, &argv);
    client_fd = Socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(hton);
    // 127.0.0.1
    Inet_pton(AF_INET, argv[1], (char *)&addr.sin_addr);
    Connect(client_fd, (struct sockaddr *)&addr, sizeof addr);

    FILE *fp;

    fp = fopen("resources/cash.bin", "r");

    if (fp == NULL)
    {
        printf("failed to open cash.bin\n");
        show_login_window();
    }
    else
    {
        char *str = mx_strnew(NAME_LENGTH + PASS_LENGTH + 1);
        fgets(str, NAME_LENGTH + PASS_LENGTH + 1, fp);
        fclose(fp);
        char **mes = unpack_mess_v3(str, strlen(str), 2);
        free(str);
        strcpy(username, mes[0]);
        strcpy(password, mes[1]);
        free(mes[0]);
        free(mes[1]);
        free(mes);

        if (get_user(username, password) == 1)
        {
            show_chat_window();
        }
    }

    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_css_provider_load_from_file(provider, g_file_new_for_path("resources/style.css"), NULL);

    gtk_main();
    close(client_fd);
    return EXIT_SUCCESS;
}
