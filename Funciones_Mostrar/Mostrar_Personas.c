void mostrarUsuarioPorRut(struct nodoPersonasABB *personas, char *rutBuscado) {
    //se busca a la persona indicada
    if (personas == NULL) {
        printf("No hay personas registradas en el sistema.\n");
        return;
    }
    if (rutBuscado == NULL) {
        printf("Por favor, ingrese un RUT valido para buscar.\n");
        return;
    }

    struct persona *personaBuscada = buscarPersonaPorRut(personas, rutBuscado);

    //si no se encuentra o algun dato es invalido, retorna mensaje de error
    if (personaBuscada == NULL)
    {
        printf("No se encontro ningun usuario con el RUT ingresado.\n");
        return;
    }

    //si se encuentra y no es null (paso el if anterior), muestra los datos de la persona
    printf("\n--- INFORMACION DE PERSONA ---\n");
    printf("Nombre      : %s\n", personaBuscada->nombre);
    printf("Apellido    : %s\n", personaBuscada->apellido);
    printf("Rut         : %s\n", personaBuscada->rut);

    /** 1 = usuario comun, 2 = fiscal, 3 = juez**/
    if (personaBuscada->rol == 1)
        printf("Rol         : Usuario Comun\n");
    else if(personaBuscada->rol == 2)
        printf("Rol         : Fiscal\n");
    else if(personaBuscada->rol == 3)
        printf("Rol         : Juez\n");
}

void mostrarTodosLosUsuarios(struct nodoPersonasABB *arbolPersonas)
{
    if (arbolPersonas == NULL)
        return;
    mostrarTodosLosUsuarios(arbolPersonas->izquierda);
    mostrarUsuarioPorRut(arbolPersonas, arbolPersonas->datosPersona->rut); // Mostrar usuario actual
    printf("\n"); // Separador visual
    mostrarTodosLosUsuarios(arbolPersonas->derecha);
}
