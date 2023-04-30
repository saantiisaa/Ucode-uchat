#include "../inc/header.h"

char *mx_strnew(const int size)
{
    if (size >= 0)
    {
        char *str = malloc((size + 1));
        for (int i = 0; i <= size; i++)
        {
            str[i] = '\0';
        }
        return str;
    }
    else
    {
        return NULL;
    }
}

gboolean contains_non_english_letters(const gchar *str)
{
    guint i;
    for (i = 0; str[i]; i++)
    {
        if (!isalnum(str[i]) && str[i] != '_')
        {
            return TRUE;
        }
    }
    return FALSE;
}

char *to_serv(char *str1, char *str2)
{
    char *res = malloc(strlen(str1) + strlen(str2) + 1);
    res = strcpy(res, str1);
    res = strcat(res, "|");
    res = strcat(res, str2);
    return res;
}

char *to_serv_x2(char *str1, char *str2, char *str3, char *str4)
{
    char *res = malloc(strlen(str1) + strlen(str2) + strlen(str3) + strlen(str4) + 3);

    res = strcpy(res, str1);
    res = strcat(res, "|");
    res = strcat(res, str2);
    res = strcat(res, "|");
    res = strcat(res, str3);
    res = strcat(res, "m");
    res = strcat(res, str4);
    return res;
}

char **unpack_mess(char *str, int size)
{
    int delimiter;
    char **res = malloc((sizeof(char *)) * 4);

    char *ptr = strchr(&str[0], (int)'|');
    printf("%s\n", ptr);
    delimiter = ptr - str;
    printf("d1-%d-%d\n", delimiter, size);
    res[0] = mx_strnew(delimiter);
    res[0] = strncpy(res[0], &str[0], delimiter);
    printf("str0 %s\n", res[0]);

    ptr = strchr(&str[delimiter + 1], '|');
    int delimiter2 = ptr - str;
    printf("d2-%d-%d\n", delimiter2, size);

    res[1] = mx_strnew(delimiter2 - 1);
    printf("\n -----k--- \n");
    res[1] = strncpy(res[1], &str[delimiter + 1], delimiter2 - delimiter - 1);
    printf("str1 %s\n", res[1]);

    ptr = strchr(&str[delimiter2 + 1], '|');
    int delimiter3 = ptr - str;
    printf("d3-%d-%d\n", delimiter3, size);
    res[2] = mx_strnew(delimiter3 - delimiter2);
    res[2] = strncpy(res[2], &str[delimiter2 + 1], delimiter3 - delimiter2 - 1);
    printf("\n%s\n", res[2]);
    res[3] = mx_strnew(size - delimiter3);
    res[3] = strcpy(res[3], &str[delimiter3 + 1]);
    printf("-%d-%d\n", delimiter3, size);

    return (char **)res;
}

char **unpack_mess2(char *str, int size)
{
    int delimiter;
    char **res = malloc((sizeof(char *)) * 5);

    char *ptr = strchr(&str[0], (int)'|');
    printf("%s\n", ptr);
    delimiter = ptr - str;
    printf("d1-%d-%d\n", delimiter, size);
    res[0] = mx_strnew(delimiter);
    res[0] = strncpy(res[0], &str[0], delimiter);
    printf("str0 %s\n", res[0]);

    ptr = strchr(&str[delimiter + 1], '|');
    int delimiter2 = ptr - str;
    printf("d2-%d-%d\n", delimiter2, size);

    res[1] = mx_strnew(delimiter2 - 1);
    printf("\n -----k--- \n");
    res[1] = strncpy(res[1], &str[delimiter + 1], delimiter2 - delimiter - 1);
    printf("str1 %s\n", res[1]);

    ptr = strchr(&str[delimiter2 + 1], '|');
    int delimiter3 = ptr - str;
    printf("d3-%d-%d\n", delimiter3, size);
    res[2] = mx_strnew(delimiter3 - delimiter2);
    res[2] = strncpy(res[2], &str[delimiter2 + 1], delimiter3 - delimiter2 - 1);
    printf("\n%s\n", res[2]);
    ptr = strchr(&str[delimiter3 + 1], '|');
    int delimiter4 = ptr - str;
    printf("d4-%d-%d\n", delimiter4, size);
    res[3] = mx_strnew(delimiter4 - delimiter3);
    res[3] = strncpy(res[3], &str[delimiter4 + 1], delimiter4 - delimiter3 - 1);
    printf("\n%s\n", res[3]);
    res[4] = mx_strnew(size - delimiter4);
    res[4] = strcpy(res[4], &str[delimiter4 + 1]);
    printf("-%d-%d\n", delimiter4, size);

    return (char **)res;
}

