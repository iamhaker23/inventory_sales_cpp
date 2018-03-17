#include <string>
#include <vector>
#include <iostream>


using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;
using std::fixed;
using std::stof;
using std::stoi;

#ifndef STOCKITEM_H
    #define	STOCKITEM_H

    using std::string;
    
    class StockItem{
        
        private:
            string type;
            int unit_price;
            int stock;
            string code;
            bool valid;
            
        protected:
        
            //Refactor into static lib
            static int stringToInt(string val);
            static float stringToFloat(string val);
            static double stringToDouble(string val);
            //Refactor into static lib
            static string intToString(int val);
            static string floatToString(float val);
            static string doubleToString(double val);
            double power(float base, int index);
            
        public:
            static bool compare(StockItem* i, StockItem* j);
            StockItem(vector<string> row);
            StockItem();
            //StockItem(StockItem item);
            string getType();
            int getPrice();
            int getStockLevel();
            string getCode();
            virtual string toString();
            static StockItem* parse(vector<string> row);
            

    };
    
    
    class Transistor : public StockItem{

        private:
            string configuration;
            
        public:
            Transistor(vector<string> row);
            //Transistor(StockItem item);
            string getConfiguration();
            
            //override
            virtual string toString();
        
    };
    
    class Resistor : public StockItem{

        private:
            float resistance;
            string resistance_orig;
            
        public:
            Resistor(vector<string> row);
            //Resistor(StockItem item);
            int getResistance();
            //override
            virtual string toString();
            float parseResistance(string val);
        
    };
    
    class Capacitor : public StockItem{

        private:
            double capacitance;
            string capacitance_orig;
            
        public:
            Capacitor(vector<string> row);
            //Capacitor(StockItem item);
            double getCapacitance();
            //override
            virtual string toString();
            double parseCapacitance(string val);
        
    };
    
    class IC : public StockItem{

        private:
            string description;
            
        public:
            IC(vector<string> row);
            //IC(StockItem item);
            string getDescription();
            //override
            virtual string toString();
    };

#endif	/* STOCKITEM_H */

