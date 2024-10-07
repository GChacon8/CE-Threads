#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    char command[100];

    // Abrir el puerto COM (ajusta "COM3" según el puerto que esté usando tu Arduino)
    hSerial = CreateFile(
        "\\\\.\\COM3",                // Puerto serial
        GENERIC_READ | GENERIC_WRITE, // Permisos de lectura y escritura
        0,                            // No compartir
        NULL,                         // Sin atributos de seguridad
        OPEN_EXISTING,                // Solo abrir si existe
        0,                            // Atributos de archivo
        NULL);                        // Sin template

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error al abrir el puerto COM\n");
        return 1;
    }

    // Configurar los parámetros del puerto serial
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error obteniendo el estado del puerto serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;    // Configura la velocidad a 9600 baudios
    dcbSerialParams.ByteSize = 8;           // 8 bits de datos
    dcbSerialParams.StopBits = ONESTOPBIT;  // 1 bit de parada
    dcbSerialParams.Parity   = NOPARITY;    // Sin paridad

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error configurando el puerto serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Configurar los timeouts
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error configurando timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Bucle que se mantendrá activo hasta que el usuario escriba 'q'
    while (1) {
        // Pedir comando al usuario
        printf("Escribe 'On' para encender el LED, 'Off' para apagarlo o 'q' para salir: ");
        scanf("%s", command);

        // Verificar si el usuario quiere salir
        if (strcmp(command, "q") == 0) {
            printf("Saliendo del programa...\n");
            break;  // Salir del bucle
        }

        // Enviar el comando al Arduino
        DWORD bytes_written;
        if (!WriteFile(hSerial, command, strlen(command), &bytes_written, NULL)) {
            printf("Error escribiendo al puerto serial\n");
            CloseHandle(hSerial);
            return 1;
        }
        printf("%ld bytes enviados\n", bytes_written);

        // Leer la respuesta del Arduino
        char response[100] = {0};
        DWORD bytes_read;
        int total_bytes_read = 0;

        // Leer todos los datos disponibles
        do {
            if (!ReadFile(hSerial, response + total_bytes_read, sizeof(response) - total_bytes_read, &bytes_read, NULL)) {
                printf("Error leyendo del puerto serial\n");
                CloseHandle(hSerial);
                return 1;
            }
            total_bytes_read += bytes_read;
        } while (bytes_read > 0 && total_bytes_read < sizeof(response) - 1);

        printf("Respuesta del Arduino: %s\n", response);
    }

    // Cerrar el puerto serial
    CloseHandle(hSerial);
    return 0;
}
