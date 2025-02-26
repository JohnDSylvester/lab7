#include "WordList.h"
#include <iostream>
#include <cctype>

WordList::WordList(std::istream& stream){
	std::string line = "";
	bool check = 1;
	while(getline(stream, line)){
		for(size_t i = 0; i < line.length(); i++){
			if(!islower(line[i])){
				check = 0;
				break;	
			}
		}
		if(check){
			mWords.push_back(line);
		}
		check = 1;
	}
		mWords.shrink_to_fit();
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const{
	Heap heap(3);
	return heap;
}
