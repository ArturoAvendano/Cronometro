///función para el envio de datos a traves de SoftwareSerial, es necesario el caracter '\n' para la recepción
void impresion(){
reloj.print("Hora: ");
reloj.print(ti.hour);
reloj.print(':');
reloj.print(ti.min);
reloj.print(':');
reloj.print(ti.sec);
reloj.print(" ");
reloj.print("Temperatura: ");
reloj.print(t);
reloj.print('C');
reloj.print(" ");
reloj.print("Humedad: ");
reloj.print(h);
reloj.print('%');
reloj.print(" ");
reloj.print('\n');    
}

