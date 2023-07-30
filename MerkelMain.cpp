#include <iostream>
#include <vector>
#include <limits>
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"

using namespace std;

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = OrderBook.getEarliestTime();
    wallet.insertCurrency("BTC",10);
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print help
    cout<< "1: Print help "<<endl;

    // 2 print exchange stats
    cout<< "2: Print exchange stats "<<endl;

    // 3 make an offer
    cout<< "3: Make an offer "<<endl;

    // 4 make a bid
    cout<< "4: Make a bid "<<endl;

    // 5 print wallet
    cout<< "5: Print wallet "<<endl;

    // 6 continue
    cout<< "6: Continue"<<endl;

    cout<< "================"<<endl;
    cout<<"Current time is: "<<currentTime<<endl;
}

int MerkelMain::getUserOption()
{
    int userOption=0;
    string line;
    std::cout<<"Type in 1-6"<<endl;
    getline(cin, line);
    try{
        userOption = stoi(line);
    }catch(const exception& e)
    {
        
    }
    
    std::cout<<"You chose: "<<userOption<<endl;
    return userOption;
}

void MerkelMain::printHelp()
{
    cout<<"Help - Your aim is to make money."<<endl;
}

void MerkelMain::printMarketStats()
{
    for (string const& p : OrderBook.getKnownProducts())
    {
        cout<< "Product: " << p << endl;
        vector<OrderBookEntry> entries = OrderBook.getOrders(OrderBookType::ask, p, currentTime);
        cout<<"Asks seen: "<<entries.size()<<endl;
        cout<<"Max ask: "<<OrderBook::getHighPrice(entries)<<endl;
        cout<<"Low ask: "<<OrderBook::getLowPrice(entries)<<endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout<<"Make an ask - Enter the amount: product,price,amount, eg: ETH/BTC, 200, 0.5"<<endl;  
    string input;
    //cin.ignore(numeric_limits<streamsize>::max(),'\n');   //this line caused input to not read anything
    getline(cin, input);
    vector<string> tokens = CSVReader::tokenise(input,',');

    if (tokens.size()!=3)
    {
        std::cout<<"Bad Input"<<endl;
    }
    else{
        try{
        OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                    tokens[2],
                                                    currentTime,
                                                    tokens[0],
                                                    OrderBookType::ask);
        obe.username="simuser";
        if (wallet.canFullfillOrder(obe))
        {
            cout<<"Wallet looks good"<<endl;
            OrderBook.insertOrder(obe);
        }else{
            cout<<"Wallet has insufficient funds"<<endl;
        }
        
        }catch(const exception& e)
        {
            std::cout<<"MerkelMain::enterAsk Bad Input "<<endl;
        }
    
    }

    std::cout<<"You typed: "<<input<<endl; 
}
    
void MerkelMain::enterBid()
{
    std::cout<<"Make a bid - Enter the amount: product,price,amount, eg: ETH/BTC, 200, 0.5"<<endl;  
    string input;
    //cin.ignore(numeric_limits<streamsize>::max(),'\n');   //this line caused input to not read anything
    getline(cin, input);
    vector<string> tokens = CSVReader::tokenise(input,',');

    if (tokens.size()!=3)
    {
        std::cout<<"Bad Input"<<endl;
    }
    else{
        try{
        OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                    tokens[2],
                                                    currentTime,
                                                    tokens[0],
                                                    OrderBookType::bid);
        obe.username="simuser";
        if (wallet.canFullfillOrder(obe))
        {
            cout<<"Wallet looks good"<<endl;
            OrderBook.insertOrder(obe);
        }else{
            cout<<"Wallet has insufficient funds"<<endl;
        }
        
        }catch(const exception& e)
        {
            std::cout<<"MerkelMain::enterBid Bad Input "<<endl;
        }
    
    }

    std::cout<<"You typed: "<<input<<endl; 
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeFrame()
{
    cout<<"Going to next time frame"<<endl;
    vector<OrderBookEntry> sales = OrderBook.matchAsksToBids("ETH/BTC",currentTime);
    cout<<"Sales: "<<sales.size()<<endl;
    for (OrderBookEntry& sale:sales)
    {
        cout<<"Sale price: "<<sale.price<<" Sale amount: "<<sale.amount<<endl;
        if (sale.username=="simuser")
        {
            wallet.processSale(sale);
        }
    }
    currentTime = OrderBook.getNextTime(currentTime);
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption==1)
    {
        printHelp();
    }
    else if (userOption==2)
    {
        printMarketStats();
    }
    else if (userOption==3)
    {
        enterAsk();
    }
    else if (userOption==4)
    {
        enterBid();
    }
    else if (userOption==5)
    {
        printWallet();
    }
    else if (userOption==6)
    {
        gotoNextTimeFrame();
    }
}