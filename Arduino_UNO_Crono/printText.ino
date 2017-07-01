///Función de núcleo, impresion estática
void printText(uint8_t modStart, uint8_t modEnd, char *pMsg)
{
  uint8_t   state_static = 0;
  uint8_t   curLen_static;
  uint16_t  showLen_static;
  uint8_t   cBuf_static[8];
  int16_t   col_static = ((modEnd + 1) * COL_SIZE) - 1;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     
  {
    switch(state_static)
    {
      case 0: 
        
        if (*pMsg == '\0')
        {
          showLen_static = col_static - (modEnd * COL_SIZE);  
          state_static = 2;
          break;
        }
        showLen_static = mx.getChar(*pMsg++, sizeof(cBuf_static)/sizeof(cBuf_static[0]), cBuf_static);
        curLen_static = 0;
        state_static++;

      case 1: // display the next part of the character
        mx.setColumn(col_static--, cBuf_static[curLen_static++]);

        // done with font character, now display the space between chars
        if (curLen_static == showLen_static)
        {
          showLen_static = CHAR_SPACING;
          state_static = 2;
        }
        break;

      case 2: 
        curLen_static = 0;
        state_static++;
    

      case 3: 
        mx.setColumn(col_static--, 0);
        curLen_static++;
        if (curLen_static == showLen_static)
          state_static = 0;
        break;

      default:
        col_static = -1;   
    }
  } while (col_static >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}
