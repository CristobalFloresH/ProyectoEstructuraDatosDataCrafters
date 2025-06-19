void agregarDenunciaMenu(struct ministerio *ministerio){
    char rutDenunciante[20];
    char rutDenunciado[20];
    char palabra[100];
    struct persona *nuevoDenunciante;
    struct persona *nuevoDenunciado;
    struct denuncia *nuevaDenuncia;

    printf("Ingrese RUT del denunciante\n");
    scanf(" %[^\n]", rutDenunciante);

    printf("Ingrese RUT del denunciado\n");
    scanf(" %[^\n]", rutDenunciado);


    nuevoDenunciante = buscarPersonaPorRut(ministerio->personas, rutDenunciante);
    nuevoDenunciado = buscarPersonaPorRut(ministerio->personas, rutDenunciado);
    /*Se pregunta y lee los ruts de denunciante y denunciado para asi copiar esta informacion en 2 strcut personas */

    if(nuevoDenunciante == NULL || nuevoDenunciado == NULL){
        printf("Denunciante y denunciado no encontrados, intente con un RUT valido\n");
        return;
    }

    nuevaDenuncia = (struct denuncia *)malloc(sizeof(struct denuncia));

    if(nuevaDenuncia == NULL){
        printf("Error al asignar memoria");
        return;
    }
    /*Se corrobora que exita denunciante y denunciado para luego asignar memoria a la nueva denuncia (tambien se corrobora que se asigne correctamente la memoria)*/

    nuevaDenuncia->denunciante = nuevoDenunciante;
    nuevaDenuncia->denunciado = nuevoDenunciado;

    printf("Ingrese la fecha actual: \n");
    scanf(" %[^\n]", palabra);

    nuevaDenuncia->fecha = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaDenuncia->fecha, palabra);

    printf("Ingrese descripcion de la denuncia: \n");
    scanf(" %[^\n]", palabra);

    nuevaDenuncia->descripcion = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaDenuncia->descripcion, palabra);

    printf("Ingrese RUC de la denuncia: \n");
    scanf(" %[^\n]", palabra);

    nuevaDenuncia->ruc = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaDenuncia->ruc, palabra);

    printf("Ingrese el tipo de denuncia: \n");
    scanf(" %[^\n]", palabra);

    nuevaDenuncia->tipoDeDenuncia = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaDenuncia->tipoDeDenuncia, palabra);
    /*Se le asigna la informacion a la denuncia como la fecha, quien es el denunciante y el denunciado entre otros*/

    agregarDenunciaAPersona(rutDenunciante, ministerio->personas, nuevaDenuncia);
    agregarDenunciaAPersona(rutDenunciado, ministerio->personas, nuevaDenuncia);
    printf("Denuncia agregada correctamente. \n");    
}
