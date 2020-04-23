#include "FamilyTree.hpp"
using namespace std;
string grn="grand",gre="great-";
namespace family{
    
    bool Tree::addFatherRe(string name, string father){
        if(name.compare(root)==0&&_father!=NULL)throw exception();
        if(this->_father!=NULL && (this->_father->addFatherRe(name,father)==true)){return true;}
        
        if(this->_father==NULL && this->root.compare(name)==0){
            
            _father= new Tree(father);
            cout<<"  father "+father+"  "+_father->root;
            // printf("true");
            return true;
        }
        if(_mother!=NULL && true==(_mother->addFatherRe(name,father))){return true;}
        printf("  false  ");
        return false;
    }
    bool Tree::addMotherRe(string name, string mother){
        if(_mother!=NULL&&name.compare(root)==0)throw "mmmm";
        if(_mother!=NULL && true==(_mother->addMotherRe(name,mother))){return true;}
        if(_mother==NULL && root==name){
            _mother= new Tree(mother);
            // printf("  new  ");
            cout<<"  mother "+mother+"  "+_mother->root;

            return true;
        }
        
        if(_father!=NULL && true==(_father->addMotherRe(name,mother))){return true;}
        printf("  false  ");
        return false;
    }
    bool Tree::removeRe(string& name){
        if(_mother&&_mother->root==name){
            delete _mother;
            return true;
        }
        if(_father&&_father->root==name){
            delete _father;
            return true;
        }
        if(_mother!=NULL && _mother->removeRe(name)==true)return true;
        if(_father!=NULL && _father->removeRe(name)==true)return true;
        return false;
    }
    string Tree::findRe(int great, bool mother){
        string ans="";
        if(great>0){
            if(_mother!=NULL)ans= this->_mother->findRe(great-1,mother);
            if(_father!=NULL && ans.empty())ans= _father->findRe(great-1,mother);
            cout<<" - "+ans+" - ";
            return ans;
        }
        if(mother&&_mother!=NULL)return _mother->root;
        if(!mother&&_father!=NULL)return _father->root;
        return ans;
    }


    Tree::Tree(string name):_father(NULL),_mother(NULL),root(name){;}

    Tree& Tree::addFather(string name, string father){
        printf("out");
        bool b=this->addFatherRe(name,father);
        printf("%i",b);
        if(b==true)return *this;
       
        printf("falseout");
        __throw_runtime_error("c");
    
    }
    Tree& Tree::addMother(string name, string mother){
        printf("outm");
        if(true==(this->addMotherRe(name,mother)))return *this;
        __throw_runtime_error("c");
    }
    void Tree::remove(string name){
        if(root.compare(name)==0){
            delete this;
            return;
        }
        if(removeRe(name))return;
        throw exception();
    }
    void Tree::display(){;
    }
    string Tree::relation(string name){
        cout<<"   "+root+"   ";
        if(this->_mother!=NULL && _mother->root==name){cout<<" mom "<<_mother->root;return "mother";}
        if(this->_father!=NULL && _father->root==name){cout<<" pop "<<_father->root;return "father";}
        string ans;
        if(this->_mother!=NULL){
            ans=_mother->relation(name);
            cout<<ans+"  here!!  ";
            if(ans.length()==6) return grn+ans;
            if(ans[0]=='g')return gre+ans; 
        }
        if(this->_father != NULL){
            ans=_father->relation(name);
            if(ans.length()==6)return grn+ans;
            if(ans[0]=='g')return gre+ans; 
        }
        if(root==name)return "me";
        cout<<"error-"+ans+"- ";
        if(ans.empty())ans="unrelated";
        return ans;
    }
    string Tree::find(string relation){
        string ans="";
        int great,grand=0;
        bool father=false,mother=false;
        for(great=0;relation.find_first_of("great-")==0;great++){
            relation=relation.substr(5);}
        if(relation.find_first_of("grand")==0){
            grand++;
            relation=relation.substr(4);
        }
        if(relation.length()==6){
            if(relation.compare("mother")==0)mother=true;
            else if(relation.compare("father")==0)father=true;
            if((mother||father)&&(grand=1||great==0)){
                ans+= this->findRe(great,mother);
                cout<<" f "+ans+" f "<<!ans.empty();
                if(!ans.empty())return ans;
                cout<<" ! "+ans+" ! ";
            }   
        }
        cout<<" ff "+ans+" f ";
        if(ans.empty())throw "k";
        // return ans;
    
    }
   
}