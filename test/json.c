#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(void) {

    zpl_file_t file;
    zpl_file_open(&file, "../data/test.json5");
    isize file_size = zpl_file_size(&file);
    char *content = (char *)zpl_malloc(file_size+1);
    zpl_file_read(&file, content, file_size);
    content[file_size] = 0;
    zpl_file_close(&file);


    zpl_json_object root = {0};

    u8 err;
    zpl_json_parse(&root, file_size, content, zpl_heap_allocator(), true, &err);

    zpl_printf("Error code: %d\n", err);

    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);

    zpl_json_free(&root);

    zpl_mfree(content);
    return 0;
}
