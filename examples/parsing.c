#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern size_t read_line(FILE *file, char **line);

typedef enum Category {
    OBJECT, DESCRIPTION, TYPE
} Category;

Category next_category(const Category category)
{
    return (Category) ((category + 1) % 3);
}

int main(void)
{
    char *object[3];
    char *description[3];
    char *type[3];
    size_t counter = 0;

    FILE *file = fopen("example.csv", "r");
    char *line = NULL;
    size_t length = 0;
    while ((length = read_line(file, &line)) > 0 && counter < sizeof(object)) {
        Category token_category = 0;
        char *next_token = strtok(line, ";");
        while (next_token != NULL) {
            size_t token_length = strlen(next_token);
            switch (token_category) {
                case OBJECT:
                    object[counter] = calloc(token_length, sizeof(char));
                    memcpy(object[counter], next_token, token_length);
                    break;
                case DESCRIPTION:
                    description[counter] = calloc(token_length, sizeof(char));
                    memcpy(description[counter], next_token, token_length);
                    break;
                case TYPE:
                    type[counter] = calloc(token_length, sizeof(char));
                    memcpy(type[counter], next_token, token_length);
                    break;
            }
            // Read the next token from the same string
            next_token = strtok(NULL, ";");
            token_category = next_category(token_category);
        }
        free(next_token);
        free(line);
        ++counter;
    }
    fclose(file);
    printf("Objects:      %s, %s, %s\n", object[0], object[1], object[2]);
    printf("Descriptions: %s, %s, %s\n", description[0], description[1], description[2]);
    printf("Types:        %s, %s, %s\n", type[0], type[1], type[2]);
    return 0;
}
