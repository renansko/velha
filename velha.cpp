#include <iostream>
#include <mysql.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "seguro.h"

using namespace std;

char numbers[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char digit[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

const char* password = seguro;
const char* user = user;

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

    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS USERS(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), email VARCHAR(255), password varchar(255))")) {
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
    char query[150] = "";
   
    if (!conn) {
        cout << "falha no mysql_init()" << endl;
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", user, password,
        NULL, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char* a, email[100];
    cout << "----------------------\n";
    cout << "Digite sua nome:    " << endl;

    char* b, password[100];
    cout << "----------------------\n";
    cout << "Digite sua senha:    " << endl;
    const char* value = "*";
    const char* table = "USERS";

    fgets(email, sizeof(email), stdin);

    sprintf_s(query, "select * from '%s' where email = '%s' AND password = '%s'", table, email, password);

    MYSQL_RES* result = mysql_store_result(conn);
    if (mysql_query(conn, query) != 0)
    {
        printf("\nFalha de consulta");
    }
    else if (result == NULL)
    {
        printf("\n credenciais invalidas!");
        exit(1);
    }

    printf("\n O usuario com o nome: %s Foi logado\n", email);
    mysql_close(conn);
  
    return email;
}

int registrar() {
    MYSQL* conn = mysql_init(NULL);
    char query[150] = "";

    if (!conn) {
        cout << "falha no mysql_init()" << endl;
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", user, password,
        NULL, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    cout << "REGISTRAR" << endl;
    cout << "----------------------\n";
    cout << "Digite seu email:    " << endl;
    char* p, email[100];

    const char* value = "*";
    const char* table = "USERS";

    fgets(email, sizeof(email), stdin);

    sprintf_s(query, "select * from '%s' where email = '%s'", table, email);
    MYSQL_RES* result = mysql_store_result(conn);
    if (mysql_query(conn, query) != 0)
    {
        printf("\nFalha de consulta");
    }
    else if (result != NULL)
    {
        printf("\n ja existe um usuario com esse email");
        exit(1);
    }

    char* a, nome[100];
    cout << "----------------------\n";
    cout << "Digite sua nome:    " << endl;

    char* b, password[100];
    cout << "----------------------\n";
    cout << "Digite sua senha:    " << endl;

    sprintf_s(query, "INSERT INTO '%s' (name, email, password) values('%s','%s','%s'); ", table, nome, email, password);

    if (mysql_query(conn, query) != 0)
    {
        printf("\nFalha de consulta");
    }
    else if (result == NULL)
    {
        printf("\n nao foram inseridos nenhum usuario");
        exit(1);
    }

    printf("\n O usuario com o email: %s Foi inserido\n", email);
    mysql_close(conn);

    return;
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

std::pair<std::string, char*> displayMenu()
{
    int acc = 1;
    char* email_1;
    char* email_2;
    for (int i; i < acc; i--) {
        cout << "Menu" << endl;
        cout << "----------------------\n";
        cout << "Login do :" << acc << " player digite 1." << endl;
        cout << "----------------------\n";
        cout << "Registrar o:" << acc << " player digite 2." << endl;
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
            if (acc == 1) {
                email_1 = login();
                
            }
            if (acc == 0) {
                email_2 = login();
            }

        case 2:
            system("cls");
            printf("registrar");
            registrar();
            displayMenu();

        default:
            exit(0);
        }

        string tmp_string(email_1);
       
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

    void check(int value)
    {
  
        if (numbers[value] == 'X')
        {
            cout << "==> Player 1 wins" << endl;            
        }
        else if (numbers[value] == 'O')
        {
          
            cout << "==> Player 2 wins" << endl;
            exit(0);
        }

    }

    // checks who won the game
    void win()
    {
        int x = 0;
        for (int i = 0; i < 9; i++)
        {
            //checks horizontal
            if (i == 0 || i == 3 || i == 6)
            {
                if (numbers[i] == numbers[i += 1] && numbers[i] == numbers[i += 1])
                {
                    check(i);
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
                    check(i);
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
            check(0);
        }
        else if (numbers[2] == numbers[4] && numbers[2] == numbers[6])
        {
            check(2);
        }
    }
};


int main()
{
    bd();
    std::pair<std::string, char*> player = displayMenu();

    std::string player_1 = player.first;
    char* player_2 = player.second;

    char number;
    Players player1;
    Players player2;

    cout << "\tTic Tac Toe" << endl;
    cout << "Player 1 (X)  -  Player 2 (O)" << endl;
    display();

    //switch between players
    for (int n = 0; n < 5; n++)
    {
        for (int i = 1; i < 3; i++)
        {
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
                player1.win();
            }
            if (i == 1 && n == 4)
            {
                cout << "==> It's a tie." << endl;
                break;
            }
            else if (i == 2)
            {
                player2.player(number, i);
                player2.win();


            }
        }
    }

    return 0;
}
