#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

struct Person {
    string name;
    vector<Person*> children;

    Person(const string& n) : name(n) {}
};

struct Relationship {
    string person1;
    string person2;
    Relationship(const string& p1, const string& p2) : person1(p1), person2(p2) {}
};


vector<Relationship> findRelatives(Person* person) {
    vector<Relationship> relatives;

    // Рекурсивный обход родственных связей
    function<void(Person*, Person*)> traversal_recursion = [&](Person* human, Person* relative) {
        // Добавляем родственную связь
        relatives.push_back({ human->name, relative->name });

        // Ищет родственников с помощью рекурсии
        for (Person* child : human->children) {
            traversal_recursion(child, relative);
        }
    };

    // Поиск родственных связей для данного человека
    traversal_recursion(person, person);
    return relatives;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Создание жителей и их детей
    Person* john = new Person("John");
    Person* alice = new Person("Alice");
    Person* bob = new Person("Bob");
    Person* eva = new Person("Eva");
    Person* caleb = new Person("Caleb");

    // Привязка детей к жителям
    john->children.push_back(alice);
    alice->children.push_back(bob);
    alice->children.push_back(eva);
    bob->children.push_back(caleb);

    // Поиск родственных связей для указанного жителя
    vector<Relationship> relatives = findRelatives(john);

    // Вывод родственных связей
    cout << "Родственные связи для John:" << endl;
    for (const auto& rel : relatives) {
        cout << rel.person1 << " и " << rel.person2 << endl;
    }
    return 0;
}
