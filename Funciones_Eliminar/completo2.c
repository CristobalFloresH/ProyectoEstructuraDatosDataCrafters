
void reenlazarCausas(struct nodoCausas **listaCausas, struct nodoCausas *nodoEliminar) {
    if (*listaCausas == NULL || nodoEliminar == NULL) return;

    // Si solo hay un nodo en la lista
    if (nodoEliminar->siguiente == nodoEliminar && nodoEliminar->anterior == nodoEliminar) {
        *listaCausas = NULL;
        return;
    }

    // Enlazamos
    nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;
    nodoEliminar->siguiente->anterior = nodoEliminar->anterior;

    // Si el nodo a eliminar es el nodo apuntado por lista (inicio), movemos el puntero
    if (*listaCausas == nodoEliminar) {
        *listaCausas = nodoEliminar->siguiente;
    }
}
void reenlazarDenuncias(struct nodoDenuncias **listaDenuncias, struct nodoDenuncias *nodoEliminar) {
    if (listaDenuncias == NULL || *listaDenuncias == NULL) return;

    if (nodoEliminar->anterior == NULL && nodoEliminar->siguiente == NULL) {
        *listaDenuncias = NULL;
        return;
    }

    if (*listaDenuncias == nodoEliminar) {
        *listaDenuncias = nodoEliminar->siguiente;
    }

    if (nodoEliminar->anterior != NULL)
        nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;

    if (nodoEliminar->siguiente != NULL)
        nodoEliminar->siguiente->anterior = nodoEliminar->anterior;
}

