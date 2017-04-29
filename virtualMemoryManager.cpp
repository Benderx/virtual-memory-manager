#include "virtualMemoryManagerInterface.hpp"
#include <vector>
#include <queue>
// #include <math.h>

class virtualMemoryManager : virtualMemoryManagerInterface
{
	public:
		virtualMemoryManager(ReplacementPolicy p, unsigned int pS, unsigned int nF, unsigned int vA) : virtualMemoryManagerInterface(p, pS, nF, vA) {}

		unsigned long long memoryAccess(unsigned long long address)
		{
			unsigned long long page_num = address / N;
			int page_index = -1;  //Assuming number of frames is less than 2^32//

			bool found = false;
			for(int i = 0; i < frame_holder.size() && found == false; i++)
			{
				if(frame_holder[i] == page_num)
				{
					found = true;
					page_index = i;
				}
			}

			if(found == true)
			{
				if(policy == ReplacementPolicy::LRU)
				{
					bool found_lru = false;
					int tracker;

					for(int j = 0; j < lru_order.size() && found_lru == false; j++)
					{
						if(lru_order[j] == page_index)
						{
							tracker = j;
							found_lru = true;
						}
					}
					while(tracker > 0)
					{
						int temp = lru_order[tracker];
						lru_order[tracker] = lru_order[tracker - 1];
						lru_order[tracker - 1] = temp;
						tracker--; 
					}
				}
			}
			else
			{
				switch(policy)
				{
					case ReplacementPolicy::FIFO:
						{
							if(frame_holder.size() < numFrames)
							{
								frame_holder.push_back(page_num);
								fifo_order.push(frame_holder.size() - 1);
							}
							else
							{
								swap(fifo_order.front(), page_num);
								fifo_order.push(fifo_order.front());				
								fifo_order.pop();
							}
							break;
						}
					case ReplacementPolicy::LRU:
						{
							if(frame_holder.size() < numFrames)
							{
								frame_holder.push_back(page_num);
								lru_order.insert(lru_order.begin(), frame_holder.size());
							}
							else
							{
								swap(lru_order[lru_order.size()-1], page_num);
								lru_order.insert(lru_order.begin(), lru_order[lru_order.size()-1]);
								lru_order.pop_back();
							}
							break;
						}
					default:
						{
							cout << "what happened?" << endl;
							break;
						}
				}
			}
			return (page_index * N) + (address % N);
		}

		void swap(unsigned int frameNumber, unsigned int pageNumber) 
		{
			frame_holder[frameNumber] = pageNumber;
			numSwaps++;
		}

	protected:
		std::vector<unsigned long long> frame_holder;
		std::queue<int> fifo_order;
		std::vector<int> lru_order;
};




// ReplacementPolicy policy;

// 	unsigned int N; /// N = Page Address bits size, 2^ N = The physical frame/virtual page size to manage (bytes)
// 	unsigned int numFrames; /// total number of physical frames. Phy mem size = numFrames * 2^N
// 	unsigned int virtualAddressSpaceSize; ///  2^virtualAddressSpaceSize = total virtual address space (bytes)

// 	unsigned long long numSwaps = 0; ///total number of page swaps performed