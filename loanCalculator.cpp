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
    // round(date2+0.25);
    return round(date2 - date1);
}

int main()
{
    /*
    double LoanA = 2750, LoanB = 3250, LoanC = 3250, Loan7 = 3750, Loan8 = 3447;
    double LoanNum[] = {LoanA, LoanA, LoanB, LoanB, LoanC, LoanC, Loan7, Loan8 };
    double lrA = 3.760 / 100;
    double lrB = 4.450 / 100;
    double lrC = 5.050 / 100;
    double lrD = 4.530 / 100;
    double rateNum[] = {lrA, lrA, lrB, lrB, lrC, lrC, lrD, lrD };
    double days1 = 1277; //08/28/2016
    double days2 = 1137; //01/15/2017
    double days3 = 913; //08/27/2017
    double days4 = 773; //01/14/2018
    double days5 = 549; //08/26/2018
    double days6 = 409; //01/13/2019
    double days7 = 178; //09/01/2019
    double days8 = 38;//01/19/2020
    double days[] = {days1, days2, days3, days4, days5, days6, days7, days8 };
    vector<double> LoanTotal;
    for(int i = 0; i < 8; i++)
    {
        LoanTotal.push_back(Loan(LoanNum[i], rateNum[i], days[i]));
        // cout << "Loan " << i+1 << ": " << LoanTotal[i] << endl;
    }

    cout << "Loan A : " << LoanTotal[0] + LoanTotal[1] << endl;
    cout << "Loan B : " << LoanTotal[2] + LoanTotal[3] << endl;
    cout << "Loan C : " << LoanTotal[4] + LoanTotal[5] << endl;
    cout << "Loan D : " << LoanTotal[6] + LoanTotal[7] << endl;
    */
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

    cout <<  "Enter corresponding intrest rates for each loan separated by spaces ";
    while(i < numLoans)
    {
        cin >> input;
        if(i < numLoans)
            rateNum[i++] = input;
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
            // days[i++] = dDay.month + dDay.day + dDay.year;
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
    
    for (int i = 0; i < numLoans; i++)
    {
        cout << balanceLoan[i] << endl;
    }

    /*
    double loanStart, intrest;
    string distributionDate, distDate;
    string outstandingDate, outDate;
    cout << "What is your starting loan balance? ";
    cin >> loanStart;
    cout << "What is your intrest rate for that loan? Enter as a percentage. ";
    cin >> intrest;

    //To get the decimal of the percentage
    intrest = intrest / 100;

    cout <<  "Insert the date of loan distributrion as MM/DD/YYY "; 
    cin >> distributionDate;
    Date dDay;
    istringstream idd(distributionDate);
    while(getline(idd, distDate))
    {
        istringstream dd(distDate);

        dd >> dDay.month; 
        dd.ignore(); //ignores the / after the month
        dd >> dDay.day;
        dd.ignore(); //ignores the / after the day
        dd >> dDay.year;

    }
    
    cout << "Insert the date you wish to see the outstanding balance of your loan as MM/DD/YYY "; 
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
    }

    double totalDays;
    totalDays = getNumDays(dDay, oDay);

    cout << totalDays << endl;
    double outstandingBalance = Loan(loanStart, intrest, totalDays);

    cout << outstandingBalance;
    */
} 