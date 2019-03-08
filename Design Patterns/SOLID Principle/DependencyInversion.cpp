#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

enum class Relationship
{
    parent,
    child,
    sibling,
};

struct Person
{
    string name;
};

struct RelationshipBrowser
{
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};

// struct Relationships // low-level module/construct
struct Relationships : RelationshipBrowser
{
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> find_all_children_of(const string& name)
    {
        vector<Person> result;
        for (auto&& [first, rel, second]: relations)
        {
            if (first.name == name && rel == Relationship::parent)
            {
                result.push_back(second);
            }
        }
        return result;
    }
};

struct Research // hihg-level module
{
    Research(RelationshipBrowser& browser)
    {
        for (auto& child : browser.find_all_children_of("Jhon"))
        {
            cout << "Jhon has a child called " << child.name << endl;
        }
    }
    // Research(Relationships& relationships)
    // {
    //     auto& relations = relationships.relations;
    //     for (auto&& [first, rel, second] : relations)
    //     {
    //         if (first.name == "Jhon" && rel == Relationship::parent)
    //         {
    //             cout << "Jhon has a child called " << second.name << endl;
    //         }
    //     }
    // }
};

int main(int argc, char const *argv[])
{
    Person parent{"Jhon"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);

    return 0;
}
