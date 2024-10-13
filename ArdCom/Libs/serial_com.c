#include "serial_com.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

/**
 * Esta funcion inicia la comunicación con el arduino
 * @param puerto_serial Un string con el puerto donde está el arduino
 * @return
 */
int iniciarComunicacion(const char *puerto_serial) {
    int fd = open(puerto_serial, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("Error al abrir el puerto serial");
        return -1;
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error obteniendo los atributos del puerto serial");
        close(fd);
        return -1;
    }

    tty.c_cflag &= ~PARENB; // Sin paridad
    tty.c_cflag &= ~CSTOPB; // 1 bit de parada
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;     // 8 bits de datos
    tty.c_cflag &= ~CRTSCTS; // Sin control de hardware
    tty.c_cflag |= CREAD | CLOCAL; // Activar la lectura y sin control de línea

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    tty.c_lflag &= ~ICANON;  // Modo no canónico
    tty.c_lflag &= ~ECHO;    // Sin eco
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ISIG;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // Sin control de flujo por software
    tty.c_oflag &= ~OPOST;  // Sin procesamiento de salida

    tty.c_cc[VMIN] = 1;     // Leer al menos 1 byte
    tty.c_cc[VTIME] = 10;   // Timeout de 1 segundo

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error configurando el puerto serial");
        close(fd);
        return -1;
    }

    return fd;
}

/**
 * Esta funcion envia un comando por el puerto serial
 * @param fd Un int de estado
 * @param comando String con el comando a enviar al arduino
 * @return Un valor de resultado
 */
int enviarComando(int fd, const char *comando) {
    // Añadir un salto de línea al comando si es necesario
    char comando_con_salto[100];
    snprintf(comando_con_salto, sizeof(comando_con_salto), "%s\n", comando);

    int n_written = write(fd, comando_con_salto, strlen(comando_con_salto));
    if (n_written < 0) {
        perror("Error enviando el comando al puerto serial");
        return 0;
    }
    return 1;
}

/**
 * Esta funcion se encarga de leer la respuesta de la comunicacion serial
 * @param fd Un int de estado
 * @param respuesta String con la respuesta del arduino
 * @param tamano Tamaño del string respuesta
 * @return Int de estado
 */
int leerRespuesta(int fd, char *respuesta, int tamano) {
    memset(respuesta, 0, tamano);  // Limpiar buffer de respuesta
    int n_read = read(fd, respuesta, tamano);

    if (n_read < 0) {
        perror("Error leyendo la respuesta del puerto serial");
        return 0;
    } else if (n_read == 0) {
        printf("No se recibió respuesta del Arduino\n");
        return 0;
    }

    respuesta[n_read] = '\0';  // Asegurarse de que la cadena termine
    printf("Respuesta del Arduino: %s\n", respuesta);
    return 1;
}


/**
 * Esta funcion cierra la comunicacion serial
 * @param fd Un int de estado
 */
void cerrarComunicacion(int fd) {
    close(fd);
}
