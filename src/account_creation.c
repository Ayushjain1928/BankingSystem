#include <stdio.h>
#include <mysql/mysql.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define PASSWD "Mydatabases@123"
#define USER "root"

typedef struct
{
    unsigned long long account_no;
    char name[20];
    unsigned int age;
    char gender[10];
    char date_of_birth[11];
    char aadhar_no[18];
    char pan_no[18];
    char phone[15];
    char email[20];
    unsigned long long balance;
    char account_type[10];
} Account;

void mysql_query_excuter(const char *, const char *); // function prototype for connection

int user_menu();

void mysql_query_excuter(const char *query, const char *databases)
{
    MYSQL *conn = mysql_init(NULL);

    // Check initialization
    if (conn == NULL)
    {
        printf("mysql_init failed\n");
        return;
    }

    // Connect to server
    if (!mysql_real_connect(conn, "localhost", USER, PASSWD, databases, 0, NULL, 0))
    {
        printf("Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Execute query
    if (mysql_query(conn, query))
    {
        printf("Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main(int argc, char const *argv[])
{
    user_menu();
    return 0;
}

Account acc;
int user_menu()
{
    printf("Write down your name.");
    scanf("%s", &acc.name);
    printf("Write down your age.");
    scanf("%u", &acc.age);
    printf("Write down your Date of Birth(YYYY-MM-DD).");
    scanf("%10s", &acc.date_of_birth);
    printf("Write down your Gender(Male,Female,Other).");
    char temp[10];
    scanf("%s", &temp);
    char temp1[10] = toupper(temp);
    if (strcmp(temp1,"MALE") == 0)
    {
        strcpy(acc.gender,"MALE");
    }
    else if (strcmp(temp1,"FEMALE") == 0)
    {
        strcpy(acc.gender,"FEMALE");
    }
    else
    {
        strcpy(acc.gender,"OTHER");
    }
    
   
    printf("Write down your Aadhar Number.");
    scanf("%s", &acc.aadhar_no);
    printf("Write down your Pan Number.");
    scanf("%s", &acc.pan_no);
    printf("Write down your Phone Number.");
    scanf("%s", &acc.phone);
    printf("Write down your age.");
    scanf("%s", &acc.email);
    printf("Write down your Type of Account(Savings,Current).");
    char temp2[10];
    scanf("%s", &temp2);
    char temp3[10] = isupper(temp2);
    if (strcmp(temp2,"SAVINGS") == 0)
    {
        strcpy(acc.gender,"SAVINGS");
    }
    else
    {
        strcpy(acc.gender,"CURRENT");
    

    char query[1024];

    sprintf(query,
            "INSERT INTO your_table_name (account_no, name, age, gender, date_of_birth, Aadhar_no, Pan_no, phone, email, balance, account_type, created_at, updated_at) "
            "VALUES (0000000000, '%s', %u, %d, '%s', '%s', '%s', '%s', '%s', %llu, %d, NOW(), NOW());",
            acc.account_no,
            acc.name,
            acc.age,
            acc.gender,
            acc.date_of_birth,
            acc.aadhar_no,
            acc.pan_no,
            acc.phone,
            acc.email,
            acc.balance,
            acc.account_type);

    mysql_query_excuter(query, "account_information");

    return 0;
}