#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"

using namespace std;

int main()
{
    MerkelMain app{};
    app.init();
    //CSVReader::readCSV("20200317.csv");

    return 0;
}