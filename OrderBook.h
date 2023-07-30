#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
    /** Construct, reading a csv data file*/
        OrderBook(std::string filename);
    /** return vector of all known products in the database*/
        std::vector<std::string> getKnownProducts();
    /** return vector of orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp); 
    /** return the earlieset time as a string. Assume the orderbook is sorted*/
        std::string getEarliestTime();
    /** returns the next time after the sent time in the orderbook*/
        std::string getNextTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order);

        vector<OrderBookEntry> matchAsksToBids(string product, string timestamp);

        static double getHighPrice(vector<OrderBookEntry>& orders);
        static double getLowPrice(vector<OrderBookEntry>& orders);
   
    private:
        std::vector<OrderBookEntry> orders;
};