#include <iostream>
#include <mysql.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "seguro.h"
#include <string>
#include <cstring>

using namespace std;

char numbers[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char digit[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

//char* password = seguro;
//char* user = username;
bool checkEmptyString(const char* s)
{
    return strlen(s) == 0;
}

void bd()
{
    MYSQL* conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", user, password,
        NULL, 0, NULL, 0) == NULL)
    {

        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS velha;")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "USE velha;")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS USERS(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255) NOT NULL, email VARCHAR(255) NOT NULL, password varchar(255) NOT NULL) ")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS PONTUACAO(id INT PRIMARY KEY AUTO_INCREMENT, points int(30), user_id int)")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}


//login
char* login(void)
{
    MYSQL* conn = mysql_init(NULL);
    MYSQL_ROW row;
    MYSQL_RES* result;
    char query[150] = "";
    char c;
   
    if (!conn) {
        cout << "falha no mysql_init()" << endl;
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", user, password,
        "velha", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    cout << "----------------------\n";
    cout << "Digite seu email:    " << endl;
    char email[100];
    fgets(email, 99, stdin);
    email[strcspn(email, "\n")] = 0;

    if (strlen(password) == 0 || strcmp(password, "0") == 0) {
        printf("\7\a\nDigite alguem valor!\n");
        exit(EXIT_FAILURE);
    }

    while ((c = getchar()) != '\n' && c != EOF) {};

    
    cout << "----------------------\n";
    cout << "Digite sua senha:    " << endl;
    char password[100];
    fgets(password, 99, stdin);
    password[strcspn(password, "\n")] = 0;
    while ((c = getchar()) != '\n' && c != EOF) {};

    if (strlen(password) == 0 || strcmp(password, "0") == 0) {
        printf("\7\a\nDigite alguem valor!\n");
        exit(EXIT_FAILURE);
    }
    const char* value = "*";
    const char* table = "USERS";

    sprintf_s(query, "select * from %s where email = '%s' AND password = '%s'", table, email, password);

    
    if (mysql_query(conn, query))
    {
        printf("\nFalha de consulta");
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
    }
    result = mysql_use_result(conn);
    if((row = mysql_fetch_row(result)) == NULL)
    {
        printf("\n credenciais invalidas!");
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("\n O usuario com o nome: %s Foi logado\n", email);
    mysql_close(conn);
  
    return email;
}

int registrar() {

    system("cls");
    MYSQL* conn = mysql_init(NULL);
    MYSQL_ROW row;
    MYSQL_RES* result;
    char query[150] = "";
    int res;

    if (!conn) {
        cout << "falha no mysql_init()" << endl;
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", user, password,
        "velha", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    cout << "REGISTRAR" << endl;
    cout << "----------------------\n";
    cout << "Digite seu email:    " << endl;
    char email[100];

    const char* value = "*";
    const char* table = "USERS";
    char c;

    fgets(email, 99, stdin);
    email[strcspn(email, "\n")] = 0;
    while ((c = getchar()) != '\n' && c != EOF) {};
  
    if (strlen(email) == 0 || strcmp(email, "0") == 0) {
        printf("\7\a\nDigite alguem valor!\n");
        exit(EXIT_FAILURE);
    }
    sprintf_s(query, "SELECT * FROM %s WHERE email = '%s'", table, email);


    if (mysql_query(conn, query))
    {
        printf("\nFalha de consulta");
        mysql_close(conn);
        exit(0);
    }
    result = mysql_use_result(conn);
    if ((row = mysql_fetch_row(result)) != NULL)
    {
        printf("\n ja existe um usuario com esse email \n");
        printf("\n\n\n %i , %s, %s , %s \n", row[0], row[1], row[2], row[3]);

        mysql_close(conn);
        exit(0);
    }

    char nome[100];
    cout << "----------------------\n";
    cout << "Digite sua nome:    " << endl;

    if (strlen(nome) == 0 || strcmp(nome, "0") == 0) {
        printf("\7\a\nDigite alguem valor!\n");
        exit(EXIT_FAILURE);
    }

    fgets(nome, 99, stdin);
    nome[strcspn(nome, "\n")] = 0;
    while ((c = getchar()) != '\n' && c != EOF) {};


    char password[100];
    cout << "----------------------\n";
    cout << "Digite sua senha:    " << endl;

    fgets(password, 99, stdin);
    password[strcspn(password, "\n")] = 0;

    if (strlen(password) == 0 || strcmp(password, "0") == 0) {
        printf("\7\a\nDigite alguem valor!\n");
        exit(EXIT_FAILURE);
    }

    while ((c = getchar()) != '\n' && c != EOF) {};

    sprintf_s(query, "INSERT INTO %s (name, email, password) values('%s','%s','%s'); ", table, nome, email, password);

    if (!mysql_query(conn, query))
    {
        printf("\n O usuario com o email: %s Foi inserido\n", email);
        mysql_close(conn);
    }
    else if (mysql_errno(conn)) 
    {
        printf("\n nao foram inseridos nenhum usuario");
        printf("Error %u: %s", mysql_errno(conn), mysql_error(conn));
        mysql_close(conn);
        exit(0);
    }
    int acc = 0;
    acc++;
    return acc;
}

//display tic tac toe
void display()
{
    cout << endl;
    cout << "  " << numbers[0] << "   |   " << numbers[1] << "   |   " << numbers[2] << endl;
    cout << "----------------------\n";
    cout << "  " << numbers[3] << "   |   " << numbers[4] << "   |   " << numbers[5] << endl;
    cout << "----------------------\n";
    cout << "  " << numbers[6] << "   |   " << numbers[7] << "   |   " << numbers[8] << endl;
    cout << "----------------------\n";
    cout << endl;
}

std::pair<std::string, std::string> displayMenu()
{
    system("cls");
    int acc = 2;
    char* email_1 = nullptr;
    char* email_2 = nullptr;

    for (int i = 1; i <= acc; i++) {
        cout << "Menu" << endl;
        cout << "----------------------\n";
        cout << "Login do :  " << i << " player digite 1." << endl;
        cout << "----------------------\n";
        cout << "Registrar o:  " << i << " player digite 2." << endl;
        cout << "----------------------\n";
        cout << "Sair digite qualquer outro numero." << endl;

        char* p, s[100];
        long n;

        while (fgets(s, sizeof(s), stdin)) {
            n = strtol(s, &p, 10);
            if (p == s || *p != '\n') {
                printf("porfavor digite um numero: ");
            }
            else break;
        }
        printf("Voce digitou: %ld\n", n);
        switch (n)
        {
        case 1:
            system("cls");
            printf("login");
            if (i == 1) {
                email_1 = login();
                
            }
            if (i == 2) {
                email_2 = login();
                break;
            }
           
            continue;

        case 2:
            system("cls");
            printf("registrar");
 
            if (registrar() == 1) {
                //displayMenu();
                system("cls");
                continue;
            }
            break;

        default:
            exit(0);
        }

        string tmp_string(email_1);
        string tmp_string_2(email_2);
       
        return std::make_pair(email_1, email_2);
    }
  
  
}

class Players
{
public:
    //input value turns to X or O
    void player(char& num, int value)
    {
        for (int i = 0; i < 9; i++)
        {
            if (num == numbers[i] && value == 1)
            {
                numbers[i] = 'X';
            }
            else if (num == numbers[i] && value == 2)
            {
                numbers[i] = 'O';
            }
        }

    }

    void check(int value, std::string player_1, std::string player_2)
    {
  
        if (numbers[value] == 'X')
        {
            cout << "==> Player "<< player_1 << " wins" << endl;
            exit(0);
        }
        else if (numbers[value] == 'O')
        {
          
            cout << "==> Player "<< player_2 << " wins" << endl;
            exit(0);
        }

    }

    // checks who won the game
    void win(std::string player_1, std::string player_2)
    { 
        int x = 0;
        for (int i = 0; i < 9; i++)
        {
            //checks horizontal
            if (i == 0 || i == 3 || i == 6)
            {
                if (numbers[i] == numbers[i += 1] && numbers[i] == numbers[i += 1])
                {
                    check(i, player_1, player_2);
                }
            }
            if (i == 8)
            {
                break;
            }
            //checks vertical
            else if (i == 0 || i == 1 || i == 2)
            {
                if (numbers[i] == numbers[i += 3] && numbers[i] == numbers[i += 3])
                {
                    check(i,player_1,player_2);
                }
                else
                {
                    x++;
                    switch (x)
                    {
                    case 1:
                        i = 0;
                        break;
                    case 2:
                        i = 1;
                        break;
                    case 3:
                        break;
                    }
                }
            }
        }

        //checks diagonal right and left
        if (numbers[0] == numbers[4] && numbers[0] == numbers[8])
        {
            check(0, player_1, player_2);
        }
        else if (numbers[2] == numbers[4] && numbers[2] == numbers[6])
        {
            check(2, player_1, player_2);
        }
    }
};


int main()
{
    bd();
    std::pair<std::string, std::string> player = displayMenu();

    std::string player_1 = player.first;
    std::string player_2 = player.second;
    std::string temp;

    char number;
    Players player1;
    Players player2;


    cout << "\tTic Tac Toe" << endl;
    cout << player_1  << " 'player 1' (X) - " << player_2 << " 'player 2' (O)" << endl;
    

    //switch between players
    for (int n = 0; n < 5; n++)
    {
        for (int i = 1; i < 3; i++)
        {
            display();
            cout << "Player " << i << ", enter a number: ";
            cin >> number;
            for (int q = 0; q < 9; q++)
            {
                //check if correct input
                if (number != digit[q] && q == 8)
                {
                    cout << "Invalid value" << endl;
                    exit(0);
                }
                if (number == digit[q])
                {
                    break;
                }
            }
            if (i == 1)
            {
                player1.player(number, i);
                player1.win(player_1, player_2);
            }
            if (i == 1 && n == 4)
            {
                cout << "==> It's a tie." << endl;
                break;
            }
            else if (i == 2)
            {
                player2.player(number, i);
                player2.win(player_1, player_2);


            }
        }
    }

    return 0;
}
