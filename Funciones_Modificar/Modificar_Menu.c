void menuModificar(struct ministerio *ministerio) {
    int opcion;
    char ruc[30];
    char rut[30];

    do {
        printf("\n=========== MENU MODIFICAR ===========\n");
        printf("1. Modificar datos de diligencia\n");
        printf("2. Modificar datos de carpeta\n");
        printf("3. Modificar denuncia\n");
        printf("4. Cambiar estado de causa\n");
        printf("5. Modificar imputado en causa\n");
        printf("6. Cambiar tipo de involucrado\n");
        printf("7. Modificar persona por RUT\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                modificarDatosDiligencia(ministerio);
                break;

            case 2:
                modificarDatosCarpeta(ministerio);
                break;

            case 3:
                modificarDenunciaMenu(ministerio);
                break;

            case 4:
                printf("Ingrese el RUC de la causa para cambiar su estado: \n");
                scanf("%s", ruc);
                getchar();
                cambiarEstadoCausa(ministerio, ruc);

                break;

            case 5:
                printf("Ingrese el RUC de la causa: \n");
                scanf("%s", ruc);
                getchar();

                printf("Ingrese el RUT del imputado: ");
                scanf("%s", rut);
                getchar();

                modificarImputado(ministerio, ruc, rut);

                break;

            case 6:
                cambiarTipoInvolucrado(ministerio);
                break;

            case 7:
                modificarPersonaPorRUT(ministerio);
                break;

            case 0:
                //volvemos
                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 0);
}
