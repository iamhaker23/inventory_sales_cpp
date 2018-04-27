
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <string>
#include <vector>

#include "inventory.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

static vector<string> readLines(FILE* fptr);

int main(int argc, char** argv) 
{
    
    cout << "Loading inventory.txt" << "\n***********************" << endl;
    
    //load file
    FILE* fptr = fopen("inventory.txt", "r");
    if (!fptr) {
        cout << "Failed to open inventory.txt! Quitting." << endl;
        EXIT_FAILURE;
    }
    
    //object will be destroyed when it goes out of scope (end of this function)
    vector<string> fileContents = readLines(fptr);
    
    //cleanup
    fclose(fptr);
    delete fptr;
    
    //verbose, report lines read from file
    cout << "Read " << fileContents.size() << " lines." << endl;
    
    //create inventory from file
    Inventory* inventory = new Inventory(fileContents);
    
    //QUERIES
    //Print a list of the inventory, sorted in order of increasing price.
    
    cout << "\nANSWER 0: Printing Inventory Sorted By Price\n" << "\n***********************" << endl;
    inventory->sort();
    inventory->printOut();
    
    //What is the component with the largest number of components in stock?
    StockItem* mostStockedItem = inventory->getMostStockedItem();
    cout << "\nANSWER 1: The item with the highest stock count is:" << endl;
    cout <<  mostStockedItem->toString() << endl;
    
    //How many NPN transistors does Chartlins have in stock?
    int npnTransistors = inventory->checkTransistorStock("NPN");
    cout << "\nANSWER 2: " << npnTransistors << " NPN Transistors in stock." << endl;
    
    //What is the total resistance of all of the resistors in stock?
    double resistance = inventory->getTotalResistance(true);
    cout << "\nANSWER 3: The total resistance of all (in-stock) resistors is ";
    
    cout.precision(2);
    
    cout << fixed << resistance << " ohms" << endl;
    
    //How many stock items have unit prices above 10p?
    int totalAboveTenPence = (inventory->getStockMoreExpensive(10)).size();
    cout << "\nANSWER 4: The inventory contains " << totalAboveTenPence << " items above 10p." << endl;
    
    //explicitly managing inventory object lifespan
    delete inventory;
    
    return EXIT_SUCCESS;
}


vector<string> readLines(FILE* fptr){
    
    vector<string> output;
    
    string line = "";
    
    char c = fgetc(fptr);
    do {
        char peek = fgetc(fptr);
        if (c){
            
            if ((c != '\n' && c!= '\r' && peek != EOF)){
                line.append(string(1, c));
                
            }else{ 
                if (line != ""){
                    
                    //add the final character
                    if (peek == EOF) line.append(string(1, c));
                                       
                    output.push_back(line);
                    
                }
                line = "";
            }
        }
        c = peek;
    }while(c != EOF);
    
    
    return output;
}