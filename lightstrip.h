#ifndef __LIGHT_STRIP_H__
#define __LIGHT_STRIP_H__

#include <Adafruit_NeoPixel.h>

class LightStrip : public Adafruit_NeoPixel {

private:
  uint8_t brightness;
  
public:
  LightStrip(int, int);
  
  void setColor(uint32_t color, uint32_t mask = 0xFFFFFFFF, bool clear = false);
  void setColorAndShow(uint32_t color, uint32_t mask = 0xFFFFFFFF, bool clear = false);
  void fadeOut(uint32_t time = 0);
  void fadeIn(uint32_t time = 0);
  
  uint8_t getBrightness();
  void    setBrightness(uint8_t value);
  
};

#endif /* __LIGHT_STRIP_H__ */
