#include "../inc/header.h"

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

void mx_daemon()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        printf("PID = %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    // Створюємо нову сесію і стаємо лідером групи процесів
    if (setsid() < 0)
    {
        exit(EXIT_FAILURE);
    }

    umask(0);

    // Закриваємо стандартні вхідні, вихідні та помилкові потоки
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        mx_printerr("usage: ./uchat_server [port]\n");
        return 1;
    }
    int hton = atoi(argv[1]);

    mx_daemon();

    sqlite3 *db;
    int rc = sqlite3_open("server/chat.db", &db);
    if (rc)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc)
    {
        printf("Can't create tables: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    sql = sqlite3_mprintf("CREATE TABLE IF NOT EXISTS chats (id INTEGER PRIMARY KEY AUTOINCREMENT, chatname TEXT, sender TEXT, receiver TEXT);");
    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc)
    {
        printf("Can't create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(0);
    }

    sqlite3_close(db);

    pthread_t pth[1];
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(hton);
    Bind(server, (struct sockaddr *)&addr, sizeof addr);
    Listen(server, 5);
    int fd;
    socklen_t len = sizeof addr;
    while ((fd = Accept(server, (struct sockaddr *)&addr, &len)))
    {
        printf("%d\n", fd);
        pthread_create(&pth[0], NULL, recive, &fd);
    }

    close(server);

    return 0;
}
