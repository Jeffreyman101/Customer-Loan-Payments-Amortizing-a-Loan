// Source.cpp
// CSCN 112
// Wait function created by Dr. Tuzi
// Error Checking Code by Dr. Poole
#include <string>
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

// Function Definitions
double principalInput();
int lifeOfLoanInput();
double interestRateInput();
void printInput(double&, int&, double&, double&);
void printColumns(double);
double monthlyPaymentCalculation(double&, double&, int&);
void Amortize(int, int, double, double, double);
void wait();

int main() 
{
	double principal{ 0.0 };
	int annualLoanLife{ 0 };
	int paymentNum{ 0 };
	double interestPerYear = 0.0;
	double ratePerPeriod{ 0.0 };
	double monthlyPayment{ 0.0 };

	// Input
	cout << "Principal: ";
	principal = principalInput();

	cout << endl;
	cout << "Life of Loan (5, 10, or 15 years): ";
	annualLoanLife = lifeOfLoanInput();

	cout << endl;
	cout << "Annual interest rate: ";
	interestPerYear = interestRateInput();
	cout << endl;

	// Calculations
	ratePerPeriod = interestPerYear / 12;
	paymentNum = annualLoanLife * 12;

	monthlyPayment = monthlyPaymentCalculation(principal, ratePerPeriod, paymentNum);
	
	// Output
	printInput(principal, annualLoanLife, interestPerYear, monthlyPayment);
	printColumns(principal);
	
	Amortize(1, paymentNum, ratePerPeriod, monthlyPayment, principal);

	wait();
	return 0;
}

// Principal Input
double principalInput()
{
	double input;
	cin >> input;
	while (cin.fail() || input < 0) {
		cout << "You must enter a positive number. Please try again. " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> input;
	}
	return input;
}

// Loan Life Input
int lifeOfLoanInput()
{
	int input;
	cin >> input;
	while (cin.fail() || !(input == 5 || input == 10 || input == 15)) {
		cout << "You must enter either 5, 10, or 15 years. Please try again. " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> input;
	}
	return input;
}

// Interest Rate Input
double interestRateInput()
{
	double input;
	cin >> input;
	while (cin.fail() || input < 0 || input > 100) {
		cout << "You must enter a positive number less than 100. Please try again. " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> input;
	}
	return input / 100;
}

// Printing Input
void printInput(double& principal, int& annualLoanLife, double& interestPerYear, double& monthlyPayment)
{
	system("cls"); // Clears screen
	cout << "Loan Application - Amortization Schedule" << endl << endl;

	cout << left << setw(40) << "Principal: " << setw(35) << right << fixed << setprecision(2) << principal << endl;
	cout << left << setw(40) << "Life of Loan (10, 15, or 30 years): " << setw(35) << right << annualLoanLife << endl;
	cout << left << setw(40) << "Annual interest rate: " << setw(34) << right << fixed << setprecision(2) << interestPerYear * 100 << '%' << endl;
	cout << left << setw(40) << "Monthly payment: " << setw(35) << right << fixed << setprecision(2) << monthlyPayment << endl;
	cout << endl << endl;
}

// Calculating Monthly Payment
double monthlyPaymentCalculation(double& principal, double& ratePerPeriod, int& paymentNum)
{
	double monthlyPayment = principal;
	monthlyPayment *= (ratePerPeriod * pow(1 + ratePerPeriod, paymentNum)) / (pow(1 + ratePerPeriod, paymentNum) - 1);
	
	return monthlyPayment;
}

// Printing Column names and initial balance
void printColumns(double principal) 
{
	cout << setw(15) << right << "Payment" << setw(15) << right << "Amount" << setw(15) << right << "Interest" << setw(15) << right << "Principal" << setw(15) << right << "Balance" << endl;
	cout << setw(75) << right << principal << endl;
}

// Recursive function to print amortization
void Amortize(int iterator, int timeToLive, double interestRate, double paymentPerMonth, double balance) 
{
	double interest = balance * interestRate;
	double principal = paymentPerMonth - interest;
	balance -= principal;

	if (iterator == timeToLive - 1)
		balance += 0.0001;
	cout << fixed << setprecision(2) << setw(15) << right << iterator << setw(15) << right << paymentPerMonth << setw(15) << right << interest << setw(15) << right << principal << setw(15) << right << balance << endl;
	if (iterator < timeToLive) 
		Amortize(++iterator, timeToLive, interestRate, paymentPerMonth, balance);
}

// Wait function by Dr. Tuzi
void wait()
{
	//The following if-statement checks to see how many characters are in cin's buffer
	//If the buffer has characters in it, the clear and ignore methods get rid of them.
	if (cin.rdbuf()->in_avail() > 0) //If the buffer is empty skip clear and ignore
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Clear the input buffer 
	}
	cout << "Press the Enter key to continue ... ";
	cin.get();
}