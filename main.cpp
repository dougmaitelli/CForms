#include <iostream>
#include <windows.h>
#include <conio.h>

#include <vector>

using namespace std;

struct user_info {
    char name[10];
    char lastname[10];
    char birthdate[11];
    char sex[10];
    char adress[30];
    char zipcode[10];
    char quarter[20];
    char city[20];
    char estate[10];
    char country[10];
    char telephone[10];
    char cellphone[10];
    char email[20];
};

vector<user_info*> Contacts;

void add()
{
    system("CLS");

    user_info* contact = new (nothrow)user_info;

    char* temp;

    printf("Digite o nome que voce deseja cadastrar:");
    gets(temp);
    sprintf(contact->name, temp);
    printf("Digite o sobrenome que voce deseja cadastrar:");
    gets(temp);
    sprintf(contact->lastname, temp);
    printf("Digite o telefone que voce deseja cadastrar:");
    gets(temp);
    sprintf(contact->telephone, temp);
    printf("Digite o celular que voce deseja cadastrar:");
    gets(temp);
    sprintf(contact->cellphone, temp);

    sprintf(contact->birthdate, "");
    sprintf(contact->birthdate, "");
    sprintf(contact->sex, "");
    sprintf(contact->adress, "");
    sprintf(contact->zipcode, "");
    sprintf(contact->quarter, "");
    sprintf(contact->city, "");
    sprintf(contact->estate, "");
    sprintf(contact->country, "");
    sprintf(contact->email, "");

    Contacts.push_back(contact);
}

void erase(int i)
{
    Contacts.erase(Contacts.begin() + i);
}

struct field_info {
    int x;
    char* value;
};

void addfield(vector<field_info>* fields, char name[], char* value)
{
    field_info info;
    info.x = strlen(name) + 2;
    info.value = value;
    fields->push_back(info);
    printf("%s: %s\n", name, value);
}

void show(int i)
{
    system("CLS");

    vector<field_info>* fields = new (nothrow)vector<field_info>;

    user_info* contact = Contacts.at(i);

    addfield(fields, "Nome", contact->name);
    addfield(fields, "Sobrenome", contact->lastname);
    addfield(fields, "Nascimento", contact->birthdate);
    addfield(fields, "Sexo", contact->sex);
    addfield(fields, "Endereco", contact->adress);
    addfield(fields, "CEP", contact->zipcode);
    addfield(fields, "Bairro", contact->quarter);
    addfield(fields, "Cidade", contact->city);
    addfield(fields, "Estado", contact->estate);
    addfield(fields, "Pais", contact->country);
    addfield(fields, "Telefone", contact->telephone);
    addfield(fields, "Celular", contact->cellphone);
    addfield(fields, "E-mail", contact->email);

    char tecla;
    int i2 = 0;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){fields->at(i2).x, i2});

    do {
        tecla = getch();

        switch (tecla) {
            case 72:
                if (i2 > 0) {
                    i2--;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){fields->at(i2).x, i2});
                }
                break;
            case 80:
                if (i2 < fields->size()-1) {
                    i2++;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){fields->at(i2).x, i2});
                }
                break;
            case 13:
                printf("                              ");
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){fields->at(i2).x, i2});
                gets(fields->at(i2).value);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){fields->at(i2).x, i2});
                break;
            case 83:
                erase(i);
                tecla = 27;
                break;
            default:
                break;
        }
    } while((tecla != 27) && (tecla != 8));
}

void search(char arg[])
{
    system("CLS");

    vector<int> indexes;

    for (UINT i=0; i < Contacts.size(); i++) {
        user_info* contact = Contacts.at(i);
        if (strstr(strlwr(contact->name), strlwr(arg))) {
            printf(" %s %s\n", contact->name, contact->lastname);
            indexes.push_back(i);
        }
    }

    char tecla;
    int i = 0;

    do {
        if (indexes.size() <= 0) {
            printf("A busca nao retornou resultados.");
            getch();
            break;
        }

        if (i >= indexes.size()) {
            i--;
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, i});
        printf(">");

        tecla = getch();

        switch (tecla) {
            case 72:
                if (i > 0) {
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, i});
                    printf(" ");
                    i--;
                }
                break;
            case 80:
                if (i < indexes.size()-1) {
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, i});
                    printf(" ");
                    i++;
                }
                break;
            case 83:
                erase(indexes.at(i));

                system("CLS");

                indexes.clear();

                for (UINT i=0; i < Contacts.size(); i++) {
                    user_info* contact = Contacts.at(i);
                    if (strstr(contact->name, arg)) {
                        printf(" %s %s\n", contact->name, contact->lastname);
                        indexes.push_back(i);
                    }
                }
                break;
            case 13:
            case 32:
                show(indexes.at(i));

                system("CLS");

                indexes.clear();

                for (UINT i=0; i < Contacts.size(); i++) {
                    user_info* contact = Contacts.at(i);
                    if (strstr(contact->name, arg)) {
                        printf(" %s %s\n", contact->name, contact->lastname);
                        indexes.push_back(i);
                    }
                }
                break;
            default:
                break;
        }
    } while((tecla != 27) && (tecla != 8));
}

int main()
{
    char choice[20];
    bool exit = true;

    do {
        printf("Escolha a opcao desejada:\n");
        printf("1-Cadastrar;\n");
        printf("Para consultar cadastros basta digitar todo ou parte do nome desejado.\n");
        printf("Para sair digite \"exit\".\n");
        gets(choice);
        if (!strcmp(choice, "exit") == 0) {
            if (strcmp(choice, "1") == 0) {
                add();
            } else {
                search(choice);
            }
        } else {
            exit = false;
        }
        system("CLS");
    } while(exit);
    return 0;
}
