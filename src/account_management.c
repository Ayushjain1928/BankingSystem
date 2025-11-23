#include <stdio.h>
#include <regex.h>
#include <string.h>
#include "account_creation.h"

char value[MAX_ROWS][20][MAX_LENGTH];
int no_of_rows;

int main()
{
    // mysql_query_excuter("select * from account_information","accounts",1,value,&no_of_rows);

    int option;
    char account_number_input[20];
    char account_passwd_input[10];
    regex_t regex_value;
    const char *pattern;
    printf("\n\n\n-----------------Welcome To Bank------------------\n\n");
    while (1)
    {

        printf("01) Account Creation\n");
        printf("02) Account Checker\n");
        printf("03) Exit\n\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            user_menu();
            continue;

        case 2:
            pattern = "^[0-9]{12}$";
            regcomp(&regex_value, pattern, REG_EXTENDED);
            int no_of_tries = 3;
            buffer();
            while (1)
            {
                int tester = 0;
                if (no_of_tries <= 0)
                {
                    printf("\n\tTo much incorrect attemt\n\n");
                    break;
                }
                printf("Enter your Account Number :");
                fgets(account_number_input, sizeof(account_number_input), stdin);
                account_number_input[strcspn(account_number_input, "\n")] = '\0';
                if (regexec(&regex_value, account_number_input, 0, NULL, 0) != 0)
                {
                    printf("\nInvalid Account Number \n\n");
                    no_of_tries = no_of_tries - 1;
                    if (no_of_tries != 0)
                        printf("no of tries left is %d\n", no_of_tries);
                    continue;
                }
                mysql_query_excuter("select account_no,password_hash from account_information", "accounts", 1, value, &no_of_rows);
                for (int i = 0; i <= no_of_rows; i++)
                {
                    if (strcmp(account_number_input, value[i][0]) != 0)
                    {
                        continue;
                    }
                    tester = 1;
                    break;
                }
                if (tester == 0)
                {
                    printf("No match found\n");
                    no_of_tries = no_of_tries - 1;
                    if (no_of_tries != 0)
                        printf("no of tries left is %d\n", no_of_tries);
                    printf("try again\n");
                    continue;
                }
                pattern = "^(\\S){6}$";
                regcomp(&regex_value, pattern, REG_EXTENDED);
                no_of_tries = 3;
                while (1)
                {
                    tester = 0;
                    if (no_of_tries <= 0)
                    {
                        printf("\n\tTo much incorrect attemt\n\n");
                        break;
                    }
                    printf("Enter your Account Number :");
                    fgets(account_passwd_input, sizeof(account_passwd_input), stdin);
                    account_passwd_input[strcspn(account_passwd_input, "\n")] = '\0';
                    if (regexec(&regex_value, account_passwd_input, 0, NULL, 0) != 0)
                    {
                        printf("\nInvalid Account Passwd \n\n");
                        no_of_tries = no_of_tries - 1;
                        if (no_of_tries != 0)
                            printf("no of tries left is %d\n", no_of_tries);
                        continue;
                    }
                    for (int i = 0; i <= no_of_rows; i++)
                    {
                        if (strcmp(account_passwd_input, value[i][1]) != 0)
                        {
                            continue;
                        }
                        tester = 1;
                        break;
                    }
                    if (tester == 0)
                    {
                        printf("No match found\n");
                        no_of_tries = no_of_tries - 1;
                        if (no_of_tries != 0)
                            printf("no of tries left is %d\n", no_of_tries);
                        printf("try again\n");
                        continue;
                    }
                    break;
                }
                printf("done\n\n");
                break;
            }

        default:
            break;
        }
    }
    return 0;
}

// int main()
// {
//     mysql_query_excuter("select account_no from account_information", "accounts", 1, value, &no_of_rows);
//     printf("%s\n",value[0][0]);
//     printf("%d\n",no_of_rows);
//     return 0;
// }
