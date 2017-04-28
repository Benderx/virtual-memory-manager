// testbench.cpp
// By Andrew Duerig and Gabe Stanton
//
// how to compile using mingw:
// g++ .\Project1.cpp myscheduler.cpp -o run.exe -std=c++11
//
//////////////////////////////////////////////////////////////////////////////////////////////
//
//ASSUMPTIONS
// assert(virtualAddressSpaceSize > N);
// assert(pow(2, virtualAddressSpaceSize) > numFrames * pow(2,N));

#include "virtualMemoryManager.cpp"
#include "stdafx.h"
#include <random>

int main(int argc, char* argv[])
{
	cout << "\n--Andrew Duerig and Gabe Stanton's Testbench--\n\n";



	virtualMemoryManager vmmi = virtualMemoryManager(POLICY, BITS_PER_BLOCK, NUMBER_OF_PAGES, VIRT_ADDRESS_SPACE);

	cout << "Alexandar Devic - Cauchy Distribution Memory Generator" << endl;
	cout << "Input the number of memory requests you want to process[0, ]: ";
	unsigned long int operations = 0;
	cin >> operations;
	cout << "Input the average place in virtual memory where you want requests to occur[0, ]: ";
	unsigned long int averageVirtLoc = 0;
	cin >> averageVirtLoc;
	cout << "Input the standard deviation for the distribution[0, ]: ";
	unsigned long int stDeviation = 0;
	cin >> stDeviation;

	cout << "Press [RETURN] to begin processing";
	cin.get(); cin.get();

	cout << "Creating random engine generator...\n";
	std::default_random_engine generator;

	cout << "Generating Cauchy Distriburion...\n";
	std::cauchy_distribution<double> distribution(averageVirtLoc, stDeviation);

	cout << "Starting to produce random memory requests...\n\n";
	unsigned long int currentProcess = 0;
	unsigned long int currSwaps = vmmi.numberPageSwaps();
	for (int i = 0; i < operations; i++) {
		unsigned long int number = distribution(generator);
		while (number < 0 && number >= pow(2, VIRT_ADDRESS_SPACE))
			number = distribution(generator);
		unsigned long int whatsReturned = vmmi.memoryAccess(number);

		if (!PRINT_IN_HEX)
			cout << "Virtual [" << number << "] is in Physical[" << whatsReturned << "] " << (currSwaps != vmmi.numberPageSwaps() ? "SWAPPED" : "") << endl;
		else
			cout << "Virtual [" << std::hex << number << "] is in Physical[" << std::hex << whatsReturned << "] " << (currSwaps != vmmi.numberPageSwaps() ? "SWAPPED" : "") << endl;

		currSwaps = vmmi.numberPageSwaps();
	}

	cout << "Finished the test! Press [ENTER] to close... ";
	cin.get();



	cout << "Testing completed, exiting";
	return 0;
}
