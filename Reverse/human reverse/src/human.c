#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 27

int state = 0;

// Проверяем, что до { стоят символы NMARK. Если да, меняем состояние на 1
int unlock(char *password) {
    if (!strncmp(password, "NMARK", 5)) {
        puts("Correct password! Stage 1/4 unlocked!");
        state = 1;
        return 0;
    }
    puts("Incorrect password! Ya obidelas!");
    exit(1);
}

// Проверяем, что первая команда - "HaNd3". Если да, меняет состояние на 2
int hand(char *command) {
    if (!strncmp(command, "HaNd3", 5)) {
        puts("Stage 2/4 unclocked!");
        state = 2;
        return 0;
    }
    
    puts("Incorrect command for stage 2/4! Ya obidelas!");
    exit(1);
}

// Проверяет, что вторая команда - LeG4. Но сравнивает первый символ переданной команды с последним символом correct и тд. То есть с разных концов. Если всё правильно, меняет состояние на 3.
int leg(char *command) {
    char *correct = "4GeL";

    for (int i = 3; i >= 0; --i) {
        if (command[i] != correct[4 - i - 1]) {
            puts("Incorrect command for stage 3/4! Ya obidelas!");
            exit(1);
        }
    }

    state = 3;
    puts("Stage 3/4 unlocked!");
    return 0;
}

// Проверяет, что переданная команда - "StOMAcH52". Проверяет сначала чётные символы, затем нечётные. Если всё правильно, меняет состояние на 4.
int stomach(char *command) { // StOMAcH52
    char *correct1 = "SOAH2";
    for (int i = 0; i < 5; ++i) {
        if (correct1[i] != command[2 * i]) {
            puts("Incorrect command for stage 4/4! Ya obidelas!");
            exit(1);
        }
    }

    char *correct2 = "tMc5";
    for (int i = 0; i < 4; ++i) {
        if (correct2[i] != command[2 * i + 1]) {
            puts("Incorrect command for stage 4/4! Ya obidelas!");
            exit(1);
        }
    }

    state = 4;
    puts("Stage 4/4 unlocked!");
    return 0;
}

int brain(char *command) {
    if (strlen(command) == 5 && state == 0) { // NMARK
        unlock(command);
        return 0;
    }

    if (strlen(command) == 5 && state == 1) { // HaNd3
        hand(command);
        return 0;
    }

    if (strlen(command) == 4 && state == 2) { // LeG4
        leg(command);
        return 0;
    }

    if (strlen(command) == 9 && state == 3) { // StOMAcH52
        stomach(command);
        return 0;
    }

    return 0;
}

int main() {
    puts("Hi, programmer! I'm a girl-reverser. I don't want to do anything, but you can reverse me and get the flag you need.");

    // Читаем переменную окружения с командой
    char *command = getenv("HUMAN_COMMAND");
    if (command == NULL) {
        puts("No command! Ya obidelas!");
        return 1;
    }
    printf("Your command: %s\n", command);

    // Проверяем длину команды
    if (strlen(command) != LEN) {
        puts("Incorrecct length! Ya obidelas!");
        return 1;
    }

    // Узнаём адрес {
    char *open_brace = strchr(command, '{');
    if (open_brace == NULL) {
        puts("Incorrect format of command! Ya obidelas!");
        return 1;
    }

    // Считаем длину подстроки до { и выделяем память под неё
    size_t pass_len = open_brace - command;
    char *pass = malloc(pass_len + 1);
    if (pass == NULL) {
        puts("Internal error! Ya obidelas!");
        return 1;
    } 

    // Копируем подстроку - пароль - из команды в отдельное место.
    strncpy(pass, command, pass_len);
    pass[pass_len] = '\0';

    // Передаём пароль в мозг. Если правильный, состояние поменяется на 1.
    brain(pass);
    if (state == 0) {
        free(pass);
        return 1;
    }

    // Адрес }
    char *close_brace = strchr(command, '}');
    if (close_brace == NULL) {
        puts("Incorrect format! Ya obidelas!");
        return 1;
    }

    // Длина строки между фигурными скобками
    int com_len = close_brace - open_brace;

    char *commands = malloc(com_len);
    if (commands == NULL) {
        puts("Internal error! Ya obidelas!");
        free(pass);
        return 1;
    }

    // Копируем содержимое между фигурными скобками в commands
    memcpy(commands, open_brace + 1, com_len - 1);
    commands[com_len] = '\0';

    char *words[3];
    int count = 0;

    // Между фигурными скобками должно быть 3 команды, разделённых запятыми. Складываем каждую команду в массив words
    char *token = strtok(commands, ","); // Вместо первой запятой ставит \0 и возвращает указатель на начало первой команды
    while (token != NULL && count < 3) {
        // Убрать пробелы в начале
        while (*token == ' ') {
            token++;
        }

        // Убрать пробелы в конце
        char *end = token + strlen(token) - 1;
        while (end > token && *end == ' ') {
            *end = '\0';
            end--;
        }

        words[count] = token;
        count++;

        token = strtok(NULL, ","); // Вместо следующей запятой ставит \0 и возвращает указатель начало следующей команды
    }

    if (count != 3) {
        printf("Expected 3 commands, found %d\n", count);
        free(commands);
        return 1;
    }

    // Выводим найденные слова
    printf("\nFound %d commands:\n", count);
    for (int i = 0; i < count; i++) {
        printf("Command %d: '%s'\n", i + 1, words[i]);
    }

    // Передаём каждую команду в brain()
    for (int i = 0; i < count; i++) {
        printf("Processing command %d: '%s'\n", i + 1, words[i]);
        brain(words[i]);
    }

    // brain() должен изменить состояние на 4
    if (state != 4) {
        puts("Incorrect command!");
        return 1;
    }

    puts("Girl-reverser unlocked. Now you can reverse-engineer BombombiniGusini");
    free(commands);
    free(pass);

    return 0;
}