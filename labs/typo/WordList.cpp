#include "WordList.h"
#include "Point.h"
#include <cctype>
#include <cmath>

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
	std::vector<std::string> rightLength;
	size_t wordLength = points.size();
	for(size_t i = 0; i < mWords.size(); i++){
		if(mWords[i].length() == wordLength){
			rightLength.push_back(mWords[i]);
		}
	}

	std::vector<float> scores;
	
	for(size_t i = 0; i < rightLength.size(); i++){
		float score = 0;
		for(size_t j = 0; j < wordLength; j++){
			float x = points[j].x;
			float y = points[j].y;
			float ux = QWERTY[(rightLength[i])[j] - 'a'].x;
			float uy = QWERTY[(rightLength[i])[j] - 'a'].y;
			float xDiff = pow((x-ux), 2);
			float yDiff = pow((y-uy), 2);
			float distance = pow((xDiff + yDiff), .5);
			float s = (1 / (10*pow(distance, 2) + 1));
			score += s;
		}

		score /= wordLength;
		scores.push_back(score);
	}
	
	Heap heap(maxcount);
	size_t count = 0;
	std::vector<std::string> usedWords;

	while(count < maxcount){
		float max = 0.00;
		std::string maxWord;
		for(size_t i = 0; i < rightLength.size(); i++){
			if(scores[i] > max){
				bool notUsed = 1;
				for(size_t j = 0; j < usedWords.size(); j++){
					if(usedWords[j] == rightLength[i]){
						notUsed = 0;
						break;
					}
				}
				if(notUsed){
					max = scores[i];	
					maxWord = rightLength[i];	
				}
			}
		}
		if(max > cutoff){
			heap.push(maxWord, max);
			count++;
		}
		else{
			break;
		}
		usedWords.push_back(maxWord);
	}

	return heap;
}
