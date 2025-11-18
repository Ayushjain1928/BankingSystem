#include <stdio.h>
#include <mysql/mysql.h>

#define PASSWD "Mydatabases@123"
#define USER "root"


void mysql_query_excuter(const char *, const char *);   //function prototype for connection
void account_creation();

int user_menu();
int user_menu() {

}

void mysql_query_excuter(const char *query ,const char *databases ) {
    MYSQL *conn = mysql_init(NULL);

    // Check initialization
    if (conn == NULL) {
        printf("mysql_init failed\n");
        return;
    }

    // Connect to server
    if (!mysql_real_connect(conn, "localhost", USER, PASSWD,databases, 0, NULL, 0)) {
        printf("Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Execute query
    if (mysql_query(conn, query)) {
        printf("Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
