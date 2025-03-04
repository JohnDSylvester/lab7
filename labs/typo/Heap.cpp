#include <stdexcept>
#include "Heap.h"

bool topCheck(Heap::Entry* data, size_t &index);
void makeEntry(const std::string& value, float score, Heap::Entry* data, size_t index);
bool bottomCheck(Heap::Entry* data, size_t &index, size_t count);


Heap::Heap(size_t capacity){
	mData = new Entry[capacity];
	mCapacity = capacity;
	mCount = 0;
}

Heap::Heap(const Heap& other){
	mCapacity = other.mCapacity;
	mCount = other.mCount;
	mData = new Entry[mCapacity];
	for(size_t i = 0; i < mCount; i++){
		mData[i] = other.mData[i];	 
	}
}

Heap::Heap(Heap&& other){
	mCapacity = other.mCapacity;
        mCount = other.mCount;
	mData = other.mData;
	other.mData = nullptr;
}

Heap::~Heap(){
	delete [] mData;
}

size_t Heap::capacity() const{
	return mCapacity;
}

size_t Heap::count() const{
	return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const{
	if(index >= mCount){
		throw(std::out_of_range("Invalid Index"));
	}
	return mData[index];
	
}

Heap::Entry Heap::pop(){
	if(mCount == 0){
		throw(std::underflow_error("Popping empty heap"));
	}
	else if(mCount == 1){
		mCount--;
		return mData[0];
	}
	
	Heap::Entry save = top();
	mData[0] = mData[mCount-1];
	mCount--;
	size_t index = 0;
	while(bottomCheck(mData, index, mCount)){}
	return save;
}

void Heap::push(const std::string& value, float score){
	if(mCount == mCapacity){
		throw(std::overflow_error("Pushing to full"));
	}
	makeEntry(value, score, mData, mCount);
	if(mCount != 0){
		size_t currentIndex = mCount;
		while(topCheck(mData, currentIndex)){}
	}
	mCount++;
}

Heap::Entry Heap::pushpop(const std::string& value, float score){
        if(mCount == 0){
                throw(std::underflow_error("Popping empty heap"));
        }
	Heap::Entry save = top();
        makeEntry(value, score, mData, 0);
        size_t index = 0;
        while(bottomCheck(mData, index, mCount)){}
        return save;
}

const Heap::Entry& Heap::top() const{
	if(mCount == 0){
                throw(std::underflow_error("Popping empty heap"));
        }
	return mData[0];
}

bool topCheck(Heap::Entry* data, size_t &index){
        if(index != 0){
        if(data[index].score < data[(index-1)/2].score){
		std::swap(data[index],data[(index-1)/2]);
                index = (index-1)/2;
                return 1;
        }
        }
        return 0;
}

bool bottomCheck(Heap::Entry* data, size_t &index, size_t count){
        if(index* 2 + 2 < count){
		bool leftLowest = data[index].score > data[(index * 2) + 1].score && data[(index*2)+2].score >= data[(index * 2) + 1].score;
		bool rightLowest = data[index].score > data[(index * 2) + 2].score && data[(index*2)+1].score > data[(index * 2) + 2].score;
		if(leftLowest){
			std::swap(data[index],data[index*2 +1]);
                	index = index * 2 + 1;
			return 1;
		}
		else if(rightLowest){
			std::swap(data[index],data[index*2 +2]);
                	index = index * 2 + 2;
			return 1;
		}
	}
	else if(index* 2 + 1 < count){
		if(data[index].score> data[(index * 2) + 1].score){
			std::swap(data[index],data[index*2 +1]);
                	index = index * 2 + 1;
			return 1;
		}
	}
        return 0;
}

void makeEntry(const std::string& value, float score, Heap::Entry* data, size_t index){
	Heap::Entry created;
        created.value = value;
        created.score = score;
        data[index] = created;
}
