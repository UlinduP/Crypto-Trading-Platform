#include "CSVReader.h"
#include <iostream>
#include <fstream>

using namespace std;

CSVReader::CSVReader()
{

}


/**This reads a csvFile and returns the entries as a vector of order book entries*/
vector<OrderBookEntry> CSVReader::readCSV(string csvFileName)
{
    vector<OrderBookEntry> entries;
    ifstream csvFile{csvFileName};
    string line;
    if (csvFile.is_open())
    {
        while(getline(csvFile, line))
        {
            try{
                OrderBookEntry obe = stringsToOBE(tokenise(line,','));
                entries.push_back(obe);
            }catch(const exception& e){
                cout<<"CSVReader::readCSV bad data"<<endl;
            }
        }
        cout<<"CSVReader::readCSV read: "<<entries.size()<<" entries."<<endl;
        csvFile.close();
    }
    return entries;
}

/**This tokenises the csv lines based on a separator*/
vector<string> CSVReader::tokenise(string csvLine, char separator)
{
    vector<string> tokens;
    signed int start,end;
    string token;
    start = csvLine.find_first_not_of(separator, 0);
    
    do{
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end) break;
        if (end != string::npos) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1;
    }while(end != string::npos);

    return tokens;
}

/**converts string tokens to a suitable order book entry*/
OrderBookEntry CSVReader::stringsToOBE(vector<string> tokens)
{
    double price, amount;

    if (tokens.size() != 5)
    {
        cout<<"Bad Line"<<endl;
        throw exception{};
    }

    try{
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    }catch(exception& e){
        cout<<"Bad Float"<<endl;
        throw;
    }
    OrderBookEntry obe{price,amount,tokens[0],tokens[1],OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}


OrderBookEntry CSVReader::stringsToOBE(std::string priceString, 
                                            std::string amountString, 
                                            std::string timestamp,
                                            std::string product, 
                                            OrderBookType OrderType)

{
    double price, amount;
    try{
        price = stod(priceString);
        amount = stod(amountString);
    }catch(exception& e){
        cout<<"CSVReader::stringsToOBE Bad Float"<<priceString<<endl;
        cout<<"CSVReader::stringsToOBE Bad Float"<<amountString<<endl;
        throw;
    }
    OrderBookEntry obe{price,amount,timestamp,product,OrderType};
    return obe;
}