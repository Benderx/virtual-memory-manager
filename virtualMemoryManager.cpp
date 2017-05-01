// Andrew Duerig and Gabe Stanton
// virtualMemoryManager.cpp



#include "virtualMemoryManagerInterface.hpp"
#include <vector>
#include <queue>
#include <math.h>

class virtualMemoryManager : public virtualMemoryManagerInterface
{
	public:
		//We use the 2^variable formulas as defined in the project
		virtualMemoryManager(ReplacementPolicy p, unsigned int pS, unsigned int nF, unsigned int vA) : virtualMemoryManagerInterface(p, pow(2, pS), nF, pow(2, vA)) {}

		unsigned long long memoryAccess(unsigned long long address)
		{
			unsigned long long page_num = address / N;
			int page_index = -1;  //Assuming number of frames is less than 2^32//
			bool found = false;


			//Searching if the required page is in the frame_holder
			for(int i = 0; i < frame_holder.size() && found == false; i++)
			{
				if(frame_holder[i] == page_num)
				{
					found = true;
					page_index = i;
				}
			}

			//Only if the page was found in the holder AND we are LRU policy, we must bubble the page used to the front.
			if(found == true)
			{
				if(policy == ReplacementPolicy::LRU)
				{
					bool found_lru = false;
					int tracker;

					//finding where the page number is in the lru_order
					for(int j = 0; j < lru_order.size() && found_lru == false; j++)
					{
						if(lru_order[j] == page_index)
						{
							tracker = j;
							found_lru = true;
						}
					}
					//Bubbling to the used page to the front of lru order
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
				//We must swap in the page into the frame holder, depends on policy
				switch(policy)
				{
					case ReplacementPolicy::FIFO:
						{
							//If the frame_holder isn't full yet, just swap the page in without removing anything
							if(frame_holder.size() < numFrames)
							{
								frame_holder.push_back(page_num);
								fifo_order.push(frame_holder.size() - 1);
								page_index = frame_holder.size() - 1;
							}
							//If the frame_holder is full then we must pull a page out and swap the one required in
							else
							{
								page_index = fifo_order.front();
								swap(fifo_order.front(), page_num);
								fifo_order.push(fifo_order.front());				
								fifo_order.pop();
							}
							break;
						}
					case ReplacementPolicy::LRU:
						{
							//If the frame_holder isn't full yet, just swap the page in without removing anything
							if(frame_holder.size() < numFrames)
							{
								frame_holder.push_back(page_num);
								lru_order.insert(lru_order.begin(), frame_holder.size() - 1);
								page_index = frame_holder.size() - 1;
							}
							//If the frame_holder is full then we must pull a page out and swap the one required in
							else
							{
								page_index = lru_order[lru_order.size()-1];
								swap(lru_order[lru_order.size()-1], page_num);
								lru_order.insert(lru_order.begin(), lru_order[lru_order.size()-1]);
								lru_order.pop_back();
							}
							break;
						}
				}
			}
			//The final virtual to physical mapping formula
			return (page_index * N) + (address % N);
		}

		void swap(unsigned int frameNumber, unsigned int pageNumber) 
		{
			frame_holder[frameNumber] = pageNumber; //simple swap for the frame_holder
			numSwaps++;
		}

	protected:
		std::vector<unsigned long long> frame_holder;
		std::queue<int> fifo_order;   //We use a simple queue for the fifo ordering
		std::vector<int> lru_order;   //We use a vector to hold the least recently used frame index at the last position, and the most used at the begining.
};
