int main(){

    struct ministerio *ministerio = malloc(sizeof(struct ministerio));
    ministerio->personas = NULL;
    ministerio->causas = NULL;

    ingresarAlSistema(ministerio);
    menuPrincipal(ministerio);

    return 0;
}
