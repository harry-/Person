#include "Person.h"
#include <limits>

bool menu(Person ** ppersons, Person * persons);
bool insertPerson(Person** ppersons, Person* persons);
bool displayPersons(Person** ppersons, Person* persons);
bool subMenu(Person ** ppersons, Person * persons);
bool displayAgeCohort(Person**ppersons, Person *persons);

bool menu(Person * persons);
bool insertPerson(Person* persons);
bool displayPersons(Person* persons);
bool subMenu(Person * persons);
bool displayAgeCohort(Person *persons);

void messageContinue(const std::string message);
void messageContinue();
bool errorMessage(std::string message);
void clearCin();

int customStrCmp(char * s1, char *s2);
bool displayLastName(Person * persons);

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
	const char* kOffsetOnly = "\t\t\t";
    const std::int32_t cIntMax = std::numeric_limits<std::int32_t>::max();
	const int kMaxLength = 50;
}

int main()
{
    Person person;
    person.setYearOfBirth(20);

    Person person2("ich", "selbst", 3);
    Person person3(person2);

    person = person3;

	
	
	//Person* ppersons[kMaxObjects];
    Person persons[kMaxObjects];
    //Person ** persons3;
    //for (size_t i = 0; i < kMaxObjects; i++)
    //{
    //    //persons[i] = *(new Person());
    //    ppersons[i] = new Person();
    //}

    //menu(ppersons, persons);
    menu(persons);

    //for (size_t i = 0; i < person.getCount(); i++)
    //{
    //    //delete persons[i];
    //    delete ppersons[i];
    //}

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //checks for memoryleaks
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
			system("cls");
            if (!subMenu(ppersons, persons))
                messageContinue("Menue konnte nicht aufgerufen werden");
			
            break;
        case '3': return true;
        default: messageContinue("Menue konnte nicht aufgerufen werden");
            break;
        }

    }
}


bool insertPerson(Person** ppersons, Person* persons)
{
    std::string firstName;
    std::string lastName;
    int year_of_birth;
    
    if (!(persons->getCount() < kMaxObjects))
    {
        std::cout << kOffset << "Keine freien Datens" << ae << "tze";
        return false;
    }

    std::cout << kOffset << "Vorname eingeben:";
    std::cin >> firstName;

    if (!std::cin)
    {
        std::cout << kOffset << "Ung"<<ue<<"ltige Eingabe";
        std::cin.clear();
        std::cin.ignore(cIntMax, '\n');
        return false;
    }
    std::cout << kOffsetOnly << "Nachname eingeben: ";
    std::cin >> lastName;
    if (!std::cin)
    {
        std::cout << kOffset << "Ung"<<ue<<"ltige Eingabe";
        std::cin.clear();
        std::cin.ignore(cIntMax, '\n');
        return false;
    }
    std::cout << kOffsetOnly << "Geburtsjahr eingeben: ";
    std::cin >> year_of_birth;
    if (std::cin.fail())
    {
        std::cout << kOffset << "Ung"<<ue<<"ltige Eingabe";
        //std::cin.seekg(0, std::ios::end);
        std::cin.clear();
        std::cin.ignore(cIntMax, '\n');
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
	if (!persons->getCount())
		return false;
	
	for (int  i = 0; i < persons[0].getCount(); i++)
    {
		std::cout << '\n' << kOffsetOnly;
		persons[i].display();
		std::cout << kOffsetOnly;
        ppersons[i]->display();
    }
    return true;
}

bool subMenu(Person ** ppersons, Person * persons)
{
    while (1)
    {

		std::cout << "\n\n" <<
		kOffset << "Ausgabemen" << ue <<
		kOffset << "1.) Alle ausgeben" <<
		kOffset << "2.) Jahrgang ausgeben" <<
		kOffset << "3.) Zur" << ue << "ck" <<
		kOffset << "Auswahl: ";

        char input;
        std::cin >> input;
        switch (input)
        {
        case '1':
            if (!displayPersons(ppersons, persons))
                std::cout << kOffset << "Keine Daten vorhanden";
			messageContinue();
            break;
        case '2': 
            if (!displayAgeCohort(ppersons, persons))
                std::cout << kOffset << "Keine Daten vorhanden";
			messageContinue();
            break;
        case '3': 
			system("cls");
			return true;
        default: std::cout << kOffset << "Ung"<<ue<<"ltige Eingabe";
        }
    }
}

bool displayAgeCohort(Person ** ppersons, Person * persons)
{
    int input;
    std::cout << kOffset << "Jahrgang: ";
    std::cin >> input;
    if (std::cin.fail())
    {
        std::cout << kOffset << "Ung"<<ue<<"ltige Eingabe";
        std::cin.clear();
        std::cin.ignore(cIntMax, '\n');
        return false;
    }
	bool found_at_least_one = false;
	for (int i = 0; i < persons[0].getCount(); i++)
	{
		if (!(persons[i].getYearOfBirth() == input))
			continue;
		std::cout << '\n' << kOffsetOnly;
		persons[i].display();
		std::cout << kOffsetOnly;
		ppersons[i]->display();
		found_at_least_one = true;
	}
	return found_at_least_one;
}

void messageContinue(const std::string message)
{
    std::cout << kOffset << message;
	messageContinue();
}

void messageContinue()
{
	std::cout << kOffset << "Weiter mit Return\n";
	std::cin.clear();
	std::cin.ignore(cIntMax, '\n');
	std::cin.get();
	system("cls");
}


bool menu(Person * persons)
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
            if (insertPerson(persons))
                messageContinue("Neuer Datensatz hinzugefuegt");
            else
                messageContinue("Datensatz konnte nicht hinzugefuegt werden");
            break;
        case '2':
			system("cls");
            if (!subMenu(persons))
                messageContinue("Menue konnte nicht aufgerufen werden");
			
            break;
        case '3': return true;
        default: messageContinue("Menue konnte nicht aufgerufen werden");
            break;
        }

    }
}


