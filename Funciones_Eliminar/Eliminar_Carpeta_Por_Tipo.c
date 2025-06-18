int eliminarDatoDeCarpetaPorTipo(struct nodoCausas **listaCausas, char *ruc, int tipoDeDato) {
    struct nodoCausas *causa = buscarNodoCausa(*listaCausas, ruc);
    struct nodoDatosCarpetas *carpeta = causa->datosCausa->datosCarpetas;
    struct nodoDatosCarpetas *aEliminar = carpeta;

    if (listaCausas == NULL || *listaCausas == NULL) { // Comprobamos existencia de causa.
        return 0;
    }

    char palabra[100];
    if (causa == NULL) {
        printf("No se encontró una causa con ese RUC.\n");
        return 0;
    }

    while (carpeta != NULL) {
        if (carpeta->datosCarpeta != NULL && carpeta->datosCarpeta->tipoDeDato == tipoDeDato) {
            carpeta = carpeta->siguiente; // Guardamos siguiente antes de eliminar

            // Reenlazamos para sacar nodo de la lista doble
            reenlazarDatosCarpeta(&(causa->datosCausa->datosCarpetas), aEliminar);

            // Liberamos según tipo
            switch (tipoDeDato) {
                case 1: // declaraciones
                    printf("Ingrese RUT del que declara.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                if (aEliminar != NULL && aEliminar->datosCarpeta->datosPersona->rut != NULL && strcmp(aEliminar->datosCarpeta->datosPersona->rut, palabra) == 0 ) {
                        free(aEliminar->datosCarpeta->fecha);
                        aEliminar->datosCarpeta->fecha = NULL;
                        free(aEliminar->datosCarpeta->descripcion);
                        aEliminar->datosCarpeta->descripcion = NULL;
                        free(aEliminar->datosCarpeta->datosPersona);
                        aEliminar->datosCarpeta->datosPersona=NULL;
                    }
                    break;

                case 2: // pruebas
                    printf("Ingrese Prueba que desea eliminar.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    if (aEliminar != NULL && aEliminar->datosCarpeta->descripcion != NULL && strcmp(aEliminar->datosCarpeta->descripcion, palabra) == 0 ) {
                        free(aEliminar->datosCarpeta->descripcion);
                        aEliminar->datosCarpeta->descripcion = NULL;
                        free(aEliminar->datosCarpeta->fecha);
                        aEliminar->datosCarpeta->fecha = NULL;
                    }
                    break;

                case 3: // diligencias
                    printf("Ingrese descripcion de diligencia a eliminar.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    if (aEliminar != NULL && aEliminar->datosCarpeta->datosDiligencias != NULL && strcmp(aEliminar->datosCarpeta->datosDiligencias->descripcion, palabra) == 0) {
                        liberarDatosDiligencias(aEliminar->datosCarpeta->datosDiligencias);
                        aEliminar->datosCarpeta->datosDiligencias = NULL;
                    }
                    break;

                case 4: // denuncia
                    printf("Ingrese RUC de la denuncia extra a eliminar.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    if (aEliminar != NULL && aEliminar->datosCarpeta->datosDenuncia != NULL && strcmp(aEliminar->datosCarpeta->datosDenuncia->ruc, palabra) == 0) {
                        liberarDenuncia(aEliminar->datosCarpeta->datosDenuncia);
                        aEliminar->datosCarpeta->datosDenuncia = NULL;
                    }
                    break;

                default:
                    return 0;
            }

            free(aEliminar->datosCarpeta);
            aEliminar->datosCarpeta = NULL;

            free(aEliminar);
            aEliminar = NULL;
            
            return 1; // Salimos tras eliminar la primera coincidencia
        }
        else {
            carpeta = carpeta->siguiente;
        }
    }
    return 0;
}
