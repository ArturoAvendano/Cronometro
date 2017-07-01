///Función de núcleo, Recibe datos para la función estática y los guarda en un array distinto al Scroll
void readSerial_Static(void)
{
  static uint8_t  putIndex = 0;

  while (reloj.available())
  {
    message_static[putIndex] = (char)reloj.read();
    if ((message_static[putIndex] == '\n') || (putIndex >= BUF_SIZE - 3))
    {
      message_static[putIndex] = '\0';
      putIndex = 0;
      newMessageAvailable_static = true;
    }
    else
      message_static[putIndex++];
  }
}
