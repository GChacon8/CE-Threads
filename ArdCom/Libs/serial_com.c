#include "serial_com.h"
#include <fcntl.h>    // Para el control de archivos
#include <unistd.h>   // Para las operaciones de lectura/escritura
#include <stdio.h>
#include <string.h>
#include <termios.h>  // Para la configuración del puerto serial

int iniciarComunicacion(const char *puerto) {
    int fd = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("Error al abrir el puerto %s\n", puerto);
        return -1;
    }

    struct termios options;
    tcgetattr(fd, &options);  // Obtener la configuración actual del puerto

    // Configurar la velocidad del puerto a 9600 baudios
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);   // Activar el receptor y establecer la conexión local
    options.c_cflag &= ~CSIZE;             // Limpiar el tamaño de los bits
    options.c_cflag |= CS8;                // 8 bits de datos
    options.c_cflag &= ~PARENB;            // Sin paridad
    options.c_cflag &= ~CSTOPB;            // 1 bit de parada
    options.c_cflag &= ~CRTSCTS;           // Sin control de flujo hardware

    // Configuración de los timeouts
    options.c_cc[VMIN]  = 0;    // Sin bytes mínimos requeridos para la lectura
    options.c_cc[VTIME] = 10;   // Tiempo de espera (1 decisegundo)

    // Aplicar la configuración al puerto
    tcsetattr(fd, TCSANOW, &options);

    return fd;
}

int enviarComando(int fd, const char *comando) {
    int bytes_written = write(fd, comando, strlen(comando));
    if (bytes_written < 0) {
        printf("Error escribiendo al puerto serial\n");
        return 0;
    }
    printf("%d bytes enviados\n", bytes_written);
    return 1;
}

int leerRespuesta(int fd, char *respuesta, int longitud) {
    int total_bytes_read = 0;
    int bytes_read;

    // Leer hasta que no haya más datos o se alcance el límite de longitud
    do {
        bytes_read = read(fd, respuesta + total_bytes_read, longitud - total_bytes_read);
        if (bytes_read < 0) {
            printf("Error leyendo del puerto serial\n");
            return 0;
        }
        total_bytes_read += bytes_read;
    } while (bytes_read > 0 && total_bytes_read < longitud - 1);

    respuesta[total_bytes_read] = '\0';  // Terminar cadena de respuesta
    printf("Respuesta del Arduino: %s\n", respuesta);
    return 1;
}

void cerrarComunicacion(int fd) {
    close(fd);  // Cerrar el descriptor de archivo
}
