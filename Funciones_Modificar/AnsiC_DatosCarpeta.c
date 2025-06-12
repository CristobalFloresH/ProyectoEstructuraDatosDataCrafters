void modificarDatosCarpeta(struct ministerio *ministerio) { // funcion lista
    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    char ruc[100];
    printf("Ingrese el RUC de la causa: ");
    fgets(ruc, sizeof(ruc), stdin);
    removerSaltoLinea(ruc);

    struct causa* causa = buscarCausaPorRuc(ministerio->causas, ruc);
    if (causa == NULL) {
        printf("No se encontró una causa con ese RUC.\n");
        return;
    }

    if (causa->datosCarpetas == NULL) {
        printf("No hay carpetas investigativas en esta causa.\n");
        return;
    }

    // Solicitar fecha y tipo de dato
    char fecha[100];
    int tipo;

    printf("Ingrese la fecha de la carpeta que desea modificar (YYYY-MM-DD): ");
    fgets(fecha, sizeof(fecha), stdin);
    removerSaltoLinea(fecha);

    do {
        printf("Ingrese el tipo de dato (1=declaraciones, 2=pruebas generales, 3=diligencias, 4=denuncia): ");
        scanf("%d", &tipo);
        getchar();

        if (tipo < 1 || tipo > 4) {
            printf("Tipo inválido. Intente nuevamente.\n");
        }
    } while (tipo < 1 || tipo > 4);

    // Buscar carpeta específica
    struct datosCarpeta *carpeta = buscarCarpetaPorTipoYFecha(causa->datosCarpetas, tipo, fecha);
    if (carpeta == NULL) {
        printf("No se encontró una carpeta con esa fecha y tipo.\n");
        return;
    }

    // Menú de modificación
    int opcion = -1;
    char buffer[300];
    char* nuevaCadena;

    while (opcion != 0) {
        printf("\n--- Modificar Datos de Carpeta ---\n");
        printf("1. Modificar fecha (Actual: %s)\n", carpeta->fecha);
        printf("2. Modificar descripción (Actual: %s)\n", carpeta->descripcion);
        printf("3. Modificar tipo de dato (Actual: %d)\n", carpeta->tipoDeDato);
        printf("0. Salir\n");
        printf("Seleccione una opción: ");

        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese nueva fecha (YYYY-MM-DD): ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    free(carpeta->fecha);
                    carpeta->fecha = nuevaCadena;
                    printf("Fecha actualizada correctamente.\n");
                }
                break;

            case 2:
                printf("Ingrese nueva descripción: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (nuevaCadena != NULL) {
                        free(carpeta->descripcion);
                        carpeta->descripcion = nuevaCadena;
                        printf("Descripción actualizada correctamente.\n");
                    } else {
                        printf("Error al asignar memoria.\n");
                    }
                }
                break;

            case 3: {
                int nuevo_tipo;
                do {
                    printf("Ingrese nuevo tipo de dato (1=declaraciones, 2=pruebas, 3=diligencias, 4=denuncia): ");
                    scanf("%d", &nuevo_tipo);
                    getchar();

                    if (nuevo_tipo < 1 || nuevo_tipo > 4) {
                        printf("Tipo inválido. Intente nuevamente.\n");
                    }
                } while (nuevo_tipo < 1 || nuevo_tipo > 4);

                carpeta->tipoDeDato = nuevo_tipo;
                printf("Tipo de dato actualizado correctamente.\n");
                break;
            }

            case 0:
                printf("Saliendo de modificación de carpeta.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    }
}
