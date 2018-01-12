#include <cmath>
#include <iostream>
using namespace std;
//Notations:TNC=Total Number of Coupons,cr=coupon rate,
//storing Bond Value as BV
double PVB(double FV,double c,double r, double d, double N)
{
    double BV=0.;
    double TNC=N+d;
    double cr=c/FV;
    for(double i=d;i<=TNC;i++)
    {
        BV=BV+c*pow((1+r),-i);
    }

    BV=BV+ FV*pow((1+r),-TNC);
    return BV;
}
//Algorithm for the Bisection Method of Calculating YTM
double BisecYTM(double FV, double cr, double PV, double N, int d, double H, double L){

    const int MaxIter=50000;
    double Tol=0.0000001;
    double midP=0.0, midCdif;

    double lowCdif=PV-PVB(FV, cr, H, d, N);
    double highCdif=PV- PVB(FV, cr, L, d, N);

    if (lowCdif*highCdif>0)
        return -1;
    else
        for (int i=0;i<=MaxIter;i++){
            midP=(H+L)/2.0;
            midCdif=PV-PVB(FV,cr,midP,d,N);
            if(abs(midCdif)<Tol) goto LastLine;
            else {
                if (midCdif>0) L=midP;
                else H= midP;
            }

        }
    LastLine:
    return midP;
}

int main()
{
    double i,c, FV, PV, N,d;
    cout << "Please provide coupon value of the bond as c: "; cin >> c;
    cout << "Please provide year fraction until next coupon payment as d: "; cin >>d;
    cout << "Please provide face value of the bond as FV: "; cin >>  FV;
    cout << "Please provide today's price of the bond as PV: "; cin >>  PV;
    cout << "Please provide number of full years until maturity as N: "; cin >>  N;
    double H= 0.000001;
    double L=10;
    double YTM = BisecYTM(FV, c, PV, N, d, H, L);
    cout << "The Yield To Maturity of the bond =" <<YTM<<""<<endl;
}