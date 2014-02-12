#include "lib.h"
/*
void Prettylight(Strip *s){
  int r=0;
  int o=r-1;
  int y=o-1;
  int g=y-1;
  int b=g-1;
  int p=b-1;
  int e=p-1;

  setPixelsRGB(s, 0, 0, 0);
  for(int pixelstrip=0; pixelstrip<=4+s->numPixels(); pixelstrip++){
    s->setPixelColor(r, 255, 0, 0);
    s->setPixelColor(o, 255, 102, 0);
    s->setPixelColor(y, 255, 233, 0);
    s->setPixelColor(g, 0, 255, 0); 
    s->setPixelColor(b, 0, 0, 255);
    s->setPixelColor(p, 159, 0, 197);
    s->setPixelColor(e, 0, 0, 0);
    r++;
    o++;
    y++;
    g++;
    b++;
    p++;
    e++;
    Serial.print(r);
    Serial.print(o);
    s->show();
    delay(100);
  }
}*/
  
 void Prettylight(Strip *s){
//    uint32_t rainbow[6] = new uint32_t[6];
    
    
    uint32_t rainbow[6] = {
      rainbow[0]=s->Color(255, 0, 0),
      rainbow[1]=s->Color(255, 102, 0),
      rainbow[2]=s->Color(255, 233, 0),
      rainbow[3]=s->Color(0, 255, 0),
      rainbow[4]=s->Color(0, 0, 255), 
      rainbow[5]=s->Color(159, 0, 197)
    };
    
    
    /*rainbow[0]=s->Color(255, 0, 0);
    rainbow[1]=s->Color(255, 102, 0);
    rainbow[2]=s->Color(255, 233, 0);
    rainbow[3]=s->Color(0, 255, 0);
    rainbow[4]=s->Color(0, 0, 255); 
    rainbow[5]=s->Color(159, 0, 197);
    */
    
    //setPixelsRGB(s, 0, 0, 0);
    for(int pos = 0; pos < s->numPixels(); pos++){
      for(int i = 0; i < s->numPixels(); ++i){
        s->setPixelColor(s->numPixels()-i, rainbow[((pos+i)%6)]);
      }
//      s->setPixelColor(r, 255, 0, 0);
//      Serial.print(r);
      s->show();
      delay(100);
    }
 }  
 