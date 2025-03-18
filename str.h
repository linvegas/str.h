#ifdef STR_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define STR_INIT_CAP 16

#define str(s) str_from(s, sizeof(s)-1)

typedef struct Str {
    char  *data;
    size_t len;
    size_t cap;
} Str;

Str    str_from(const char *text, size_t len);
Str    str_from_file(const char *file_path);

void   str_insert(Str *s, char c, size_t idx);
void   str_push(Str *s, char c);
void   str_delete(Str *s, size_t idx);
void   str_concat(Str *s, const char *text);

size_t str_len(const char *text);
void   str_info(Str s);
void   str_check_cap(Str *s);
void   str_free(Str *s);
void   str_clear(Str *s);

Str str_from(const char *text, size_t len)
{
    Str s = {0};

    for (size_t i = 0; i < len; i++)
        str_push(&s, text[i]);

    return s;
}

Str str_from_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    assert(file != NULL);

    fseek(file, 0L, SEEK_END);
    long int file_len = ftell(file);

    rewind(file);

    char *buffer = calloc((size_t)file_len+1, sizeof(char));
    assert(buffer != NULL);

    size_t buffer_len = fread(buffer, 1, (size_t)file_len ,file);
    buffer[buffer_len] = '\0';

    Str s = str_from(buffer, buffer_len-1);

    free(buffer);
    fclose(file);

    return s;
}

void str_insert(Str *s, char c, size_t idx)
{
    assert(idx <= s->len);

    str_check_cap(s);

    if (idx != s->len) {
        // A simplified version of memmove
        for (size_t i = s->len; i > idx; i--)
            s->data[i] = s->data[i-1];
    }

    s->data[idx] = c;
    s->len += 1;
}

void str_push(Str *s, char c)
{
    str_insert(s, c, s->len);
}

void str_delete(Str *s, size_t idx)
{
    assert(idx < s->len && idx > 0);

    for (size_t i = idx; i < s->len; i++)
        s->data[i] = s->data[i+1];

    s->len -= 1;
}

void str_concat(Str *s, const char *text)
{
    size_t len = str_len(text);

    for (size_t i = 0; i < len; i++)
        str_push(s, text[i]);
}

size_t str_len(const char *text)
{
    size_t len = 0;

    while (*text) len += 1, *(text++);

    return len;
}

void str_info(Str s)
{
    printf("data     = [");
    for (size_t i = 0; i < s.len; i++) {
        printf("%c", s.data[i]);
    }
    printf("]\n");
    printf("length   = %lu\n", s.len);
    printf("capacity = %lu\n", s.cap);
}

void str_check_cap(Str *s)
{
    if (s->len >= s->cap) {
        s->cap = s->cap == 0 ? STR_INIT_CAP : s->cap * 2;
        s->data = realloc(s->data, s->cap * sizeof(*s->data));
        assert(s->data != NULL);
    }
}

void str_free(Str *s)
{
    free(s->data);
}

void str_clear(Str *s)
{
    str_free(s);
    s->len = 0;
}

#endif // STR_IMPLEMENTATION

// vim:ft=c