void reenlazarDatosCarpeta(struct nodoDatosCarpetas **listaCarpetas, struct nodoDatosCarpetas *nodoEliminar) {
    if (*listaCarpetas == NULL || nodoEliminar == NULL) return;

    if (*listaCarpetas == nodoEliminar) {
        *listaCarpetas = nodoEliminar->siguiente;
        if (*listaCarpetas != NULL) {
            (*listaCarpetas)->anterior = NULL;
        }
    } else {
        if (nodoEliminar->anterior != NULL) {
            nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;
        }
        if (nodoEliminar->siguiente != NULL) {
            nodoEliminar->siguiente->anterior = nodoEliminar->anterior;
        }
    }
}
void liberarPersona(struct persona *persona) {
    if (persona == NULL)
        return;

    free(persona->nombre);
    persona->nombre = NULL;
    free(persona->apellido);
    persona->apellido = NULL;
    free(persona->rut);
    persona->rut = NULL;
    free(persona->contrasena);
    persona->contrasena = NULL;

    free(persona);
    persona = NULL;
}
void liberarDenuncia(struct denuncia *denuncia) {
    if (denuncia == NULL)
        return;

    free(denuncia->fecha);
    denuncia->fecha = NULL;
    free(denuncia->descripcion);
    denuncia->descripcion = NULL;
    free(denuncia->ruc);
    denuncia->ruc = NULL;
    free(denuncia->tipoDeDenuncia);
    denuncia->tipoDeDenuncia = NULL;

    free(denuncia);
    denuncia = NULL;
}
void liberarDatosImputados(struct datosImputados *datos) {
    if (datos == NULL)
        return;

    free(datos->declaracion);
    datos->declaracion = NULL;
    free(datos->fechaInicioMedida);
    datos->fechaInicioMedida = NULL;
    free(datos->fechaFinMedida);
    datos->fechaFinMedida = NULL;

    free(datos);
    datos = NULL;
}
void liberarInvolucrados(struct involucrados **involucrados, int tam) {
    int i;

    if (involucrados == NULL)
        return;

    for (i = 0; i < tam; i++) {
        if (involucrados[i] != NULL) {
            if (involucrados[i]->datosImputados != NULL) {
                liberarDatosImputados(involucrados[i]->datosImputados);
                involucrados[i]->datosImputados = NULL;
            }
            // No liberamos persona, asumiendo que es compartida
            free(involucrados[i]);
            involucrados[i] = NULL;
        }
    }

    free(involucrados);
}
void liberarDatosDiligencias(struct datosDiligencias *degligencias) {
    if (degligencias == NULL)
        return;

    free(degligencias->fechaInicio);
    degligencias->fechaInicio = NULL;
    free(degligencias->fechaFin);
    degligencias->fechaFin = NULL;
    free(degligencias->descripcion);
    degligencias->descripcion = NULL;
    free(degligencias->estado);
    degligencias->estado = NULL;
    free(degligencias->tipoDiligencia);
    degligencias->tipoDiligencia = NULL;

    free(degligencias);
    degligencias = NULL;
}
void liberarDatosCarpeta(struct datosCarpeta *datosCarpeta) {
    if (datosCarpeta == NULL)
        return;

    free(datosCarpeta->fecha);
    datosCarpeta->fecha = NULL;
    free(datosCarpeta->descripcion);
    datosCarpeta->descripcion = NULL;

    if (datosCarpeta->datosDiligencias != NULL) {
        liberarDatosDiligencias(datosCarpeta->datosDiligencias);
        datosCarpeta->datosDiligencias = NULL;
    }

    if (datosCarpeta->datosDenuncia != NULL) {
        liberarDenuncia(datosCarpeta->datosDenuncia);
        datosCarpeta->datosDenuncia = NULL;
    }

    if (datosCarpeta->datosPersona != NULL) {
        liberarPersona(datosCarpeta->datosPersona);
        datosCarpeta->datosPersona = NULL;
    }

    free(datosCarpeta);
    datosCarpeta = NULL;
}
void liberarCausa(struct causa *causa) {
    struct nodoDatosCarpetas *actual;
    struct nodoDatosCarpetas *sig;

    if (causa == NULL)
        return;

    free(causa->ruc);
    causa->ruc = NULL;

    if (causa->sentencia != NULL){
        free(causa->sentencia);
        causa->sentencia = NULL;
    }

    if (causa->denuncia != NULL) {
        liberarDenuncia(causa->denuncia);
        causa->denuncia = NULL;
    }

    actual = causa->datosCarpetas;
    if (actual != NULL) {
        while (actual != NULL) {
            sig = actual->siguiente;
            if (actual->datosCarpeta != NULL) {
                liberarDatosCarpeta(actual->datosCarpeta);
                actual->datosCarpeta = NULL;
            }
            free(actual);
            actual = sig;
        }
    }

    causa->datosCarpetas = NULL;

    if (causa->involucrados != NULL) {
        liberarInvolucrados(causa->involucrados, causa->tamInvolucrados);
        causa->involucrados = NULL;
    }

    free(causa);
}


