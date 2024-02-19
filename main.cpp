#include "Bank.h"

int main(int argc, char *argv[])
{
	string file_name = "";
	if (argc != 2)
	{
		cerr << "Invalid number of command line arguments." << endl;
	}
	else
	{
		file_name = string(argv[1]);
		Bank bank;
		bank.ReadTransactions(file_name);
		bank.ExecuteTransactions();
		bank.DisplayTransactions();
	}
}