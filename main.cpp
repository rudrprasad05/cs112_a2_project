#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "List.h"
#include "VisaApplication.h"
#include "Node.h"
#include "Data.h"

using namespace std;

void discard_line(ifstream& in);
bool check_white_space(string input1);
void print_success_failure(string type, List& myList);
void remove_success_failure(List& myList);
void read_file(ifstream& in, List& myList);

int main()
{

    ifstream in;
    ofstream out;

    List myList;


    in.open("applications.txt", ios::in);
    // out.open("applications_outcome.txt", ios::out);

    read_file(in, myList);
    cout << "1" << endl;
    myList.printList();

    cout << "2" << endl;
    print_success_failure("success", myList);

    cout << "3" << endl;
    print_success_failure("failure", myList);

    cout << "4" << endl;
    remove_success_failure(myList);
    in.close();
    // out.close();
    
}

void discard_line(ifstream& in)
{
    char c;

    do
        in.get(c);
    while (c != '\n');
}

void remove_success_failure(List& myList){

    
    if (myList.isEmpty())
        cout << "The list is empty\n";
    else{
        Node *pHead = myList.getpHead();
        Node *pNode = pHead;
        Node *temp = pNode;

        for (pNode = pHead; pNode != NULL; pNode = myList.nextNode(pNode)){
            
            Data *d = pNode->getData();
            
            VisaApplication *v = dynamic_cast<VisaApplication*>(d);
            
            if(v->result == "success" || v->result == "failure"){
                myList.removeNode(pNode);
                pNode = temp;

            }
            else{
                continue;
            }
        }
    }
    myList.printList();

}

void print_success_failure(string type, List& myList){

    Node *pHead = myList.getpHead();
    Node *pNode = pHead;
    if (myList.isEmpty())
        cout << "The list is empty\n";
    else
        for (pNode = pHead; pNode != NULL; pNode = myList.nextNode(pNode)){
            
            Data *d = pNode->getData();
            VisaApplication *v = dynamic_cast<VisaApplication*>(d);
            

            if(v->result == type){
                v->print();
            }
            else{
                continue;
            }
        }
}

void read_file(ifstream& in, List& myList){

    if(in.fail()){
        cout << "invalid file or pathname" << endl;
        return;
    }

    discard_line(in);

    while(!in.eof()){
        
        VisaApplication *v = new VisaApplication;

        in >> v->visa_type;
        in >> v->invoice_no;
        in >> v->surname;
        in >> v->first_name;
        in >> v->contact;
        in >> v->status;
        in >> v->result;

        if(check_white_space(v->visa_type)){
            break;
        }
        
        myList.appendNode(v);


    }

}

bool check_white_space(string input1){
    if(input1 == "" ){
        return true;
    }
    else return false;
}


