/*
 This file is part of Livecut
 Copyright 2004 by Remy Muller.
 
 AnalogDelay can be redistributed and/or modified under the terms of the
 GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.
 
 AnalogDelay is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with AnalogDelay; if not, visit www.gnu.org/licenses or write to the
 Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
 Boston, MA 02111-1307 USA
 */

#ifndef FIRST_ORDER_LOWPASS_H
#define FIRST_ORDER_LOWPASS_H

class FirstOrderLowpass
{
public:
	FirstOrderLowpass()
	: lambda(0)
	, sr(0)
	, lastout(0)
	{
	}
  
	~FirstOrderLowpass() 
  {
  }
  
	inline float tick(float x)
	{
		add_white_noise(x);
		lastout *= lambda;
		lastout += (1.f-lambda)*x;
		return lastout;
	}
	
  inline float LastOut() 
  {
    return lastout;
  }
	
  void SetTimeConstant(float t) 
  {
    time = t; 
    lambda = exp(log(1.0-0.66)/(0.001*time*sr));
  }
	
  void SetSampleRate(float samplerate) 
  {
    sr = samplerate; 
    SetTimeConstant(time);
  }
	
  void clear() 
  {
    lastout = 0.0f;
  }
	
  inline void add_white_noise (float &val)
	{
    static unsigned int rand_state = rand_state * 1234567UL + 890123UL;
    int mantissa = rand_state & 0x807F0000; // Keep only most significant bits
    int flt_rnd = mantissa | 0x1E000000; // Set exponent
    val += *reinterpret_cast <const float *> (&flt_rnd);
	}
	
  inline void SetState(float v)
  {
    lastout=v;
  }
  
protected:
	float lambda;
	float sr;
	float lastout;
	float time;  
};

#endif