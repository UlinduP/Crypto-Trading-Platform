#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain
{
    public:
        MerkelMain();  //creating the object
        void init();
        /**call this to start sim*/
    
    private:
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();
        int getUserOption();
        void processUserOption(int userOption);

        string currentTime;
        
        OrderBook OrderBook{"20200317.csv"};
        
        Wallet wallet;
};