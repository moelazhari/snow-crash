int main(int argc, char **argv) {
    char *token = argv[1];

    for(int i = 0; *token; token++, i++) {
        printf("%c", *token - i);
    }
    printf("\n");
    return 0;
}
