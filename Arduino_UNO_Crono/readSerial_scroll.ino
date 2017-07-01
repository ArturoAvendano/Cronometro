///Función de núcleo, recibe datos para la función Scroll y los almacena en un array
void readSerial_scroll(void)
{
  static uint8_t  putIndex = 0;

  while (reloj.available())
  {
    newMessage[putIndex] = (char)reloj.read();
    if ((newMessage[putIndex] == '\n') || (putIndex >= BUF_SIZE-3)) 
    {
      newMessage[putIndex++] = ' ';
      newMessage[putIndex] = '\0';
      putIndex = 0;
      newMessageAvailable = true;
    }
    else
      newMessage[putIndex++];
  }
}
