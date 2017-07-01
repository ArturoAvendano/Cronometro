///Calcula el largo del array y el tiempo que tarda en pasar por la matriz
void scrollText(void)
{
  static uint32_t prevTime = 0;
  
  if (millis()-prevTime >= scrollDelay)
  {
    mx.transform(MD_MAX72XX::TSL);  
    prevTime = millis();      
  }
}
///obtiene el valor de la velocidad de Scroll en el caso 
///que se use un potenciometro
uint16_t getScrollDelay(void)
{
#if USE_POT_CONTROL
  uint16_t  t;

  t = analogRead(SPEED_IN);
  t = map(t, 0, 1023, 25, 250);

  return(t);
#else
  return(SCROLL_DELAY);
#endif
}
