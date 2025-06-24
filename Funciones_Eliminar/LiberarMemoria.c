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
