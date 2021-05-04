#ifndef MYTIME_H
#define MYTIME_H
/**
 * MyTime.h
 * CS 3307 - RaspberryOke
 *
 * The processing time for each lyrics is specified as [min:sec.msec] in the lrc files.
 * The class Time is used to stored processing time of each lyrics.
 * Its value will be converted into an integer as "min * 60 + sec" for better use of GUI code (msec will be ignored)
 * and stored into a vector in Lyrics.cpp
 *
 * Created by Team 30
 * Date: 29th Oct, 2019
 */

class MyTime
{
public:
    int min = 0;		// the value of minutes, default value is the origin 0
    int sec = 0;		// the value of seconds, default value is the origin 0

    MyTime() {}

    MyTime(int _min, int _sec)
    {
        min = _min;	// set the minutes value with the given integer
        sec = _sec;	// set the seconds value with the given integer
    }

    /**
     * 		Function from_Time_to_int
     * convert Time value into an integer value by basic calculation
     * parameter 	Time lrc_time		stores value of minutes and seconds in two variables
     * returns				(x seconds)
     */
    int from_Time_to_int(MyTime lrc_time)
    {
        return sec + min * 60;
    }


};

#endif // MYTIME_H
