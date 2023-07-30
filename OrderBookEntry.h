#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class OrderBookType{bid, ask, bidsale, asksale, unkown};

class OrderBookEntry
{
    public:  //means we can access these outside the class

        OrderBookEntry(        //constructor
            double _price,
            double _amount,
            string _timestamp,
            string _product,
            OrderBookType _orderType,
            string _username="dataset");
        
        static OrderBookType stringToOrderBookType(string s);

        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);

        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);

        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);

        double price;
        double amount;
        string timestamp;
        string product;
        OrderBookType orderType;
        string username;

};