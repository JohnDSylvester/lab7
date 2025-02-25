#include <stdexcept>
#include <iostream>
#include "Heap.h"

void fixPop(Heap::Entry* data, size_t index, size_t count);
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
	fixPop(mData, 0, mCount);
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

void fixPop(Heap::Entry* data, size_t index, size_t count){
	size_t left = index* 2 + 1;
	size_t right = index* 2 + 2;
	size_t current = index;

	if(left < count && data[left].score < data[current].score){
                current = left;
        }

	if(right < count && data[right].score< data[current].score){
		current = right;
	}
	
	if(left < count && right < count && data[left].score == data[right].score){
                current = left;
        }

	if(current != index){
		Heap::Entry temp = data[index];
	        data[index] = data[current];
       		data[current] = temp;
 		fixPop(data,current,count);		
	}
}



bool topCheck(Heap::Entry* data, size_t &index){
        if(index != 0){
        if(data[index].score < data[(index-1)/2].score){
                Heap::Entry temp = data[index];
                data[index] = data[(index-1)/2];
                data[(index-1)/2] = temp;
                index = (index-1)/2;
                return 1;
        }
        }
        return 0;
}

bool bottomCheck(Heap::Entry* data, size_t &index, size_t count){
        if(index* 2 + 2 < count){
	bool leftLowest = data[index].score> data[(index * 2) + 1].score && data[(index*2)+2].score > data[(index * 2) + 1].score;
	bool rightLowest = data[index].score > data[(index * 2) + 2].score && data[(index*2)+1].score > data[(index * 2) + 2].score;
	if(leftLowest){
		Heap::Entry temp = data[index];
                data[index] = data[index * 2 +1];
                data[index * 2 + 1] = temp;
                index = index * 2 + 1;
		return 1;
	}
	else if(rightLowest){
		Heap::Entry temp = data[index];
                data[index] = data[index * 2 + 2];
                data[index * 2 + 2] = temp;
                index = index * 2 + 2;
		return 1;
	}
	else{
		Heap::Entry temp = data[index];
                data[index] = data[index * 2 +1];
                data[index * 2 + 1] = temp;
                index = index * 2 + 1;
                return 1;
	}
	}
	else if(index* 2 + 1 < count){
		if(data[index].score> data[(index * 2) + 1].score){
		Heap::Entry temp = data[index];
                data[index] = data[index * 2 +1];
                data[index * 2 + 1] = temp;
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
