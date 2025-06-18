/* Función auxiliar para encontrar el primer salto de línea */
int encontrarSaltoLinea(char* cadena) {
    int i;
    i = 0;

    while (cadena[i] != '\0') {
        if (cadena[i] == '\n') {
            return i;
        }
        i++;
    }
    return -1; /* No se encontró salto de línea */
}

/* Función auxiliar para remover el salto de línea */
void removerSaltoLinea(char* cadena) {
    int pos;
    pos = encontrarSaltoLinea(cadena);

    if (pos != -1) {
        cadena[pos] = '\0';
    }
}

char* duplicarCadena(char* origen) {
    char* destino;
    int longitud;
    int i;

    destino = NULL;
    longitud = 0;
    i = 0;

    if (origen == NULL) {
        return NULL;
    }

    /* Calcular longitud de la cadena */
    while (origen[longitud] != '\0') {
        longitud++;
    }

    /* Asignar memoria */
    destino = (char*)malloc((longitud + 1) * sizeof(char));
    if (destino == NULL) {
        return NULL;
    }

    /* Copiar cadena */
    for (i = 0; i <= longitud; i++) {
        destino[i] = origen[i];
    }

    return destino;
}




void modificarDatosDiligencia(struct ministerio *ministerio) {
    // Variables declaradas al principio
    char ruc[20], fechaInicio[50], tipoDiligencia[50];
    char buffer[300];
    char *nuevaCadena;
    int opcion = -1;
    int nueva_prioridad = 0;  // usado en case 1
    struct datosDiligencias *diligencia = NULL;

    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    printf("Ingrese el RUC de la causa: ");
    scanf("%s", ruc);
    getchar(); // limpiar '\n'
    printf("Ingrese la fecha de inicio de la diligencia (YYYY-MM-DD): ");
    scanf("%s", fechaInicio);
    getchar();
    printf("Ingrese el tipo de diligencia: ");
    scanf("%s", tipoDiligencia);
    getchar();

    diligencia = buscarDiligencia(ministerio, ruc, fechaInicio, tipoDiligencia);
    if (diligencia == NULL) {
        printf("No se encontró la diligencia con esos datos.\n");
        return;
    }

    while (opcion != 0) {
        printf("\n--- Modificar Datos de Diligencia ---\n");
        printf("1. Modificar prioridad (Actual: %d)\n", diligencia->prioridad);
        printf("2. Modificar fecha inicio (Actual: %s)\n", diligencia->fechaInicio);
        printf("3. Modificar fecha fin (Actual: %s)\n", diligencia->fechaFin);
        printf("4. Modificar descripción (Actual: %s)\n", diligencia->descripcion);
        printf("5. Modificar estado (Actual: %s)\n", diligencia->estado);
        printf("6. Modificar tipo de diligencia (Actual: %s)\n", diligencia->tipoDiligencia);
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1:
                do {
                    printf("Ingrese nueva prioridad (1 = muy baja, ..., 5 = muy alta): ");
                    scanf("%d", &nueva_prioridad);
                    getchar();
                    if (nueva_prioridad < 1 || nueva_prioridad > 5)
                        printf("Prioridad inválida. Intente nuevamente.\n");
                } while (nueva_prioridad < 1 || nueva_prioridad > 5);
                diligencia->prioridad = nueva_prioridad;
                printf("Prioridad actualizada correctamente.\n");
                break;

            case 2:
                printf("Ingrese nueva fecha inicio (YYYY-MM-DD): ");
                scanf("%s", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->fechaInicio);
                    diligencia->fechaInicio = nuevaCadena;
                    printf("Fecha inicio actualizada correctamente.\n");
                }
                break;

            case 3:
                printf("Ingrese nueva fecha fin (YYYY-MM-DD): ");
                scanf("%s", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->fechaFin);
                    diligencia->fechaFin = nuevaCadena;
                    printf("Fecha fin actualizada correctamente.\n");
                }
                break;

            case 4:
                printf("Ingrese nueva descripción: ");
                scanf(" %[^\n]", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->descripcion);
                    diligencia->descripcion = nuevaCadena;
                    printf("Descripción actualizada correctamente.\n");
                }
                break;

            case 5:
                printf("Ingrese nuevo estado: ");
                scanf(" %[^\n]", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->estado);
                    diligencia->estado = nuevaCadena;
                    printf("Estado actualizado correctamente.\n");
                }
                break;

            case 6:
                printf("Ingrese nuevo tipo de diligencia: ");
                scanf(" %[^\n]", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->tipoDiligencia);
                    diligencia->tipoDiligencia = nuevaCadena;
                    printf("Tipo de diligencia actualizado correctamente.\n");
                }
                break;

            case 0:
                printf("Saliendo del menú de modificación.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    }
}

