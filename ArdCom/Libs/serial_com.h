#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include  <termios.h>

int iniciarComunicacion(const char *puerto);

int enviarComando(int fd, const char *comando);

int leerRespuesta(int fd, char *respuesta, int longitud);

void cerrarComunicacion(int fd);

#endif //SERIAL_COM_H
