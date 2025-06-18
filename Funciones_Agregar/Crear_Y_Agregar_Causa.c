void crearYagregarCausaNueva(struct ministerio *ministerio, struct denuncia *denunciaAsociada, int estadoCausa) {
    struct causa *nuevaCausa;
    
    if (ministerio == NULL || denunciaAsociada == NULL) {
        printf("Ministerio o denuncia inválida.\n");
        return;
    }

    nuevaCausa = (struct causa *)malloc(sizeof(struct causa));
    if (nuevaCausa == NULL) {
        printf("Error al asignar memoria para la causa.\n");
        return;
    }
    nuevaCausa->ruc = duplicarCadena(denunciaAsociada->ruc);
    if (nuevaCausa->ruc == NULL) {
        printf("Error al duplicar el RUC.\n");
        return;
    }


    nuevaCausa->denuncia = denunciaAsociada;
    nuevaCausa->datosCarpetas = NULL;
    nuevaCausa->involucrados = NULL;
    nuevaCausa->tamInvolucrados = 0;
    nuevaCausa->estadoCausa = estadoCausa;
    nuevaCausa->sentencia = NULL;

    agregarCausa(&ministerio->causas, nuevaCausa);
    printf("Causa agregada correctamente\n");

}
