///Función de núcleo, permite el Scroll por la matriz
uint8_t scrollDataSource(uint8_t dev, MD_MAX72XX::transformType_t t)
{
  static char   *p = curMessage;
  static uint8_t  state = 0;
  static uint8_t  curLen, showLen;
  static uint8_t  cBuf[8];
  uint8_t colData;

  
  switch(state)
  {
    case 0: 
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
      curLen = 0;
      state++;

      if (*p == '\0')
      {
        p = curMessage;     
        if (newMessageAvailable)  
        {
          strcpy(curMessage, newMessage);
          newMessageAvailable = false;
        }
      }
      

    case 1: 
      colData = cBuf[curLen++];
      if (curLen == showLen)
      {
        showLen = CHAR_SPACING;
        curLen = 0;
        state = 2;
      }
      break;

    case 2: 
      colData = 0;
      curLen++;
      if (curLen == showLen)
        state = 0;
      break;

    default:
      state = 0;
  }

  return(colData);
}
