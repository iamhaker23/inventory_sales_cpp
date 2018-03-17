
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
