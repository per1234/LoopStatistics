#include <LoopStatistics.h>

LoopStatistics LoopStats; //Instantiate a LoopStatistics class

void setup() {
	Serial.begin(115200);
}

void loop() {
	LoopStats.tick(true); //calculate statistics and print them out every scan
}