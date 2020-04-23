#include <string>
#include <iostream>
using namespace std;
namespace family{
    class Tree{
        string root;
        Tree* _father;
        Tree* _mother;
        string findRe(int great, bool mother);
        bool addFatherRe(string name, string father);
        bool addMotherRe(string name, string mother);
        bool removeRe(string& name);
        public:
        Tree(string name);
        Tree& addFather(string name, string father);
        Tree& addMother(string name, string mother);
        void remove(string name);
        void display();
        string relation(string name);
        string find(string relation);
    };
}