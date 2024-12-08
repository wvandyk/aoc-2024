uint8_t *get_file_content(const char *filename) {
    size_t fsize = 0;
    FILE *f = fopen(filename, "rb");

    if(f) {
        if(fseek(f, 0, SEEK_END) == 0) {
            fsize = ftell(f);
            fseek(f, 0, SEEK_SET);
        } else {
            perror("ERROR\n");
            return NULL;
        }
    } else {
        perror("ERROR\n");
        return NULL;
    }

    uint8_t *buffer = (uint8_t *)malloc(fsize);
    if(buffer != NULL && fsize > 0) {
        fread(buffer, 1, fsize, f);
        fclose(f);
    } else {
        perror("ERROR\n");
        fclose(f);
        return NULL;
    }
    return buffer;
}