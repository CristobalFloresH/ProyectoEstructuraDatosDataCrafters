void cambiarEstadoCausa(struct ministerio *ministerio, char *rucCausa) {
    int nuevoEstado;
    struct nodoCausas *nodoActual;

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
