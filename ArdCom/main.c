#include "Libs/serial_com.h"
#include <stdio.h>
#include <string.h>

int main() {
    int fd;
    char command[100];
    char response[100];

    // Iniciar la comunicación con el puerto serial
    fd = iniciarComunicacion("/dev/ttyACM0");  // Ajustar según el puerto utilizado
    if (fd == -1) {
        return 1;
    }

    // Bucle que se mantendrá activo hasta que el usuario escriba 'q'
    while (1) {
        printf("Escribe 'On' para encender el LED, 'Off' para apagarlo o 'q' para salir: ");
        scanf("%s", command);


        if (strcmp(command, "q") == 0) {
            printf("Saliendo del programa...\n");
            break;
        }

        // Enviar comando y leer respuesta
        if (enviarComando(fd, command)) {
            leerRespuesta(fd, response, sizeof(response));
        }
    }

    // Cerrar la comunicación
    cerrarComunicacion(fd);
    return 0;
}