bool insertPerson(Person* persons)
{
    std::string firstName;
    char lastName[kMaxLength];
    int year_of_birth;
    
	system("cls");

    if (!(persons->getCount() < kMaxObjects))
    {
        std::cout << kOffset << "Keine freien Datens" << ae << "tze";
        return false;
    }

    std::cout << kOffset << "Vorname eingeben: ";
    std::cin >> firstName;

	if (!std::cin)
		return errorMessage("Ungueltige Eingabe");

	clearCin();


    std::cout << kOffsetOnly << "Nachname eingeben: ";
    std::cin.getline(lastName, kMaxLength);
	if (!std::cin)
		return errorMessage("Ungueltige Eingabe");

    std::cout << kOffsetOnly << "Geburtsjahr eingeben: ";
    std::cin >> year_of_birth;
	if (std::cin.fail())
		return errorMessage("Ungueltige Eingabe");

    Person person(firstName.c_str(), lastName, year_of_birth);

    persons[person.getCount()].setFirstName(firstName.c_str());
    persons[person.getCount()].setLastName(lastName);
    persons[person.getCount()].setYearOfBirth(year_of_birth);

    person.raiseCount();
}

bool displayPersons(Person * persons)
{
	if (!persons->getCount())
		return false;

	system("cls");

	for (int  i = 0; i < persons[0].getCount(); i++)
    {
		std::cout << '\n' << kOffsetOnly;
		persons[i].display();
    }
    return true;
}

bool subMenu(Person * persons)
{
    while (1)
    {

		std::cout << "\n\n" <<
		kOffset << "Ausgabemen" << ue <<
		kOffset << "1.) Alle ausgeben" <<
		kOffset << "2.) Jahrgang ausgeben" <<
		kOffset << "3.) Personen mit gleichen Nachnamen ausgeben" <<
		kOffset << "4.) Zur" << ue << "ck" <<
		kOffset << "Auswahl: ";

        char input;
        std::cin >> input;
        switch (input)
        {
        case '1':
            if (!displayPersons(persons))
                std::cout << kOffset << "Keine Daten vorhanden";
			messageContinue();
            break;
        case '2': 
            if (!displayAgeCohort(persons))
                std::cout << kOffset << "Keine Daten vorhanden";
			messageContinue();
            break;
		case '3':
			if (!displayLastName(persons))
				std::cout << kOffset << "Keine Daten vorhanden";
			messageContinue();
			break;
        case '4': 
			system("cls");
			return true;
        default: std::cout << kOffset << "Ung"<<ue<<"ltige Eingabe";
        }
    }
}

bool displayAgeCohort(Person * persons)
{
    int input;
	system("cls");
    std::cout << kOffset << "Jahrgang: ";
    std::cin >> input;
	if (std::cin.fail())
		return errorMessage("Ungueltige Eingabe");
		
    
	bool found_at_least_one = false;
	for (int i = 0; i < persons[0].getCount(); i++)
	{
		if (!(persons[i].getYearOfBirth() == input))
			continue;
		std::cout << '\n' << kOffsetOnly;
		persons[i].display();
		found_at_least_one = true;
	}
	return found_at_least_one;
}

/* Fehlermeldung, Buffer leeren, immer false zurueckgeben (wird durchgereicht) */

bool errorMessage(std::string message)
{
	std::cout << kOffset << message;
	clearCin();
	return false;
}

/* den Einlesebuffer zuruecksetzen */

void clearCin()
{
	std::cin.clear();
	std::cin.ignore(cIntMax, '\n');
}

bool displayLastName(Person * persons)
{
	char input[50];
	system("cls");
	clearCin();
	std::cout << kOffset << "Nachname: ";
	std::cin.getline(input, kMaxLength);
	if (std::cin.fail())
		return errorMessage("Ungueltige Eingabe");


	bool found_at_least_one = false;
	for (int i = 0; i < persons[0].getCount(); i++)
	{
		if (customStrCmp(persons[i].getLastName(),input))
			continue;
		std::cout << '\n' << kOffsetOnly;
		persons[i].display();
		found_at_least_one = true;
	}

	return found_at_least_one;
}

int customStrCmp(char * s1, char *s2)
{
	for (int i = 0;; ++i)
	{
		if (s1[i] < s2[i]) 
			return -1;
		else if (s1[i] > s2[i]) 
			return 1;
		if (!s1[i]) 
			return 0;
	}
}
