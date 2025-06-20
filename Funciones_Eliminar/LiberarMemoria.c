void liberarPersona(struct persona *persona) {
    if (persona == NULL)
        return;

    free(persona->nombre);
    free(persona->apellido);
    free(persona->rut);
    free(persona->contrasena);

    free(persona);
}
void liberarDenuncia(struct denuncia *denuncia) {
    if (denuncia == NULL)
        return;

    free(denuncia->fecha);
    free(denuncia->descripcion);
    free(denuncia->ruc);
    free(denuncia->tipoDeDenuncia);

    free(denuncia);
}
void liberarDatosImputados(struct datosImputados *datos) {
    if (datos == NULL)
        return;

    free(datos->declaracion);
    free(datos->fechaInicioMedida);
    free(datos->fechaFinMedida);

    free(datos);
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
    free(degligencias->fechaFin);
    free(degligencias->descripcion);
    free(degligencias->estado);
    free(degligencias->tipoDiligencia);

    free(degligencias);
}
void liberarDatosCarpeta(struct datosCarpeta *datosCarpeta) {
    if (datosCarpeta == NULL)
        return;

    free(datosCarpeta->fecha);
    free(datosCarpeta->descripcion);

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
}
void liberarCausa(struct causa *causa) {
    struct nodoDatosCarpetas *actual;
    struct nodoDatosCarpetas *sig;

    if (causa == NULL)
        return;

    free(causa->ruc);

    if (causa->sentencia != NULL)
        free(causa->sentencia);

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
