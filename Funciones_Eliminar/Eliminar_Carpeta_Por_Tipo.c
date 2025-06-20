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
