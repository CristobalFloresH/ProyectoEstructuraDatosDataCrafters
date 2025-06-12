void modificarImputado(struct ministerio *ministerio, char *rucCausa, char *rutImputado) {
    if (ministerio == NULL || rucCausa == NULL || rutImputado == NULL) {
        return;
    }

    struct causa *c = buscarCausaPorRuc(ministerio->causas, rucCausa);
    if (c == NULL) {
        printf("Causa con RUC %s no encontrada.\n", rucCausa);
        return;
    }

    struct involucrados *imp = buscarImputadoEnCausa(c, rutImputado);
    if (imp == NULL || imp->tipoInvolucrado != 2) {
        printf("Imputado con RUT %s no encontrado en la causa.\n", rutImputado);
        return;
    }

    if (imp->datosImputados == NULL) {
        imp->datosImputados = (struct datosImputados *) malloc(sizeof(struct datosImputados));
        if (imp->datosImputados != NULL) {
            memset(imp->datosImputados, 0, sizeof(struct datosImputados));
        } else {
            printf("Error al crear datos del imputado.\n");
            return;
        }
    }

    struct datosImputados *datos = imp->datosImputados;

    int opcion = -1;
    char palabras[300];
    char *nuevaCadena;

    while (opcion != 0) {
        printf("\n--- Modificar Imputado ---\n");
        printf("1. Declaracion\n");
        printf("2. Medida Cautelar\n");
        printf("3. Fecha Inicio Medida\n");
        printf("4. Fecha Fin Medida\n");
        printf("5. Estado Procesal\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese nueva declaracion: ");
                if (fgets(palabras, sizeof(palabras), stdin)) {
                    palabras[strcspn(palabras, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabras);
                    if (nuevaCadena != NULL) {
                        if (datos->declaracion != NULL) {
                            free(datos->declaracion);
                        }
                        datos->declaracion = nuevaCadena;
                    }
                }
                break;

            case 2:
                int nueva_medida;
                do {
                    printf("Ingrese nueva medida cautelar (1 = Prision Preventiva, 2 = Arraigo Nacional, 3 = Firma Periodica, "
                           "4 = Orden de Alejamiento, 5 = Arresto Domiciliario, 6 = Libertad bajo Fianza, 7 = Ninguna): ");

                    scanf("%d", &nueva_medida);
                    getchar();


                    if (nueva_medida < 1 || nueva_medida > 7) {
                        printf("Medida cautelar no valida. Intente nuevamente.\n");
                        }

                } while (nueva_medida < 1 || nueva_medida > 7);

                datos->medidasCautelar = nueva_medida;
                printf("Medida cautelar actualizada correctamente.\n");


            case 3:
                printf("Ingrese nueva fecha de inicio (YYYY-MM-DD): ");
                if (fgets(palabras, sizeof(palabras), stdin)) {
                    palabras[strcspn(palabras, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabras);
                    if (nuevaCadena != NULL) {
                        if (datos->fechaInicioMedida != NULL) {
                            free(datos->fechaInicioMedida);
                        }
                        datos->fechaInicioMedida = nuevaCadena;
                    }
                }
                break;

            case 4:
                printf("Ingrese nueva fecha de fin (YYYY-MM-DD): ");
                if (fgets(palabras, sizeof(palabras), stdin)) {
                    palabras[strcspn(palabras, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabras);
                    if (nuevaCadena != NULL) {
                        if (datos->fechaFinMedida != NULL) {
                            free(datos->fechaFinMedida);
                        }
                        datos->fechaFinMedida = nuevaCadena;
                    }
                }
                break;

            case 5:
                int nuevo_estado;
                do {
                    printf("Ingrese nuevo estado procesal (1: Cautelar, 2: Formalizado, 3: Sobreseido): ");

                    scanf("%d", &nuevo_estado);
                    getchar();

                    if (nuevo_estado < 1 || nuevo_estado > 3) {
                    printf("Estado procesal no valido. Intente nuevamente.\n");
                    }

                } while (nuevo_estado < 1 || nuevo_estado > 3);

                datos->estadoProcesal = nuevo_estado;
                printf("Estado procesal actualizado correctamente.\n");

            case 0:
                //Volver.
                break;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}
