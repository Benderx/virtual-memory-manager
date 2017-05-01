// Andrew Duerig and Gabe Stanton
// testbench.cpp
//
// how to compile using linux/mingw:
// g++ testbench.cpp -o run -std=c++11
//
//////////////////////////////////////////////////////////////////////////////////////////////
//
//ASSUMPTIONS
// assert(virtualAddressSpaceSize > N);
// assert(pow(2, virtualAddressSpaceSize) > numFrames * pow(2, N));

#include "virtualMemoryManager.cpp"
#include <random>

int main(int argc, char* argv[])
{
	cout << "\n--Andrew Duerig and Gabe Stanton's Testbench--\n\n";

	unsigned int virtualAddressSize = -1, numFrames = -1, N = -1, policy = -1;
	unsigned long long v_addr;

	cout << "Policy Number (LRU = 1, FIFO=0):  ";
	cin >> policy;
	cout << policy << endl;
	cout << "Enter N: ";
	cin >> N;
	cout << N << endl << "Number of Frames: ";
	cin >> numFrames;
	cout << numFrames << endl << "Virtual Address Size: ";
	cin >> virtualAddressSize;
	cout << virtualAddressSize << endl << endl;

	virtualMemoryManager manager = virtualMemoryManager(policy ? LRU : FIFO, N, numFrames, virtualAddressSize);
	
	cout << "Give an address: ";
	while (cin >> v_addr) 
	{
		cout << std::endl;
		cout << "Address: " << v_addr << std::endl;
		cout << "Physical memory: " << manager.memoryAccess(v_addr) << std::endl;
		cout << "Total Swaps: " << manager.numberPageSwaps() << endl << std::endl;
		cout << "Give an address: ";
	}


	cout << "Testing completed, exiting" << std::endl;
	
	return 0;
}
