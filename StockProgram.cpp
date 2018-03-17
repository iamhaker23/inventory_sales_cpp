
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
    
    cout << "1. Loading inventory.txt" << "\n***********************" << endl;
    
    //load file
    FILE* fptr = fopen("inventory.txt", "r");
    if (!fptr) {
        cout << "Failed to open inventory.txt! Quitting." << endl;
        EXIT_FAILURE;
    }
    
    vector<string> fileContents = readLines(fptr);
    
    
    fclose(fptr);
    
    cout << "Read " << fileContents.size() << " lines." << endl;
    
    //create inventory from file
    Inventory* inventory = new Inventory(fileContents);
    
    
    //QUERIES
    
    //Print a list of the inventory, sorted in order of increasing price.
    
    cout << "\n2. Printing Inventory Sorted By Price\n" << "\n***********************" << endl;
    inventory->sort(true);
    inventory->printOut();
    
    //What is the component with the largest number of components in stock?
    StockItem* mostStockedItem = inventory->getMostStockedItem();
    cout << "The item with the highest stock count is " << mostStockedItem->toString() << endl;
    
    //How many NPN transistors does Chartlins have in stock?
    //int npnTransistors = inventory->checkTransistorStock("NPN");
    //cout << "Chartlins has " << npnTransistors << " NPN Transistors in stock." << endl;
    
    //What is the total resistance of all of the resistors in stock?
    //float resistance = inventory->getTotalResistance(true);
    //cout << "The total resistance of all (in-stock) resistors is " << resistance << "." << endl;
    
    //How man stock items have unit prices above 10p?
    //int totalAboveTenPence = (inventory->getStockMoreExpensive(10))->getSize();
    //cout << "The inventory contains " << totalAboveTenPence << " items above 10p." << endl;
    
    //Note: This would happen implicitly when object goes out of scope, in about 2 lines
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