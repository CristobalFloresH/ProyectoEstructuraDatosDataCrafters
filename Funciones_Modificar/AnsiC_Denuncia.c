void modificarDenunciaMenu(struct ministerio *ministerio) {
    char ruc[20], rut[20];
    char buffer[300];
    int opcion;
    char *nuevaCadena;
    struct denuncia *denunciaMod;
    struct persona *personaBuscada;

    opcion = -1;
    nuevaCadena = NULL;
    denunciaMod = NULL;

    printf("Ingrese el RUT de la persona a la cual le pertenezca la denuncia que desea modificar: ");
    if (fgets(rut, sizeof(rut), stdin)) {
        removerSaltoLinea(rut);
    } else {
        printf("Error al leer el RUT.\n");
        return;
    }

    personaBuscada = buscarPersonaPorRut(ministerio->personas, rut);
    if (personaBuscada == NULL) {
        printf("Persona con RUT %s no encontrada.\n", rut);
        return;
    }
    if (personaBuscada->denuncias == NULL) {
        printf("La persona no tiene denuncias.\n");
        return;
    }

    printf("Ingrese el RUC de la denuncia que desea modificar: ");
    if (fgets(ruc, sizeof(ruc), stdin)) {
        removerSaltoLinea(ruc);
    } else {
        printf("Error al leer el RUC.\n");
        return;
    }


    denunciaMod = buscarDenunciaPorRuc(personaBuscada->denuncias, ruc);
    if (denunciaMod == NULL) {
        printf("No se encontro una denuncia con el RUC ingresado.\n");
        return;
    }

    while (opcion != 4) {
        printf("\n--- MODIFICAR DENUNCIA ---\n");
        printf("1. Modificar Fecha (Actual: %s)\n", denunciaMod->fecha);
        printf("2. Modificar Descripcion (Actual: %s)\n", denunciaMod->descripcion);
        printf("3. Modificar Tipo de Denuncia (Actual: %s)\n", denunciaMod->tipoDeDenuncia);
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese nueva fecha (YYY-MM-DD): ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (denunciaMod->fecha != NULL) {
                        free(denunciaMod->fecha);
                    }
                    denunciaMod->fecha = nuevaCadena;
                    printf("Fecha modificada correctamente.\n");
                }
                break;

            case 2:
                printf("Ingrese nueva descripcion: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (denunciaMod->descripcion != NULL) {
                        free(denunciaMod->descripcion);
                    }
                    denunciaMod->descripcion = nuevaCadena;
                    printf("Descripcion modificada correctamente.\n");
                }
                break;

            case 3:
                printf("Ingrese nuevo tipo de denuncia: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (denunciaMod->tipoDeDenuncia != NULL) {
                        free(denunciaMod->tipoDeDenuncia);
                    }
                    denunciaMod->tipoDeDenuncia = nuevaCadena;
                    printf("Tipo de denuncia modificado correctamente.\n");
                }
                break;

            case 4:
                printf("Saliendo del menu de modificacion.\n");
                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    }
}
