/*
LoopStatistics
Created by Terry Myers Jan 2016 <TerryJMyers@gmail.com

v1.0

Calculate average, minimum, and maximum loop time in order to determine performance of code

Functions :
1. Call LoopStatistics.tick(bool print==false) once and only once each loop.
  1. set print to 1 to automatically call printStatistics once a second
2. float LoopStatistics.Avg() to return the average loop time in ms calculated during the last 1 second interval
3. float LoopStatistics.Min() to return the fastest loop time in ms recorded during the last 1 second interval
4. float LoopStatistics.Max() to return the slowest loop time un ms recorded during the last 1 second interval
5. uint32_t LoopStatistics.LoopsPerSec() to number of loops that occured during the last 1 second interval
  1.  tip: only call this once a second or so, or pass in a 1 to tick().
6. void printStatistics() - prints all of the above to serial monitor

Note:
	This function technically interferes with calcluating what the loop time would be WITHOUT this function.  Especially when printing the statistics to the serial monitor which takes about 2.5ms
*/

#ifndef LoopStatistics_H
#define LoopStatistics_H



class LoopStatistics {

public:
	LoopStatistics(void) {
	}
	//Update loop time statistics.  This routine should run every loop of the program
		void tick(bool print=false) {
			//Calculate the current loop time
				uint32_t microsCurrent_ = micros(); // Record the current micros
				uint32_t LastLoopTime_ = microsCurrent_ - microsREM_; //calculate the last loop time
				microsREM_ = microsCurrent_; //Remember for next time

			//Calculate min/max loop time
				if (LastLoopTime_ > MaxLoopTimeuS_) { //Capture the maximum loop time
					MaxLoopTimeuS_ = LastLoopTime_;
				}
				if (LastLoopTime_ < MinLoopTimeuS_) { //Capture the fastest loop time
					MinLoopTimeuS_ = LastLoopTime_;
				}

			//Calculate average and reset statistics one a second
				LoopCounter_++; //count the nunmber of loops to determine averae
				uint32_t millisNOW_ = millis(); //get the current millis()
				uint16_t elapsed = millisNOW_ - millisREM_; //Get the elapsed time
				if (elapsed >= TimerPRE_) {
					AvgLoopTimeuS_ = (float)elapsed * 1000.0 / (float)LoopCounter_; //Calculate average
					LoopsPerSec_ = LoopCounter_ / elapsed * 1000; ////Calculate loops per second An integer is used instead of a more precise float for speed.
					if (print == true) {printStatistics();} //print statistics
					//Reset statistics
					LoopCounter_ = 0;
					MaxLoopTimeuS_ = 0;
					MinLoopTimeuS_ = 4294967295;
					millisREM_ = millisNOW_;
				}
		}
	//A return units of ms was choosen for readability
	float Avg() { return AvgLoopTimeuS_ / 1000.0; } //Return the Average loop time in ms
	float Min() { return (float)MinLoopTimeuS_ / 1000.0; } //Return the minimum loop time in ms
	float Max() { return (float)MaxLoopTimeuS_ / 1000.0; } //Return the maximum loop time in ms
	uint32_t LoopsPerSec() { return LoopsPerSec_; } //Return the number of loops per second
	void printStatistics() {
		//print full array of statistics to serial monitor.
		Serial.print(F("Avg="));
		Serial.print(Avg(), 4);
		Serial.print(F("ms "));

		Serial.print(F("Loops/sec:"));
		Serial.print(LoopsPerSec());

		Serial.print(F(" Min="));
		Serial.print(Min(), 4);
		Serial.print(F("ms "));

		Serial.print(F("Max="));
		Serial.print(Max(), 4);
		Serial.println(F("ms"));
	}

private:
	float AvgLoopTimeuS_; //loopTime in us averaged over one sec
	uint32_t LoopsPerSec_; //An integer is used instead of a more precise float for speed.
	uint32_t MinLoopTimeuS_ = 4294967295; //smallest recorded loopTime in us.  Set to the max number so that when a smaller number is recorded during the program its updated
	uint32_t MaxLoopTimeuS_; //largest loopTime in us
	uint32_t LoopCounter_; //used for average
	uint32_t microsREM_; //last micros() to remember
	uint32_t millisREM_; //Used for timer function
	uint16_t TimerPRE_ = 997; //Set the timer to calculate average.  A prime number is used to assist with overlapping other timers

};

#endif


