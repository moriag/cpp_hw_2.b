#include "FamilyTree.hpp"
using namespace std;
string grn="grand",gre="great-";
namespace family{
    

    bool Tree::addFatherRe(string name, string father){

        if(_father==NULL && root==name){//found place to add
            _father= new Tree(father);//add father  
            return true;
        }
        //search on father's side
        if(_father!=NULL && (_father->addFatherRe(name,father)))return true;
        //search on mother's side
        if(_mother!=NULL && (_mother->addFatherRe(name,father)))return true;
        //did not find
        return false; 
    }
    
    
    bool Tree::addMotherRe(string name, string mother){
        
        if(_mother==NULL && root==name){//found place to add
            _mother= new Tree(mother);//add mother
            return true;
        }
         //search on mother's side
        if(_mother!=NULL && (_mother->addMotherRe(name,mother)))return true;
        //search on father's side
        if(_father!=NULL && (_father->addMotherRe(name,mother)))return true;
        //did not find
        return false;
    }
    
    
    bool Tree::removeRe(string& name){
        if(_mother&&_mother->root==name){//found name
            delete _mother;//remove "name"
            _mother=NULL;
            return true;
        }
        if(_father&&_father->root==name){//found name
            delete _father;//remove "name"
            _father=NULL;
            return true;
        }
        //search on mother's side
        if(_mother!=NULL && _mother->removeRe(name))return true;
        //search on father's side
        if(_father!=NULL && _father->removeRe(name))return true;
        return false;//did not find
    }
    
    
    string Tree::findRe(int great, bool mother){
        string ans="";
        if(great>0){//not yet the generation to search in
        //go up a generation to mother
            if(_mother!=NULL)ans= this->_mother->findRe(great-1,mother);
        //if not found go up a generation to father 
            if(_father!=NULL && ans.empty())ans= _father->findRe(great-1,mother);
            //not found
            return ans;
        }
        //in generation to search
        if(mother&&_mother!=NULL)return _mother->root;//if looking for a mother
        if(!mother&&_father!=NULL)return _father->root;//if looking for a father
        return ans;//not found
    }
    
    //constructor 
    Tree::Tree(string name):_father(NULL),_mother(NULL),root(name){;}
    
    
    Tree::~Tree(){
        if(_mother!=NULL)delete _mother;
        _mother=NULL;
        if(_father!=NULL)delete _father;
        _father=NULL;
    }


    Tree& Tree::addFather(string name, string father){
        //go to boolean recursion
        if(this->addFatherRe(name,father)==true)return *this;
        __throw_runtime_error("cant add father");
    }
    
    
    Tree& Tree::addMother(string name, string mother){
        //go to boolean recursion 
        if(true==(this->addMotherRe(name,mother)))return *this;
        __throw_runtime_error("cant add mother");
    }


    void Tree::remove(string name){
        if(removeRe(name))return;//go to recursion
        throw exception();
    }
    
    
    void Tree::display(){
        cout << "Name: " <<root;
        if(_father!=NULL)cout<<"\tFather: "<<_father->root;
        if(_mother!=NULL)cout<<"\tMother: "<<_mother->root;
        cout<<endl;
        if(_father!=NULL)_father->display();
        if(_mother!=NULL)_mother->display();
    }

    
    
    string Tree::relation(string name){
        
        if(_mother!=NULL && _mother->root==name)return "mother";//found name..
        if(_father!=NULL && _father->root==name)return "father";//
        string ans;
        if(this->_mother!=NULL){
            ans=_mother->relation(name);//relation to mother

            if(ans.length()==6) return grn+ans;//grandmother
            if(ans[0]=='g')return gre+ans;//grate-...grandmother 
        }
        if(this->_father != NULL){
            ans=_father->relation(name);//relation to father

            if(ans.length()==6)return grn+ans;//grandfather
            if(ans[0]=='g')return gre+ans; //great-...grandfather
        }
        if(root==name)return "me";//found me
     
        return "unrelated";//didnt find
        
    }


    string Tree::find(string relation){
        string ans="";
        int great,grand=0;
        bool father=false,mother=false;
        //count generations to go back 
        for(great=0;relation.find("great-")==0;great++){
            relation=relation.erase(0,6);
        }
        if(relation.find("grand")==0){
            grand++;
            relation=relation.erase(0,5);
        }
        if(relation.length()==6){//length of mother\father
            
            if(relation=="mother")mother=true;
            else if(relation=="father")father=true;
            //need one parent, if no grand, #"great-" must be 0
            if((mother||father)&&(grand==1||great==0)){
                ans= this->findRe(great+grand,mother);
                        // #generations  , gender of last in line
            
                if(!ans.empty())return ans;//found in tree
               
            }   
        }
  
        throw "not found in tree";//including wrong format input
    
    }
   
}