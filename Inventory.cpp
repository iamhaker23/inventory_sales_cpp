
#include "Inventory.h"

Inventory::Inventory(vector<string> csvData){
    
    
    for (auto i : csvData){
        
        vector<string> row = splitString(i, ',');
        
        StockItem* current = StockItem::parse(row);
        
        this->items.push_back(current);
    }
    
    
}

void Inventory::sort(bool ascendingPrice){
    std::sort(items.begin(), items.end(), StockItem::compare);
}
            
void Inventory::printOut(){
    for (StockItem* i : this->items){
        
        cout << i->toString() << endl;
        
    }
}

vector<string> Inventory::splitString(string input, char delimiter){
    
    
    vector<string> output;
    
    if (input.length() < 1) return output;
    
    string part = "";
    int currentChar = 0;
    char c = input[currentChar];
    int str_len = input.length();
    
    do {
        
        if (c){
            
            if(c != delimiter && c != ' ' && c != '\n' && c != '\r' && int(c) != int(0x1E) && int(c) != int(0x01) && (currentChar != str_len-1) ){
                part.append(string(1, c));
            }else{
                if (part != "" || (currentChar == str_len-1 && c != delimiter && c != ' ' && c != '\n' && c != '\r' && int(c) != int(0x1E) && int(c) != int(0x01)) ){
                    
                    //if there's a part to append or we're on the last character and it's not a space
                    
                    if (currentChar == str_len-1){
                        part.append(string(1, c));
                    }
                    
                    output.push_back(part);
                    part = "";
                }
            }
        }
        
        
        c = input[++currentChar];
    }while(currentChar < str_len);
    
    
    return output;
}

StockItem* Inventory::getMostStockedItem(){
    
    StockItem* mostStocked = nullptr;
    
    for (StockItem* item : items){
        
        if (item->isValid()){
            if (!mostStocked || mostStocked->getStockLevel() < item->getStockLevel()){
                mostStocked = item;
            }
        }
    }
    
    return mostStocked;
    
}

int Inventory::checkTransistorStock(string typeFilter){
    
    int total = 0;
    
    for (StockItem* item : items){
        if (item->isValid() && item->getType()=="transistor"){
            Transistor* transistor = (Transistor*)item;
            
            if (transistor->getConfiguration() == typeFilter){
                total = total + transistor->getStockLevel();
            }
        }
    }
    
    return total;
    
}


double Inventory::getTotalResistance(bool onlyCountStocked){
    
    double total = 0.0f;
    
    for (StockItem* item : items){
        if (item->isValid() && item->getType()=="resistor"){
            Resistor* resistor = (Resistor*)item;
            
            if (!onlyCountStocked || (onlyCountStocked && resistor->getStockLevel() > 0)){
                
                double currTotal = (resistor->getResistance()*(double(resistor->getStockLevel())));
                                
                total = total + currTotal;
            }
        }
    }
    
    return total;
    
}

vector<StockItem*> Inventory::getStockMoreExpensive(int threshold){
    
    vector<StockItem*> expensiveItems;
    
    for (StockItem* item : items){
        if (item->isValid() && item->getPrice() > threshold){
            expensiveItems.push_back(item);
        }
    }
    
    return expensiveItems;
    
}
