///Función de núcleo, devuelve el texto luego de pasar por la matriz completa
void scrollDataSink(uint8_t dev, MD_MAX72XX::transformType_t t, uint8_t col)
{
#if PRINT_CALLBACK
  reloj.print("\n cb ");
  reloj.print(dev);
  reloj.print(' ');
  reloj.print(t);
  reloj.print(' ');
  reloj.println(col);
#endif
}

