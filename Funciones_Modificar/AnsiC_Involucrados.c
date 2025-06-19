void cambiarTipoInvolucrado(struct ministerio *ministerio) {
    char ruc[100];
    char rut[100];
    int nuevoTipo;
    int encontrado;
    int i;
    struct causa *c = NULL;
    struct involucrados *inv = NULL;

    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    printf("Ingrese el RUC de la causa: ");
    fgets(ruc, sizeof(ruc), stdin);
    removerSaltoLinea(ruc);

    c = buscarCausaPorRuc(ministerio->causas, ruc);
    if (c == NULL || c->involucrados == NULL) {
        printf("No se encontró la causa o no tiene involucrados.\n");
        return;
    }

    printf("Ingrese el RUT del involucrado: ");
    fgets(rut, sizeof(rut), stdin);
    removerSaltoLinea(rut);

    do {
        printf("Ingrese nuevo tipo de involucrado (1=Víctima, 2=Imputado, 3=Testigo, 4=Otro): ");
        scanf("%d", &nuevoTipo);
        getchar();
        if (nuevoTipo < 1 || nuevoTipo > 4) {
            printf("Tipo inválido. Intente nuevamente.\n");
        }
    } while (nuevoTipo < 1 || nuevoTipo > 4);

    encontrado = 0;

    for (i = 0; i < c->tamInvolucrados; i++) {
        inv = c->involucrados[i];

        if (inv != NULL && inv->persona != NULL && strcmp(inv->persona->rut, rut) == 0) {
            encontrado = 1;

            if (inv->tipoInvolucrado == 2 && nuevoTipo != 2 && inv->datosImputados != NULL) {
                free(inv->datosImputados);
                inv->datosImputados = NULL;
            }

            inv->tipoInvolucrado = nuevoTipo;

            if (nuevoTipo == 2 && inv->datosImputados == NULL) {
                inv->datosImputados = (struct datosImputados *)malloc(sizeof(struct datosImputados));
                if (inv->datosImputados == NULL) {
                    printf("Error al asignar memoria para datosImputados.\n");
                    return;
                }

                inv->datosImputados->declaracion = NULL;
                inv->datosImputados->medidasCautelar = 7;
                inv->datosImputados->fechaInicioMedida = NULL;
                inv->datosImputados->fechaFinMedida = NULL;
                inv->datosImputados->estadoProcesal = 1;
            }

            printf("Tipo de involucrado cambiado exitosamente para RUT: %s\n", rut);
            break;
        }
    }

    if (!encontrado) {
        printf("Involucrado con RUT %s no encontrado en la causa.\n", rut);
    }
}
