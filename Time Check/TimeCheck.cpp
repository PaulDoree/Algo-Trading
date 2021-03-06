//This allows you to stop making trades after a given time and closes any open trades
//CHANGE extension from .cpp to .mt4

extern bool UseTimeLimit = true;
extern double LotSize = 1.0;

void CloseTime(int x);

void start()
{
    bool AllowTrade = false;
    datetime TimeOfTrade = TimeCurrent();
    int CurrentHour;
    //set these to whatever time you want - 0 <= hour < 24:00
    int StartTradeTime = 0;
    int EndTradeTime = 16;
    
    if (UseTimeLimit == true){
        CurrentHour = TimeHour(TimeOfTrade);
        if (CurrentHour >= StartTradeTime && CurrentHour <= EndTradeTime){
            AllowTrade = true;
        }
    }
    
    if(AllowTrade == true){
        //here you can insert all necessary algorithmic functions etc. as the bool AllowTrade
        //will ensure trades only take place in the given period.
    }
    
    void CloseTime(EndTradeTime);
}

//Allows you to close all trades outside of given range in order to save you from paying overnight fees
void CloseTime(int EndTradeTime)
{
    if(TimeCurrent() > EndTradeTime){
        if(OrderSelect(ticket, SELECT_BY_TICKET) == true){
            if((OrderType() == OP_BUY)){
                //OrderClose function is (int ticket, double LotSize, Ask/Bid, int slippage, color)
                //refer to MT4 documentation
                OrderClose(ticket,LotSize,Bid,3,Red);
            }
            else if (OrderType() == OP_SELL){
                OrderClose(ticket,LotSize,Ask,3,Green);
            }
        }
    }
}
