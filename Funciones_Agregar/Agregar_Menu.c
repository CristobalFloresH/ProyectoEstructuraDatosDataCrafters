void menuAgregar(struct ministerio *ministerio){
    int opcion;
    struct persona *nuevaPersona;
    char palabra[100];
    int rol;
    char contrasenaIngresada[100];

    while(1){
        printf("\n=========== MENU AGREGAR ===========\n");
        printf("Opcion 1: Agregar persona\n");
        printf("Opcion 2: Agregar denuncia\n");
        printf("Opcion 3: Agregar carpeta investigativa\n");
        printf("Opcion 4: Agregar causa\n");
        printf("Opcion 5: Agregar involucrados\n");
        printf("Opcion 0: Volver.\n");
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        /*El fiscal tendra que elegir la opcion a agregar, ya sea una persona, denuncia, carpeta investigativa*/

        if(opcion == 0){
            //menuPrincipal(struct ministerio *ministerio);
            break;
        }
        else if (opcion == 1) {
        /*Opcion 1 agregar persona*/
            agregarPersonaMenu(ministerio);  
            break;
        }

        else if(opcion == 2){
        /*Opcion 2 agregar denuncia */
            agregarDenunciaMenu(ministerio);
            break;
        }

        else if(opcion == 3){
        /*Opcion 3 agregar carpeta*/
            agregarCarpetaMenu(ministerio);
            break;
        }
        else if (opcion == 4) { 
            agregarCausaMenu(ministerio);
            break;
        }

        else if(opcion == 5){
            agregarInvolucradoMenu(ministerio);
            break;
        }
    }
    else{
        printf("Opcion invalida, intente nuevamente.\n");
    }
}

