#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctgmath>

using namespace std;

struct Date {
    double year; 
    double month;
    double day;
 };

 const double daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

template <typename T> T LoanBalance (T rate, T curPay)
{
    T dailyBalance = curPay + rate;

    return dailyBalance;
}

template <typename T> T IntrestCalculator (T rate, T curPay)
{
    T dailyIntrest = (curPay * rate) / 365.25;
    return dailyIntrest;
}

template <typename T> T Loan (T loanNum, T rate, T numDays)
{
    T dailyRate = IntrestCalculator(rate, loanNum);
    T total = LoanBalance(dailyRate, loanNum);
    T accruedIntrest;

    accruedIntrest = dailyRate * numDays;
    return loanNum + accruedIntrest;
}

template <typename S> double getNumDays(S dMonth, S dDay, S dYear, S oMonth, S oDay, S oYear)
{
    double date1 = (dYear*365.25 + dDay);
    for(int i = 0; i < dMonth - 1; i++)
    {
        date1 += daysInMonth[i];
    }

    //day -1 is because it has not reached the end of day so don't include current day
    double date2 = (oYear*365.25 + (oDay - 1));
    for(int i = 0; i < oMonth - 1; i++)
    {
        date2 += daysInMonth[i];
    }
    return round(date2 - date1);
}

int main()
{
    
    int numLoans; 
    cout << "How many loans do you want to calculate? ";
    cin >> numLoans;
    double loanNum[numLoans];
    double rateNum[numLoans];
    double days[numLoans];
    vector<Date> ddList;

    cout << "Enter the loan starting balances separated by a space ";
    double input;
    int i = 0;
    while(i < numLoans)
    {
        cin >> input;
        if(i < numLoans)
            loanNum[i++] = input;
        else
            break;
    }
    i = 0;

    cout <<  "Enter corresponding intrest rates for each loan as percentages, separated by spaces ";
    while(i < numLoans)
    {
        cin >> input;
        if(i < numLoans)
            rateNum[i++] = input / 100;
        else
            break;
    }
    i = 0;

    cout << "What is the distribution date of the loans? Enter as MM/DD/YYYY separated by spaces ";
    while(i < numLoans)
    {
        string date;
        string ddate;
        cin >> date;
        Date dDay;
        istringstream idd(date);
        while(getline(idd, ddate))
        {
            istringstream dd(ddate);

            dd >> dDay.month; 
            dd.ignore(); //ignores the / after the month
            dd >> dDay.day;
            dd.ignore(); //ignores the / after the day
            dd >> dDay.year;

        
        if(i < numLoans)
            ddList.push_back(dDay);
        else
            break;
        }
        i++;
    }

    cout << "Enter the date you would like to know your outstanding balance for. Enter as MM/DD/YYY ";
    string outDate, outstandingDate;
    vector<Date> oList;
    cin >> outstandingDate;
    Date oDay;
    istringstream iod(outstandingDate);
    while(getline(iod, outDate))
    {
        istringstream od(outDate);

        od >> oDay.month; 
        od.ignore(); //ignores the / after the month
        od >> oDay.day;
        od.ignore(); //ignores the / after the day
        od >> oDay.year;

        oList.push_back(oDay);
    }
    
    int j = 0;
    double totalDays;
    vector<double> calcDays;
    for(int i = 0; i < ddList.size(); i++)
    {
        totalDays = getNumDays(ddList[i].month, ddList[i].day, ddList[i].year, oList[j].month, oList[j].day, oList[j].year);
        cout << totalDays << endl;
        calcDays.push_back(totalDays);
    }

    vector<double> balanceLoan;
    double numDays;
    for(int i = 0; i < numLoans; i++)
    {
        numDays = calcDays[i];
        double outstandingBalance = Loan(loanNum[i], rateNum[i], numDays);
        balanceLoan.push_back(outstandingBalance);
    }

    double accumulated;
    //How much intrest was accumulated for each loan
    for(int i = 0; i < numLoans; i++)
    {
        accumulated = balanceLoan[i] - loanNum[i];
        cout << "You accumulated $" << accumulated << " for your loan starting at $" << loanNum[i]
             << " with intrest rate " << rateNum[i] * 100 << "% to get a total of $" << balanceLoan[i]
             << " from " << ddList[i].month << '/' << ddList[i].day << '/' << ddList[i].year << " to "
             << oList[0].month << '/' << oList[0].day << '/' << oList[0].year << endl;
    }
    
    //Add all balances for overall
    double overall;
    for(int i = 0; i < balanceLoan.size(); i++)
    {
        overall += balanceLoan[i];
    }


    cout << "You have an overall loan total of $" << overall << endl;
    
} 