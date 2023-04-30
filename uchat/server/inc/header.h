#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sqlite3.h>
#include <pthread.h>
#include <errno.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <string.h>
// #include <sys/epoll.h>
#include "../libmx/inc/libmx.h"

bool description(int fd, char *str, int size);
int add_user(char *username, char *password);
int del_user(char *username);
int get_user(char *username, char *password);
int check_username(char *username);
char **unpack_log(char *str, int size);
void *recive(void *sock);
int fill_users_list(const char *search, int fd);
int add_chat(char *sender, char *receiver);
int fill_chats_list(const char *search, int fd);
int check_chat(char *sender, char *receiver);
char **unpack_mess(char *str, int size);
int add_message(char *chatname, char *sender, char *message);
int del_chat(char *chatname);
int update_message(char *chatname, int message_id, char *new_text);
int del_message(char *chatname, int message_id);
int fill_messages_list(const char *chatname, int fd);
char *zero_pad(int num, int width);
int count_messages(const char *chatname);

char *to_serv(char *str1, char *str2);
int count_users(const char *param);
int count_chats(char *username);

int change_password(char *username, const char *new_password);
// ssize_t Send(int sockfd, const void *buf, size_t len, int flags);
