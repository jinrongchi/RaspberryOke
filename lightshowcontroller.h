//LightShowController.hpp

#ifndef LightShowController_h
#define LightShowController_h

#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

extern "C" {

#include <wiringPi.h>

}

#include <random>

#define LIGHT_ONE 17		// Light one is on pin 17
#define LIGHT_TWO 18		// Light two is on pin 18
#define LIGHT_THREE 22		// Light three is on pin 22

#define BLINK_DUR 10		// Blink duration

class LightShowController {

private:

    int tempo;              // The tempo of the song in beats per minute
    bool blinking;          // Indicates whether or not the lights should be blinking

public:

    /** Constructor
     * 
     * @param tempo
    */
    LightShowController(int t);

    /**
     * Destructor
     */
    ~LightShowController();

    /**
     * Blink a light
     * 
     * @param time to blink
    */
    void blinkLight(int time);

    /**
     * Start the blinking
    */
    void start();

    /**
     * Controls the periodic blinking
    */
    void blinkController();

    /**
     * Stop the blinking
    */
    void stop();



private:
    
    /**
     * @return a random number between 0 and 2 
     */
    int randomNumber();

};


#endif
