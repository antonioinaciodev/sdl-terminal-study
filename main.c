#include <stdio.h>
#include <unistd.h>
#include <pty.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>

#include <SDL3/SDL.h>

extern char* environ[];

int main(void) {
    int master;
    int slave;
    openpty(&master, &slave, NULL, NULL, NULL);

    pid_t pid = fork();
    if (pid == 0) {
        login_tty(slave);


        char* path = "/usr/bin/bash";
        char* argv[] = { path, NULL };
        execve(path, argv, environ);
    }

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_Window* window = SDL_CreateWindow("Terminal", 800, 600, 0);
    SDL_Renderer* rend = SDL_CreateRenderer(window, NULL);
    SDL_Event event;
    SDL_StartTextInput(window);
    for (;;) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                return 0;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE)
                    return 0;
                if (event.key.key == SDLK_RETURN)
                    write(master, "\n", 1);
            }

            if (event.type == SDL_EVENT_TEXT_INPUT)
                write(master, event.text.text, strlen(event.text.text));
        }

        char buffer[1024 * 1024];
        fcntl(master, F_SETFL, O_NONBLOCK);
        int n = read(master, buffer, 1024 * 1024);

        if (n > 0) {
        FILE* f = fopen("terminal.txt", "a");
        fwrite(buffer, 1, n, f);
        fclose(f);
        }
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return 0;
}