void modificarDatosCarpeta(struct ministerio *ministerio) {
    // Declaraciones al inicio
    char ruc[100];
    struct causa* causa;
    char fecha[100];
    int tipo;
    struct datosCarpeta *carpeta;
    int opcion = -1;
    char buffer[300];
    char* nuevaCadena;
    int nuevo_tipo;

    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    printf("Ingrese el RUC de la causa: ");
    fgets(ruc, sizeof(ruc), stdin);
    removerSaltoLinea(ruc);

    causa = buscarCausaPorRuc(ministerio->causas, ruc);
    if (causa == NULL) {
        printf("No se encontró una causa con ese RUC.\n");
        return;
    }

    if (causa->datosCarpetas == NULL) {
        printf("No hay carpetas investigativas en esta causa.\n");
        return;
    }

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

    carpeta = buscarCarpetaPorTipoYFecha(causa->datosCarpetas, tipo, fecha);
    if (carpeta == NULL) {
        printf("No se encontró una carpeta con esa fecha y tipo.\n");
        return;
    }

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
                    if (nuevaCadena != NULL) {
                        free(carpeta->fecha);
                        carpeta->fecha = nuevaCadena;
                        printf("Fecha actualizada correctamente.\n");
                    } else {
                        printf("Error al asignar memoria.\n");
                    }
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

            case 3:
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

            case 0:
                printf("Saliendo de modificación de carpeta.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    }
}

void modificarDenunciaMenu(struct ministerio *ministerio) {
    char ruc[20];
    char rut[20];
    char buffer[300];
    int opcion;
    char *nuevaCadena;
    struct denuncia *denunciaMod;
    struct persona *personaBuscada;

    
    opcion = -1;
    nuevaCadena = NULL;
    denunciaMod = NULL;
    personaBuscada = NULL;

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
        printf("No se encontró una denuncia con el RUC ingresado.\n");
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

void cambiarEstadoCausa(struct ministerio *ministerio, char *rucCausa) {
    int nuevoEstado;
    struct nodoCausas *nodoActual;

    nuevoEstado = 0;
    nodoActual = NULL;

    printf("Ingrese el nuevo estado para la causa (1=Archivada, 2=En progreso, 3=Cerrada, 4=En juicio): ");
    scanf("%d", &nuevoEstado);

    if (nuevoEstado != 1) {
        printf("Entrada invalida.\n");
    }

    if (nuevoEstado < 1 || nuevoEstado > 4) {
        printf("Estado invalido. Los estados validos son del 1 al 4.\n");
        return;
    }

    nodoActual = ministerio->causas;
    if (nodoActual == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    do {
        if (nodoActual->datosCausa != NULL && nodoActual->datosCausa->ruc != NULL &&
            strcmp(nodoActual->datosCausa->ruc, rucCausa) == 0) {

            nodoActual->datosCausa->estadoCausa = nuevoEstado;

            printf("Estado de la causa con RUC %s cambiado a %d.\n", rucCausa, nuevoEstado);
            return;
        }

        nodoActual = nodoActual->siguiente;
    } while (nodoActual != ministerio->causas);

    printf("Causa con RUC %s no encontrada.\n", rucCausa);
}
void modificarImputado(struct ministerio *ministerio, char *rucCausa, char *rutImputado) {
    struct causa *c;
    struct involucrados *imp;
    struct datosImputados *datos;
    int opcion;
    char palabras[300];
    char *nuevaCadena;
    int nueva_medida;
    int nuevo_estado;

    c = NULL;
    imp = NULL;
    datos = NULL;
    opcion = -1;
    nuevaCadena = NULL;
    nueva_medida = 0;
    nuevo_estado = 0;

    if (ministerio == NULL || rucCausa == NULL || rutImputado == NULL) {
        return;
    }

    c = buscarCausaPorRuc(ministerio->causas, rucCausa);
    if (c == NULL) {
        printf("Causa con RUC %s no encontrada.\n", rucCausa);
        return;
    }

    imp = buscarImputadoEnCausa(c, rutImputado);
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

    datos = imp->datosImputados;

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
                do {
                    printf("Ingrese nueva medida cautelar (1 = Prision Preventiva, 2 = Arraigo Nacional, 3 = Firma Periodica, "
                           "4 = Orden de Alejamiento, 5 = Arresto Domiciliario, 6 = Libertad bajo Fianza, 7 = Ninguna): ");
                    scanf("%d", &nueva_medida);
                    getchar();
                    if (nueva_medida < 1 || nueva_medida > 7) {
                        printf("Medida cautelar no valida. Intente nuevamente.\n");
                    }
                } while (nueva_medida < 1 || nu_

void cambiarTipoInvolucrado(struct ministerio *ministerio) {
    char ruc[100];
    char rut[100];
    int nuevoTipo;
    int encontrado;
    int i;
    struct causa *c;
    struct involucrados *inv;

    nuevoTipo = 0;
    encontrado = 0;
    i = 0;
    c = NULL;
    inv = NULL;

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
                inv->datosImputados = (struct datosImputados *) malloc(sizeof(struct datosImputados));
                if (inv->datosImputados == NULL) {
                    printf("Error al asignar memoria para datosImputados.\n");

void modificarPersonaPorRUT(struct ministerio *ministerio) { // Agregue cambiar rut
    char rut[20];
    char palabra[300];
    int opcion = -1;
    struct persona *persona = NULL;
    char *nuevaCadena = NULL;
    int nuevo_rol;

    printf("Ingrese RUT de la persona a modificar: ");
    scanf(" %[^\n]", rut);
    getchar(); // Limpia el salto de línea

    persona = buscarPersonaPorRut(ministerio->personas, rut);
    if (persona == NULL) {
        printf("Persona con RUT %s no encontrada.\n", rut);
        return;
    }

    do {
        printf("\n--- Modificar Persona (%s %s) ---\n", persona->nombre, persona->apellido);
        printf("1. Cambiar nombre\n");
        printf("2. Cambiar apellido\n");
        printf("3. Cambiar contraseña\n");
        printf("4. Cambiar rol (actual: %d)\n", persona->rol);
        printf("5. Cambiar Rut\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");

        scanf("%d", &opcion);
        getchar(); // Limpiar '\n'
        switch (opcion) {
            case 1:
                printf("Nuevo nombre: ");
                if (fgets(palabra, sizeof(palabra), stdin)) {
                    palabra[strcspn(palabra, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabra);
                    if (nuevaCadena != NULL) {
                        free(persona->nombre);
                        persona->nombre = nuevaCadena;
                        printf("Nombre actualizado correctamente.\n");
                    }
                }
                break;

            case 2:
                printf("Nuevo apellido: ");
                if (fgets(palabra, sizeof(palabra), stdin)) {
                    palabra[strcspn(palabra, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabra);
                    if (nuevaCadena != NULL) {
                        free(persona->apellido);
                        persona->apellido = nuevaCadena;
                        printf("Apellido actualizado correctamente.\n");
                    }
                }
                break;

            case 3:
                printf("Nueva contraseña: ");
                if (fgets(palabra, sizeof(palabra), stdin)) {
                    palabra[strcspn(palabra, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabra);
                    if (nuevaCadena != NULL) {
                        free(persona->contrasena);
                        persona->contrasena = nuevaCadena;
                        printf("Contraseña actualizada correctamente.\n");
                    }
                }
                break;

            case 4:
                do {
                    printf("Nuevo rol (1 = usuario común, 2 = fiscal, 3 = juez): ");


                    scanf("%d", &nuevo_rol);
                    getchar();

                    if (nuevo_rol < 1 || nuevo_rol > 3) {
                        printf("Rol inválido. Intente nuevamente.\n");
                    }

                } while (nuevo_rol < 1 || nuevo_rol > 3);

                persona->rol = nuevo_rol;
                printf("Rol actualizado correctamente.\n");

            case 5:
                printf("Nuevo rut: ");
            if (fgets(palabra, sizeof(palabra), stdin)) {
                palabra[strcspn(palabra, "\n")] = '\0';
                nuevaCadena = duplicarCadena(palabra);
                if (nuevaCadena != NULL) {
                    free(persona->rut);
                    persona->rut = nuevaCadena;
                    printf("Rut actualizada correctamente.\n");
                }
            }
            break;
            case 0:
                printf("Modificación finalizada.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 0);
}

void menuModificar(struct ministerio *ministerio) {
    int opcion;
    char ruc[30];
    char rut[30];

    opcion = -1;
    ruc[0] = '\0';
    rut[0] = '\0';

    do {
        printf("\n=========== MENU MODIFICAR ===========\n");
        printf("1. Modificar datos de diligencia\n");
        printf("2. Modificar datos de carpeta\n");
        printf("3. Modificar denuncia\n");
        printf("4. Cambiar estado de causa\n");
        printf("5. Modificar imputado en causa\n");
        printf("6. Cambiar tipo de involucrado\n");
        printf("7. Modificar persona por RUT\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                modificarDatosDiligencia(ministerio);
                break;

            case 2:
                modificarDatosCarpeta(ministerio);
                break;

            case 3:
                modificarDenunciaMenu(ministerio);
                break;

            case 4:
                printf("Ingrese el RUC de la causa para cambiar su estado: \n");
                scanf("%s", ruc);
                getchar();
                cambiarEstadoCausa(ministerio, ruc);
                break;

            case 5:
                printf("Ingrese el RUC de la causa: \n");
                scanf("%s", ruc);
                getchar();

                printf("Ingrese el RUT del imputado: ");
                scanf("%s", rut);
                getchar();

                modificarImputado(ministerio, ruc, rut);
                break;

            case 6:
                cambiarTipoInvolucrado(ministerio);
                break;

            case 7:
                modificarPersonaPorRUT(ministerio);
                break;

            case 0:
                // volver
                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 0);
}

