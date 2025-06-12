void mostrarDenunciaPorRut(struct nodoPersonasABB *personas, char *rutBuscado) {
    if (personas == NULL) {
        printf("No hay personas registradas en el sistema.\n");
        return;
    }
    if (rutBuscado == NULL) {
        printf("Por favor, ingrese un RUT valido para buscar denuncias.\n");
        return;
    }

    //se busca a la persona indicada
    struct persona *personaBuscada = buscarPersonaPorRut(personas, rutBuscado);

    //si no se encuentra o algun dato es invalido, retorna mensaje de error
    if (personaBuscada == NULL)
    {
        printf("No se encontro ningun usuario con el RUT ingresado.\n\n");
        return;
    }

    if (personaBuscada->denuncias == NULL)
    {
        printf("Este usuario no tiene denuncias asociadas.\n");
        return;
    }
    struct nodoDenuncias *actual = personaBuscada->denuncias;
    int contadorDenuncias = 0;

    printf("\n========================================\n");
    printf("Denuncias de %s %s | Rut: %s\n", personaBuscada->nombre, personaBuscada->apellido, personaBuscada->rut);
    printf("========================================\n");

    while (actual != NULL)
    {
        if (actual->datosDenuncia != NULL)
        {
            contadorDenuncias++;
            printf("\n--------- DENUNCIA %d ---------\n", contadorDenuncias);
            printf("RUC           : %s\n", actual->datosDenuncia->ruc);
            printf("Fecha         : %s\n", actual->datosDenuncia->fecha);
            printf("Descripcion   : %s\n", actual->datosDenuncia->descripcion);
            printf("Tipo de delito: %s\n", actual->datosDenuncia->tipoDeDenuncia);

            //Si el rut del denunciante es el mismo de la persona buscada significa que la persona envio esta denuncia
            if (strcmp(actual->datosDenuncia->denunciante->rut, personaBuscada->rut) == 0) {
                printf("Denuncia Enviada a %s %s\n", actual->datosDenuncia->denunciado->nombre,
                    actual->datosDenuncia->denunciado->apellido);
            }
            //si el rut del denunciado es el mismo de la persona buscada significa que la persona recibio esta denuncia
            if (strcmp(actual->datosDenuncia->denunciado->rut, personaBuscada->rut) == 0) {
                printf("Denuncia Recibida por %s %s\n", actual->datosDenuncia->denunciante->nombre,
                    actual->datosDenuncia->denunciante->apellido);
            }
        }
        actual = actual->siguiente;
    }
}

void mostrarTodasLasDenunciasDePersonas(struct nodoPersonasABB *arbolPersonas)
{
    if (arbolPersonas == NULL)
    {
        return;
    }

    mostrarTodasLasDenunciasDePersonas(arbolPersonas->izquierda);
    mostrarDenunciaPorRut(arbolPersonas, arbolPersonas->datosPersona->rut); // Mostrar denuncias de este usuario
    printf("\n"); // Separador visual
    mostrarTodasLasDenunciasDePersonas(arbolPersonas->derecha);
}
