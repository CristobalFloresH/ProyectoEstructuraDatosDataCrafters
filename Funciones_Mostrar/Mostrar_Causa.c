void mostrarDenunciaDeCausa(struct causa *causaActual) {
    if (causaActual == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causaActual->denuncia == NULL) {
        printf("Esta causa no tiene denuncias asociadas.\n");
        return;
    }

    struct denuncia *denuncia = causaActual->denuncia;
    printf("========================================\n");
    printf("DENUNCIA EN LA CAUSA RUC: %s\n", causaActual->ruc);
    printf("========================================\n");
    printf("RUC           : %s\n", denuncia->ruc);
    printf("Fecha         : %s\n", denuncia->fecha);
    printf("Descripcion   : %s\n", denuncia->descripcion);
    printf("Delito        : %s\n", denuncia->tipoDeDenuncia);
    if (denuncia->denunciante != NULL && denuncia->denunciado != NULL)
    {
        printf("Denunciante   : %s %s (RUT: %s)\n", denuncia->denunciante->nombre,
               denuncia->denunciante->apellido, denuncia->denunciante->rut);
        printf("Denunciado    : %s %s (RUT: %s)\n", denuncia->denunciado->nombre,
               denuncia->denunciado->apellido, denuncia->denunciado->rut);
    }
    else if (denuncia->denunciante == NULL && denuncia->denunciado != NULL)
    {
        printf("Denunciante   : Anonimo\n");
        printf("Denunciado    : %s %s (RUT: %s)\n", denuncia->denunciado->nombre,
                 denuncia->denunciado->apellido, denuncia->denunciado->rut);
    }
    else if (denuncia->denunciante != NULL && denuncia->denunciado == NULL)
    {
        printf("Denunciante   : %s %s (RUT: %s)\n", denuncia->denunciante->nombre,
                 denuncia->denunciante->apellido, denuncia->denunciante->rut);
        printf("Denunciado    : Contra los que resulten culpables\n");
    }
}

void mostrarTodoDatoDeCausaPorRuc(struct nodoCausas *causas, char *rucBuscado) {
    if (causas == NULL)
    {
        printf("No hay causas registradas en el sistema.\n");
        return;
    }
    if (rucBuscado == NULL)
    {
        printf("Ruc ingresado invalido.\n");
        return;
    }

    //se busca a la carpeta indicada
    struct causa *causaBuscada = buscarCausaPorRuc(causas, rucBuscado);

    //si no se encuentra o algun dato es invalido, retorna mensaje de error
    if (causaBuscada == NULL)
    {
        printf("Se genero un error al buscar la causa o esta no existe\n");
        return;
    }

    printf("\n========================================\n");
    printf("Causa con Ruc: %s\n", causaBuscada->ruc);
    printf("========================================\n");

    // Seccion de denuncias
    printf("\n>> DENUNCIA REGISTRADA:\n");
    mostrarDenunciaDeCausa(causaBuscada);

    // Seccion de involucrados
    printf("\n>> INVOLUCRADOS:\n");
    mostrarTodosInvolucradosCausa(causaBuscada);

    // Seccion de datos de la carpeta
    printf("\n>> DATOS CARPETA INVESTIGATIVA:\n");
    mostrarTodosDatosCarpetaCausa(causaBuscada);

    printf("========================================\n\n");
}

void mostrarTodasLasCausas(struct nodoCausas *causas)
{
    struct nodoCausas *actual = causas;
    do
    {
        mostrarTodoDatoDeCausaPorRuc(causas, actual->datosCausa->ruc);
        printf("\n"); // Separador visual
        actual = actual->siguiente;
    } while (actual != causas);
}
