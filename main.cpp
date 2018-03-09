#include "Person.h"


bool menu(Person ** ppersons, Person * persons);
bool insertPerson(Person** ppersons, Person* persons);
bool displayPersons(Person** ppersons, Person* persons);
bool subMenu(Person ** ppersons, Person * persons);
bool displayAgeCohort(Person**ppersons, Person *persons);
void messageContinue(const std::string message);

namespace {
    /*------casted umlaute in der konsole direkt um :))------*/
    const unsigned char AE = static_cast<unsigned char>(142);//
    const unsigned char ae = static_cast<unsigned char>(132);//
    const unsigned char OE = static_cast<unsigned char>(153);//
    const unsigned char oe = static_cast<unsigned char>(148);//
    const unsigned char UE = static_cast<unsigned char>(154);//
    const unsigned char ue = static_cast<unsigned char>(129);//
    const unsigned char ss = static_cast<unsigned char>(225);//
    /*-------------------------------------------------------*/

    const int kMaxObjects = 3;
    const char* kOffset= "\n\t\t\t";
}

int main()
{
    Person person;
    person.setYearOfBirth(20);

    Person person2("ich", "selbst", 3);
    Person person3(person2);

    person = person3;

    Person* ppersons[kMaxObjects];
    Person persons[kMaxObjects];
    Person ** persons3;
    for (size_t i = 0; i < kMaxObjects; i++)
    {
        //persons[i] = *(new Person());
        ppersons[i] = new Person();
    }

    menu(ppersons, persons);

    for (size_t i = 0; i < person.getCount(); i++)
    {
        //delete &persons[i];
        delete ppersons[i];
    }

    //std::cout << "press enter to exit";
    //std::cin.get();
    return 0;
}

bool menu(Person ** ppersons, Person * persons)
{
    while (1)
    {
        std::cout << "\n\n" <<
        kOffset<<"Men"<<ue<<
        kOffset << "1.) Eingabe" <<
        kOffset << "2.) Ausgabe" <<
        kOffset << "3.) Beenden" <<
        kOffset << "Auswahl: ";

        char input;
        std::cin >> input;
        if (!std::cin)
        {
            messageContinue("Ungueltige Eingabe");
            break;
        }

        switch (input)
        {
        case '1':
            if (insertPerson(ppersons, persons))
                messageContinue("Neuer Datensatz hinzugefuegt");
            else
                messageContinue("Datensatz konnte nicht hinzugefuegt werden");
            break;
        case '2': 
            if (!subMenu(ppersons, persons))
                messageContinue("Menue konnte nicht aufgerufen werden");
            break;
        case '3': return true;
        default: messageContinue("Menue konnte nicht aufgerufen werden");
            break;
        }

    }
    Person* fjdk = new Person;
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //checks for memoryleaks
}


bool insertPerson(Person** ppersons, Person* persons)
{
    std::string firstName;
    std::string lastName;
    int year_of_birth;
    
    if (!(persons->getCount() < kMaxObjects))
    {
        std::cout << "      Keine freien Datens" << ae << "tze\n";
        return false;
    }

    std::cout << "\n      Vorname eingeben:";
    std::cin >> firstName;

    if (!std::cin)
    {
        std::cout << "      Ung"<<ue<<"ltige Eingabe\n";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        return false;
    }
    std::cout << "      Nachname eingeben:";
    std::cin >> lastName;
    if (!std::cin)
    {
        std::cout << "      Ung"<<ue<<"ltige Eingabe\n";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        return false;
    }
    std::cout << "      Geburtsjahr eingeben:";
    std::cin >> year_of_birth;
    if (std::cin.fail())
    {
        std::cout << "      Ung"<<ue<<"ltige Eingabe" << std::endl ;
        //std::cin.seekg(0, std::ios::end);
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        //std::cin.clear();
        //std::cin.ignore('\n');
        return false;
    }
    Person person(firstName.c_str(), lastName.c_str(), year_of_birth);

    //persons[person.raiseCount() - 1] = person;
    //ppersons[person.getCount()] = &person;

    //persons[person.getCount()] = *(new Person());

    persons[person.getCount()].setFirstName(firstName.c_str());
    persons[person.getCount()].setLastName(lastName.c_str());
    persons[person.getCount()].setYearOfBirth(year_of_birth);

    ppersons[person.getCount()]->setFirstName(firstName.c_str());
    ppersons[person.getCount()]->setLastName(lastName.c_str());
    ppersons[person.getCount()]->setYearOfBirth(year_of_birth);

    person.raiseCount();

}

bool displayPersons(Person ** ppersons, Person * persons)
{
    for (auto  i = 0; i < persons[0].getCount(); i++)
    {
        persons[i].display();
        ppersons[i]->display();
    }
    return true;
}

bool subMenu(Person ** ppersons, Person * persons)
{
    while (1)
    {
        std::cout << "\n\n\
        Ausgabemen" << ue <<'\n'<<"\
        1.) Alle ausgeben\n\
        2.) Jahrgang ausgeben\n\
        3.) Zur"<<ue<<"ck\n\
        ";

        char input;
        std::cin >> input;
        switch (input)
        {
        case '1':
            if (!displayPersons(ppersons, persons))
                std::cout << "      Keine Daten vorhanden\n";
            break;
        case '2': 
            if (!displayAgeCohort(ppersons, persons))
                std::cout << "      Keine Daten vorhanden\n";
            break;
        case '3': return true;
        default: std::cout << "Ung"<<ue<<"ltige Eingabe\n";;
        }
    }
}

bool displayAgeCohort(Person ** ppersons, Person * persons)
{
    char input;
    std::cout << "Jahrgang: ";
    std::cin >> input;
    if (std::cin.fail())
    {
        std::cout << "      Ung"<<ue<<"ltige Eingabe" << std::endl;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        return false;
    }
    return false;
}

void messageContinue(const std::string message)
{
    std::cout << kOffset << message;
    std::cout << kOffset << "Weiter mit Return\n";
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cin.get();
    system("cls");
}