int eliminarCausa(struct nodoCausas **listaCausa, char *ruc) {
    struct nodoCausas *aEliminar;

    if (listaCausa == NULL || *listaCausa == NULL) {
        return 0;
    }

    aEliminar = buscarNodoCausa(*listaCausa, ruc);
    if (aEliminar == NULL) {
        return 0;
    }

    if (aEliminar != NULL) {
        reenlazarCausas(listaCausa, aEliminar);
        liberarCausa(aEliminar->datosCausa);
        free(aEliminar);
        aEliminar = NULL;
        return 1;
    }
    return 0;
}
int eliminarDenuncia(struct nodoDenuncias **listaDenuncia, char *ruc) {
    struct nodoDenuncias *actual;

    if (listaDenuncia == NULL || *listaDenuncia == NULL) {
        return 0;
    }

    actual = *listaDenuncia;

    while (actual != NULL) {
        if (strcmp(actual->datosDenuncia->ruc, ruc) == 0) {
            reenlazarDenuncias(listaDenuncia, actual);
            liberarDenuncia(actual->datosDenuncia);
            free(actual);
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

void compactarInvolucrados(struct involucrados **involucrados, int *tam) {
    int i, j = 0;

    if (involucrados == NULL || tam == NULL || *tam == 0)
        return;

    for (i = 0; i < *tam; i++) {
        if (involucrados[i] != NULL) {
            if (i != j) {
                involucrados[j] = involucrados[i];
                involucrados[i] = NULL;
            }
            j++;
        }
    }
    *tam = j;
}

int eliminarInvolucradoPorRut(struct involucrados **involucrados, int tam, char *rut) {
    struct involucrados *involucrado;
    int i;
    involucrado = buscarInvolucradoPorRut(involucrados, tam, rut);
    if (involucrado == NULL) {
        return 0;
    }

    if (involucrado->tipoInvolucrado == 2 && involucrado->datosImputados != NULL) {
        liberarDatosImputados(involucrado->datosImputados);
        involucrado->datosImputados = NULL;
    }
    involucrado->persona = NULL;

    for (i = 0; i < tam && involucrados[i] != NULL; i++) {
  		if(involucrados[i]->persona->rut ==  NULL){
          free(involucrados[i]);
          involucrados[i] = NULL;
          compactarInvolucrados(involucrados, &tam);
        }

        if (involucrados[i] == involucrado) {
            free(involucrados[i]);
            involucrados[i] = NULL;
            compactarInvolucrados(involucrados, &tam);
            return 1;
        }
    }
    return 0;
}

int eliminarInvolucrado(struct nodoCausas **listaCausas, char *ruc, char *rut) {
    struct nodoCausas *actual;
    struct nodoCausas *inicio;

    if (listaCausas == NULL || *listaCausas == NULL) {
        return 0;
    }

    actual = *listaCausas;
    inicio = *listaCausas;

    do {
        if (actual->datosCausa != NULL && strcmp(actual->datosCausa->ruc, ruc) == 0 && actual->datosCausa->involucrados != NULL) {

            return eliminarInvolucradoPorRut(actual->datosCausa->involucrados, actual->datosCausa->tamInvolucrados, rut);
        }

        actual = actual->siguiente;
    } while (actual != inicio);

    return 0;
}
struct nodoPersonasABB* minimo(struct nodoPersonasABB *arbol) {
    while (arbol != NULL && arbol->izquierda != NULL)
        arbol = arbol->izquierda;
    return arbol;
}
int eliminarPersona(struct nodoPersonasABB **personas, char *rut) {
    int comparar;
    struct nodoPersonasABB *nodoEliminar;
    struct nodoPersonasABB *minNodo;
    struct persona *aux;

    if (personas == NULL || *personas == NULL) {
        return 0;
    }

    comparar = strcmp(rut, (*personas)->datosPersona->rut);

    if (comparar < 0) {
        return eliminarPersona(&((*personas)->izquierda), rut);
    } else if (comparar > 0) {
        return eliminarPersona(&((*personas)->derecha), rut);
    } else {
        nodoEliminar = *personas;

        if (nodoEliminar->izquierda == NULL) {
            *personas = nodoEliminar->derecha;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);

        } else if (nodoEliminar->derecha == NULL) {
            *personas = nodoEliminar->izquierda;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);

        } else {
            minNodo = minimo(nodoEliminar->derecha);
            aux = nodoEliminar->datosPersona;
            nodoEliminar->datosPersona = minNodo->datosPersona;
            minNodo->datosPersona = aux;
            return eliminarPersona(&(nodoEliminar->derecha), aux->rut);
        }
    }
    return 1;
}
int eliminarCarpetaDeCausa(struct nodoCausas **listaCausas, char *ruc) {
    struct nodoCausas *causa;
    struct nodoDatosCarpetas *actualCarpeta;
    struct nodoDatosCarpetas *sig;

    if (listaCausas == NULL || *listaCausas == NULL) {
        return 0;
    }

    causa = buscarNodoCausa(*listaCausas, ruc);
    if (causa == NULL) {
        return 0;
    }

    actualCarpeta = causa->datosCausa->datosCarpetas;
    while (actualCarpeta != NULL) {
        sig = actualCarpeta->siguiente;
        liberarDatosCarpeta(actualCarpeta->datosCarpeta);
        free(actualCarpeta);
        actualCarpeta = sig;
    }
    causa->datosCausa->datosCarpetas = NULL;
    return 1;
}
void eliminarDatoDeCarpetaPorTipo(struct nodoCausas **listaCausas, char *ruc, int tipoDeDato) {
    struct nodoCausas *causa;
    struct nodoDatosCarpetas *carpeta;
    struct nodoDatosCarpetas *aEliminar;
    char palabra[100];
    int coincide;

    // Verificar si la lista es válida
    if (listaCausas == NULL || *listaCausas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    causa = buscarNodoCausa(*listaCausas, ruc);
    if (causa == NULL) {
        printf("No se encontró una causa con ese RUC.\n");
        return;
    }

    carpeta = causa->datosCausa->datosCarpetas;

    while (carpeta != NULL) {
        if (carpeta->datosCarpeta != NULL && carpeta->datosCarpeta->tipoDeDato == tipoDeDato) {
            aEliminar = carpeta;
            carpeta = carpeta->siguiente; // Avanzar antes de modificar

            coincide = 0;

            switch (tipoDeDato) {
                case 1: // Declaraciones
                    printf("Ingrese RUT del que declara:\n");
                    scanf(" %[^\n]", palabra);
                    (void)getchar();
                    if (aEliminar->datosCarpeta->datosPersona != NULL && strcmp(aEliminar->datosCarpeta->datosPersona->rut, palabra) == 0) {
                        free(aEliminar->datosCarpeta->fecha);
                        aEliminar->datosCarpeta->fecha = NULL;

                        free(aEliminar->datosCarpeta->descripcion);
                        aEliminar->datosCarpeta->descripcion = NULL;

                        free(aEliminar->datosCarpeta->datosPersona);
                        aEliminar->datosCarpeta->datosPersona = NULL;

                        coincide = 1;
                    }
                    break;

                case 2: // Pruebas
                    printf("Ingrese descripción de la prueba a eliminar:\n");
                    scanf(" %[^\n]", palabra);
                    (void)getchar();
                    if (aEliminar->datosCarpeta->descripcion != NULL && strcmp(aEliminar->datosCarpeta->descripcion, palabra) == 0) {
                        free(aEliminar->datosCarpeta->descripcion);
                        aEliminar->datosCarpeta->descripcion = NULL;

                        free(aEliminar->datosCarpeta->fecha);
                        aEliminar->datosCarpeta->fecha = NULL;

                        coincide = 1;
                    }
                    break;

                case 3: // Diligencias
                    printf("Ingrese descripción de la diligencia a eliminar:\n");
                    scanf(" %[^\n]", palabra);
                    (void)getchar();
                    if (aEliminar->datosCarpeta->datosDiligencias != NULL && strcmp(aEliminar->datosCarpeta->datosDiligencias->descripcion, palabra) == 0) {
                        liberarDatosDiligencias(aEliminar->datosCarpeta->datosDiligencias);
                        aEliminar->datosCarpeta->datosDiligencias = NULL;
                        coincide = 1;
                    }
                    break;

                case 4: // Denuncia
                    printf("Ingrese RUC de la denuncia extra a eliminar:\n");
                    scanf(" %[^\n]", palabra);
                    (void)getchar();
                    if (aEliminar->datosCarpeta->datosDenuncia != NULL && strcmp(aEliminar->datosCarpeta->datosDenuncia->ruc, palabra) == 0) {
                        liberarDenuncia(aEliminar->datosCarpeta->datosDenuncia);
                        aEliminar->datosCarpeta->datosDenuncia = NULL;
                        coincide = 1;
                    }
                    break;

                default:
                    printf("Tipo de dato no válido.\n");
                    return;
            }

            if (coincide) {
                reenlazarDatosCarpeta(&(causa->datosCausa->datosCarpetas), aEliminar);
                free(aEliminar->datosCarpeta);
                aEliminar->datosCarpeta = NULL;
                free(aEliminar);
                aEliminar = NULL;

                printf("Dato eliminado correctamente.\n");
                return;
            } else {
                printf("No se encontró coincidencia con los datos ingresados.\n");
                return;
            }
        } else {
            carpeta = carpeta->siguiente;
        }
    }

    printf("No se encontraron datos del tipo especificado en carpetas.\n");
}

void menuEliminarCarpeta(struct ministerio *ministerio) {
    int opcion = -1, exito;
    char ruc[30];

    while (opcion != 0) {
        printf("\n=========== MENU ELIMINAR DATOS CARPETA ===========\n");
        printf("1. Eliminar Carpeta Completa.\n");
        printf("2. Eliminar Declaraciones.\n");
        printf("3. Eliminar Pruebas.\n");
        printf("4. Eliminar Diligencias.\n");
        printf("5. Eliminar Denuncias.\n");
        printf("0  Volver.\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese RUC de carpeta a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            exito = eliminarCarpetaDeCausa(&(ministerio->causas), ruc);
            if (exito == 0)
                printf("No se pudo eliminar la carpeta.\n");
            else
                printf("Carpeta eliminada con exito. \n");
            break;

            case 2:
                printf("Ingrese RUC de declaracion a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 1);
            break;

            case 3:
                printf("Ingrese RUC de prueba a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 2);
            break;

            case 4:
                printf("Ingrese RUC de diligencia a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 3);
            break;

            case 5:
                printf("Ingrese RUC de denuncia a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 4);
            break;

            case 0:
                return;

            default:
                printf("Opcion no valida\n");
            break;
        }
    }
}

void menuEliminarCausa(struct ministerio *ministerio) {
    int opcion = -1, exito;
    char rut[30];
    char ruc[30];
    struct nodoCausas *encontrado;

    if (ministerio == NULL) {
        printf("Ministerio no inicializado.\n");
        return;
    }

    while (opcion != 0) {
        printf("\n=========== MENU ELIMINAR CAUSA ===========\n");
        printf("1. Eliminar Causa\n");
        printf("2. Eliminar Carpeta\n");
        printf("3. Eliminar Involucrado\n");
        printf("4. Eliminar Sentencia\n");
        printf("0. Volver.\n");
        printf("Ingrese opcion:");
        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese RUC de la causa a eliminar:\n");
                scanf("%s", ruc);
                (void)getchar();
                exito = eliminarCausa(&(ministerio->causas), ruc);
                if (exito == 0)
                    printf("No se pudo eliminar causa.\n");
                else
                    printf("Causa eliminada exitosamente.\n");

                break;

            case 2:
                menuEliminarCarpeta(ministerio);
                break;

            case 3:
                printf("Ingrese RUC de la causa y RUT del involucrado a eliminar.\n");
                scanf("%s", ruc);
                (void)getchar();
                scanf("%s", rut);
                (void)getchar();
                exito = eliminarInvolucrado(&(ministerio->causas), ruc, rut);
                if (exito == 0)
                    printf("No se pudo eliminar el involucrado.\n");
                else
                    printf("Involucrado eliminado exitosamente.\n");
                break;

            case 4:
                printf("Ingrese RUC de la sentencia a eliminar:\n");
                scanf("%s", ruc);
                (void)getchar();
                encontrado = buscarNodoCausa(ministerio->causas, ruc);
                if (encontrado != NULL && encontrado->datosCausa != NULL && encontrado->datosCausa->sentencia != NULL) {
                    free(encontrado->datosCausa->sentencia);
                    encontrado->datosCausa->sentencia = NULL;
                    printf("Sentencia eliminada correctamente.\n");
                } else {
                    printf("No se encontro sentencia para eliminar.\n");
                }
                break;

            case 0:
                return;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}
