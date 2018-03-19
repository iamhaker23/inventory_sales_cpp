#include <basetsd.h>
#include <sstream>

#include "StockItem.h"

StockItem::StockItem(vector<string> row){
    //type, code, stock, price, unit/description
        
    this->valid = false;
    
    try{
        
        this->type = row.at(0);
        this->code = row.at(1);
        this->stock = stringToInt(row.at(2));
        this->unit_price = stringToInt(row.at(3));
        
        this->valid = true;
    }catch(std::out_of_range e){
        cout << "Could not parse line: " << row.front() << ":" << row.size() << endl;
        cout << "\t" << row.at(0) << row.at(1) << row.at(2) << endl;
    }
}

StockItem::StockItem(){
    //type, code, stock, price, unit/description
        
    this->valid = false;
    this->code = "";
    this->stock = -1;
    this->unit_price = -1;
    this->type = "";
    
}

bool StockItem::compare (StockItem* i,StockItem* j) { 
    return (i->getPrice() < j->getPrice()); 
}

string StockItem::toString(){
    string output = "";
    
    if (this->valid){
        output.append(this->type);
        output.append(",\t");
        output.append(this->code);
        output.append(",\t");
        output.append(intToString(this->stock));
        output.append(",\t");
        output.append(intToString(this->unit_price));
    }else{
        output = "This object is invalid.";
    }
    
    return output;
}

int StockItem::stringToInt(string val){
    return stoi(val);
}
float StockItem::stringToFloat(string val){
    return stof(val);
}
double StockItem::stringToDouble(string val){
    return stod(val);
}

string StockItem::floatToString(float val){
    stringstream ss;
    ss.precision(1);
    
    ss << fixed << val;
    return ss.str();
}
string StockItem::doubleToString(double val){
    stringstream ss;
    ss.precision(12);
    
    ss << fixed << val;
    return ss.str();
}

string StockItem::intToString(int val){
    stringstream ss;
    ss << val;
    return ss.str();
}

double StockItem::power(float base, int index){
    double output = 1.0;
    if (index > 0){
        while(index>0){
            output = output * base;
            index--;
        }   
    }else if (index < 0){
        while(index<0){
            output = output / base;
            index++;
        }   
    }
    return output;
}
StockItem* StockItem::parse(vector<string> row){
    
    StockItem* item;
    
    string type = row.front();
    
    if (type=="capacitor"){
        item = new Capacitor(row);
    }
    else if (type=="transistor"){
        
        item = new Transistor(row);
    }
    else if (type=="resistor"){
        
        item = new Resistor(row);
    }
    else if (type=="IC"){
        
        item = new IC(row);
    }
    else if (type=="diode"){
        item = new StockItem(row);
    }else{
        item = new StockItem();
    }
        
    return item;
}

string StockItem::getType(){
    return this->type;
}

int StockItem::getPrice(){
    return this->unit_price;
}

int StockItem::getStockLevel(){
    return this->stock;
}

string StockItem::getCode(){
    return this->code;
}
bool StockItem::isValid(){
    return this->valid;
}

            
Transistor::Transistor(vector<string> row) : StockItem(row){
    try{
        
        this->configuration = row.at(4);
        
    }catch(std::out_of_range e){
        if (row.size() >= 1){
            cout << "Could not parse line:" << row.front() << endl;
        }else{
            cout << "Could not parse line with no data." << endl;
        }
    }
}

string Transistor::getConfiguration(){
    return this->configuration;
}
string Transistor::toString(){
    string output = StockItem::toString();
    output.append(",\t");
    output.append(this->getConfiguration());
    return output;
}
           

Resistor::Resistor(vector<string> row) : StockItem(row){
    try{
        
        this->resistance = parseResistance(row.at(4));
        this->resistance_orig = row.at(4);
        
    }catch(std::out_of_range e){
        if (row.size() >= 1){
            cout << "Could not parse line:" << row.front() << endl;
        }else{
            cout << "Could not parse line with no data." << endl;
        }
    }
}

double Resistor::getResistance(){
    return this->resistance;
}

string Resistor::toString(){
    string output = StockItem::toString();
    output.append(",\t");
    output.append(doubleToString(this->getResistance()));
    output.append(",\t");
    output.append(this->resistance_orig);
    return output;
}

double Resistor::parseResistance(string val){
    
    string prefix = "";
    string suffix = "";
    char unit = char(0);
    
    bool addToSuffix = false;
    
    
    for (char c : val){
        int int_val = int(c);
        if (c == 'R' || c=='M' || c=='K'){
            addToSuffix = true;
            unit = c;
        }else if (int_val >= 48 && int_val <= 57){
            //numeric character
            if (addToSuffix){
                suffix.append(string(1, c));
            }else{
                prefix.append(string(1, c));
            }
        }//else skip
        
        
    }
    
    int pow = 0;
    
    switch(unit){
        case('M'):
            pow = 6;
            break;
        case('K'):
            pow = 3;
            break;
        default:
            break;
    }
    
    double multiplier = 1.0;
    int suffix_len = suffix.length();
    pow = pow - suffix_len;
    
    multiplier = power(10.0f, pow);
    
    prefix.append(suffix);
    return stringToDouble(prefix) * multiplier;
}

Capacitor::Capacitor(vector<string> row) : StockItem(row){
    try{
        
        this->capacitance = parseCapacitance(row.at(4));
        this->capacitance_orig = row.at(4);
        
    }catch(std::out_of_range e){
        if (row.size() >= 1){
            cout << "Could not parse line:" << row.front() << endl;
        }else{
            cout << "Could not parse line with no data." << endl;
        }
    }
}
double Capacitor::getCapacitance(){
    return this->capacitance;
}
string Capacitor::toString(){
    string output = StockItem::toString();
    output.append(",\t");
    output.append(doubleToString(this->getCapacitance()));
    output.append(",\t");
    output.append(this->capacitance_orig);
    return output;
}

double Capacitor::parseCapacitance(string val){
    string value = "";
    char unit = char(0);
    
    for (char c : val){
        int int_val = int(c);
        if (c == 'n' || c=='p' || c=='u'){
            unit = c;
        }else if (int_val >= 48 && int_val <= 57){
            //numeric character
            value.append(string(1, c));
        }//else skip
        
        
    }
    
    int pow = 0;
    
    switch(unit){
        case('u'):
            pow = -6;
            break;
        case('n'):
            pow = -9;
            break;
        case('p'):
            pow = -12;
            break;
        default:
            break;
    }
    
    double multiplier = power(10.0f, pow);
    
    return stringToDouble(value) * multiplier;
}

IC::IC(vector<string> row) : StockItem(row){
    try{
        
        this->description = row.at(4);
        
    }catch(std::out_of_range e){
        if (row.size() >= 1){
            cout << "Could not parse line:" << row.front() << endl;
        }else{
            cout << "Could not parse line with no data." << endl;
        }
    }
}

string IC::getDescription(){
    return this->description;
}

string IC::toString(){
    string output = StockItem::toString();
    output.append(",\t");
    output.append(this->getDescription());
    return output;
}

