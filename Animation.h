#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"


class Animation
{
private:
    int _internalFrame;
    int _startPixel;
    int _endPixel;
    int _currentPixel;
    byte _pace;
    int _localFrame;
    unsigned long _lastFrame = 0;
    int _animationType;
    int _animationIndex;
    bool _chaseForward;
    byte fadeLevel = 0;
    byte direction = 0;
    
public:
    struct CRGB
    {
        unsigned char b;
        unsigned char r;
        unsigned char g;
    };
    CRGB* leds;
    int numLeds;
    
    void clear()
    {
        Serial.print("clear ");
        Serial.println(numLeds);
        
        memset(leds, 0, numLeds * sizeof(struct CRGB));
    }
    
    //<<constructor>> setup the LED, make pin 13 an OUTPUT
    Animation(CRGB* lights, int numLeds)
    {
        _startPixel = 0;
        _endPixel = 0;
        _currentPixel = 0;
        _localFrame = 0;
        _animationType = 0;
        getIndex();
        leds = lights;
    }
    
    //<<destructor>>
    ~Animation()
    {
        /*nothing to destruct*/
    }
    
    //turn the LED on
    void setup()
    {
        // nothing
    }
    
    void getIndex()
    {
        static byte index = 0;
        _animationIndex = index++;
    }
    
    //turn the LED off
    void play()
    {
        bool increment;
        
    	Serial.print(_animationIndex);Serial.print(" ");Serial.print("play ");Serial.print(_animationType);
        Serial.print(" now ");Serial.print(millis());Serial.print(" last ");Serial.print(_lastFrame);
        Serial.print(" pace ");Serial.print(_pace);
        Serial.println();
        
        if (millis() > _lastFrame + _pace)
        {
            increment = true;
            Serial.println("Increment");
            _lastFrame = millis();
        }
        else
        {
            Serial.println("Don't Increment");
            increment = false;
        }
        
        switch(_animationType)
        {
            case (0):
                runSolid(increment);
                break;
            case (1):
                runChase(increment);
                break;
            case (2):
                runFade(increment);
                break;
        }
    }
    
    void chase(int start, int end, int color, byte pace)
    {
        //	Serial.print(getIndex(false));Serial.print(" ");Serial.println("start chase");
        
        if (start < end)
        {
            _startPixel = start;
            _currentPixel = start;
            _endPixel = end;
            _chaseForward = true;
        }
        else
        {
            _startPixel = end;
            _currentPixel = end;
            _endPixel = start;
            _chaseForward = false;
        }
        _animationType = 1;
        _pace = pace;
    }
    
    void runChase(bool increment)
    {
        //	Serial.print(getIndex(false));Serial.print(" ");Serial.println("runChase");
        
        if (increment)
        {
            if (_chaseForward)
            {
                if (_currentPixel < _endPixel)
                {
                    _currentPixel++;
                }
                else
                {
                    _currentPixel = _startPixel;
                }
            }
            else
            {
                if (_currentPixel > _startPixel)
                {
                    _currentPixel--;
                }
                else
                {
                    _currentPixel = _endPixel;
                }
            }
        }
        
        int iFadePos = _currentPixel;
        if (_chaseForward)
        {
            for(int brightness = 255;brightness>1;brightness/=4)
            {
                leds[iFadePos].r = brightness;
                leds[iFadePos].g = 0;
                leds[iFadePos].b = 0;
                if (--iFadePos < 1)
                    break;
            }
        }
        else
        {
            for(int brightness = 255;brightness>1;brightness/=4)
            {
                leds[iFadePos].r = brightness;
                leds[iFadePos].g = 0;
                leds[iFadePos].b = 0;
                if (++iFadePos > _endPixel)
                    break;
            }
        }

        leds[_currentPixel].r = 255;
        leds[_currentPixel].g = 0;
        leds[_currentPixel].b = 0;
        // nothing
    }
    
    
    void solid(int start, int end, int color, byte pace)
    {
        //	Serial.print(getIndex(false));Serial.print(" ");Serial.println("start solid");
        
        _startPixel = start;
        _currentPixel = start;
        _endPixel = end;
        _pace = pace;
        _animationType = 0;
    }
    
    void runSolid(bool increment)
    {
        //	Serial.print(getIndex(false));Serial.print(" ");Serial.println("runSolid");
        for(int i = _startPixel;i<=_endPixel;i++)
        {
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = 55;
        }
        
    }
    
    void fade(int start, int end, int color, byte pace)
    {
        //	Serial.print(getIndex(false));Serial.print(" ");Serial.println("start solid");
        
        _startPixel = start;
        _currentPixel = start;
        _endPixel = end;
        _animationType = 2;
        _pace = pace;
    }
    
    void runFade(bool increment)
    {
        //	Serial.print("fade ");Serial.print(fadeLevel);Serial.print(" dir ");Serial.print(direction);Serial.println();
        
        if (increment)
        {
            if (direction == 0)
            {
                fadeLevel++;
                if (fadeLevel == 128)
                    direction = 1;
            }
            else if (direction == 1)
            {
                fadeLevel--;
                if (fadeLevel == 0)
                    direction = 0;
            }
        }
        
        for(int i = _startPixel;i<=_endPixel;i++)
        {
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = fadeLevel;
        }
    }
    
};



#endif