# LoopStatistics

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