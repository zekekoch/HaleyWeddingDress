#ifndef ANIMATION_H
#define ANIMATION_H
 
#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"
 
 
class Animation 
{
        //void setLeds(struct CRGB lights[]);
	private:
		int _internalFrame;
		int _startPixel;
		int _endPixel;
		int _currentPixel;
		int _localFrame;
		int _numLeds;
		int _animationType;
		int _animationIndex;
		bool _chaseForward;

	public:
		// Sometimes chipsets wire in a backwards sort of way
		struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
		CRGB* leds; // struct CRGB { unsigned char r; unsigned char g; unsigned char b; };

		//<<constructor>> setup the LED, make pin 13 an OUTPUT
		Animation(CRGB* lights, int numLeds)
		{
			_startPixel = 0;
			_endPixel = 0;
			_currentPixel = 0;
			_localFrame = 0;
			_numLeds = 0;
			_animationType = 0;
			_animationIndex++;
			_numLeds = numLeds;
			leds = lights;
			/* nothing for now */
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
		
		//turn the LED off
		void play()
		{
		//	Serial.print(_animationIndex);Serial.print(" ");Serial.print("play ");Serial.print(_animationType);Serial.println();
				
			switch(_animationType)
			{
				case (0):
					runSolid();
					break;
				case (1):
					runChase();
					break;
				case (2):
					runFade();
					break;
			}
		}
		
		void clear()
		{
			memset(leds, 0, _numLeds * sizeof(struct CRGB));
		}
		
		void chase(int start, int end, int color)
		{
		//	Serial.print(_animationIndex);Serial.print(" ");Serial.println("start chase");
			
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
		}
		
		void runChase()
		{
		//	Serial.print(_animationIndex);Serial.print(" ");Serial.println("runChase");
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
			leds[_currentPixel].r = 255;
			leds[_currentPixel].g = 0;
			leds[_currentPixel].b = 0;
			// nothing
		}	

		
		void solid(int start, int end, int color)
		{
		//	Serial.print(_animationIndex);Serial.print(" ");Serial.println("start solid");
		
			_startPixel = start;
			_currentPixel = start;
			_endPixel = end;
			_animationType = 0;
		}
		
		void fade(int start, int end, int color)
		{
		//	Serial.print(_animationIndex);Serial.print(" ");Serial.println("start solid");
		
			_startPixel = start;
			_currentPixel = start;
			_endPixel = end;
			_animationType = 2;
		}
		
		void runSolid()
		{
		//	Serial.print(_animationIndex);Serial.print(" ");Serial.println("runSolid");
			for(int i = _startPixel;i<=_endPixel;i++)
			{
				leds[i].r = 0;
				leds[i].g = 0;
				leds[i].b = 255;
			}
		
		}
		
		void runFade()
		{
			static byte fadeLevel = 0;
			static byte direction = 0;
		
		//	Serial.print("fade ");Serial.print(fadeLevel);Serial.print(" dir ");Serial.print(direction);Serial.println();
			
			if (direction == 0)
			{
				fadeLevel++;
				if (fadeLevel == 255)
					direction = 1; 
			}
			else if (direction == 1)
			{
				fadeLevel--;
				if (fadeLevel == 0)
					direction = 0;
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