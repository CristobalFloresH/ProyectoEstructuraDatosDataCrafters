struct datosDiligencias* buscarDiligencia(struct ministerio *ministerio, char *ruc, char *fechaInicio, char *tipoDiligencia) {
    struct causa *c;
    struct datosCarpeta *carpeta;
    struct datosDiligencias *d;
    
    if (ministerio == NULL || ruc == NULL || fechaInicio == NULL || tipoDiligencia == NULL) {
        printf("Parámetros inválidos.\n");
        return NULL;
    }

    // Buscar causa por RUC
    c = buscarCausaPorRuc(ministerio->causas, ruc);
    if (c == NULL) {
        printf("No se encontró la causa con RUC: %s\n", ruc);
        return NULL;
    }

    // Acceder a la carpeta única de la causa
    if (c->datosCarpetas == NULL || c->datosCarpetas->datosCarpeta == NULL) {
        printf("La causa no tiene carpeta válida.\n");
        return NULL;
    }

    carpeta = c->datosCarpetas->datosCarpeta;

    if (carpeta->tipoDeDato == 3 && carpeta->datosDiligencias != NULL) {
        d = carpeta->datosDiligencias;
        if (strcmp(d->fechaInicio, fechaInicio) == 0 && strcmp(d->tipoDiligencia, tipoDiligencia) == 0) {
            return d;
        }
    }

    printf("No se encontró una diligencia que coincida con fecha de inicio '%s' y tipo '%s'.\n", fechaInicio, tipoDiligencia);
    return NULL;
}
