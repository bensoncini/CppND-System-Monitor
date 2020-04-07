#include <string>

#include "format.h"

using std::string;
using std::to_string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int time) {
    int hours, minutes,seconds;
  	string s_hours, s_minutes, s_seconds;
    string hold;
    hours =time/3600;
    time = time%3600;
    minutes = time/60;
    time = time%60;
    seconds = time;
	if (seconds <10) {
    	s_seconds = "0" + to_string(seconds);
    }else{
      	s_seconds = to_string(seconds);
    };
  
  	if (minutes <10) {
    	s_minutes = "0" + to_string(minutes);
    }else{
      	s_minutes = to_string(minutes);
    };
  
    hold = to_string(hours) + ":" + s_minutes + ":" + s_seconds; 
    return hold; 
};