char **unpack_mess_v3(char *str, int size, int size_2)
{
    printf("str %s\n", str);
    char **res = malloc((sizeof(char *)) * size_2);

    int delimeter = 0;
    int prev_delimeter = 0;
    for (int i = 0; i < size_2 - 1; i++)
    {
        int temp = 1;
        if (i == 0)
        {
            temp = 0;
        }
        char *ptr = strchr(&str[delimeter + temp], '|');
        delimeter = ptr - str;
        res[i] = mx_strnew(delimeter - temp);
        printf("d1-%d-%d\n", delimeter, size);
        res[i] = strncpy(res[i], &str[prev_delimeter + temp], delimeter - prev_delimeter - temp);
        printf("str%d %s\n", i, res[i]);
        prev_delimeter = delimeter;
    }
    res[size_2 - 1] = mx_strnew(size - delimeter);
    res[size_2 - 1] = strcpy(res[size_2 - 1], &str[delimeter + 1]);
    printf("-%d-%d\n", delimeter, size);
    printf("str%d %s\n", size_2 - 1, res[size_2 - 1]);
    return (char **)res;
}

char *mx_itoa(int number)
{
    char *result = NULL;
    bool is_neg = false;
    int c = 0;
    if (number == 0)
    {
        result = mx_strnew(1);
        result[0] = '0';
        return result;
    }
    if (number < 0)
    {
        if (number == -2147483648)
        {
            return "-2147483648";
        }
        number *= -1;
        is_neg = true;
        c++;
    }
    if (number == 2147483647)
    {
        return "2147483647";
    }
    int t = number;
    for (; t != 0;)
    {
        t = t / 10;
        c++;
    }

    if (is_neg)
    {
        result = mx_strnew(c);
        result[0] = '-';
    }
    else
    {
        result = mx_strnew(c);
    }

    while ((number != 0 && c >= 0) && result[c] != '-')
    {
        result[--c] = (number % 10) + '0';
        number /= 10;
    }

    return result;
}

gboolean show_widget_idle(GtkWidget *window)
{
    gtk_widget_show_all(window);
    return G_SOURCE_REMOVE;
}

gboolean hide_widget_idle(GtkWidget *window)
{
    gtk_widget_hide(window);
    return G_SOURCE_REMOVE;
}

gboolean destroy_widget_idle(GtkWidget *window)
{
    gtk_widget_destroy(window);
    return G_SOURCE_REMOVE;
}

void show_widget(GtkWidget *window)
{
    g_idle_add((GSourceFunc)show_widget_idle, window);
}

void hide_widget(GtkWidget *window)
{
    g_idle_add((GSourceFunc)hide_widget_idle, window);
}

void destroy_widget(GtkWidget *window)
{
    g_idle_add((GSourceFunc)destroy_widget_idle, window);
}

void *reconnect_c(void *arg)
{
    show_reconnect();
    show_widget(reconnect);

    while (1)
    {
        close(client_fd);
        client_fd = socket(AF_INET, SOCK_STREAM, 0);

        struct timeval tv;
        fd_set set;
        int rc;

        // Встановлюємо таймаут на 5 секунд
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        // Встановлюємо файловий дескриптор для відслідковування подій
        FD_ZERO(&set);
        FD_SET(client_fd, &set);

        // Чекаємо, поки socket буде доступний для запису
        rc = select(client_fd + 1, NULL, &set, NULL, &tv);
        if (rc < 0)
        {
            perror("Error in select");
            exit(EXIT_FAILURE);
        }
        else if (rc == 0)
        {
            // socket не готовий для запису, пробуємо ще раз
            continue;
        }
        else
        {
            // socket доступний для запису, підключаємося до сервера
            if (connect(client_fd, (struct sockaddr *)&addr, sizeof addr) == -1)
            {
                close(client_fd);
                printf("reconecting..\n");
                sleep(5);
                continue;
            }
            else
            {
                // успішне підключення до сервера, виходимо з циклу
                break;
            }
        }
    }
    destroy_widget(reconnect);
    is_reconecting = false;
    pthread_exit(NULL);
}

int Send(int sockfd, const void *buf, size_t len, int flags)
{
    int k = send(sockfd, buf, len, flags);
    if (k == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            fd_set set;
            struct timeval timeout;
            int rv = 0;
            while (rv == 0)
            {
                FD_ZERO(&set);
                FD_SET(sockfd, &set); // додати дескриптор сокета до множини

                timeout.tv_sec = 5; // задати час очікування 5 секунд
                timeout.tv_usec = 0;

                rv = select(sockfd + 1, NULL, &set, NULL, &timeout);
                if (rv == -1)
                {
                    perror("select"); // помилка select()
                    break;
                }
            }
            k = Send(sockfd, buf, len, 0);
        }
        else
        {
            if (is_reconecting == false)
            {
                pthread_t pth;
                is_reconecting = true;
                pthread_create(&pth, NULL, reconnect_c, &pth);
                k = Send(sockfd, buf, len, 0);
            }
        }
    }

    return k;
}
