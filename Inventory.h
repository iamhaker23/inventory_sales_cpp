#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "StockItem.h"

//using namespace std;

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::sort;

#ifndef INVENTORY_H
    
    #define	INVENTORY_H

    
    class Inventory{
    
        private:
            vector<StockItem*> items;
        
        public:
            
            //Refactor into static lib
            static vector<string> splitString(string input, char delimiter);

            Inventory(vector<string> csvData);
            ~Inventory();
            
            void sort();
            
            void printOut();
            
            StockItem* getMostStockedItem();
            
            int checkTransistorStock(string typeFilter);
            
            double getTotalResistance(bool onlyCountStocked);
            
            vector<StockItem*> getStockMoreExpensive(int threshold);
            
            
            
    
    };

#endif	/* INVENTORY_H */

