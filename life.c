#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/curses.h>

#define BLACK_1x1 L' '
#define WHITE_BLACK_1x1 L'\u2580'
#define BLACK_WHITE_1x1 L'\u2584'
#define WHITE_1x1 L'\u2588'

struct state {
    char old:4;
    char new:4;
} __attribute__((packed));

char *status = NULL;

volatile sig_atomic_t signal_status = 0;

void signal_handler(int signal)
{
  signal_status = signal;
}

struct state *board_init(int columns, int lines)
{
    struct state *board = (struct state *)calloc(columns * lines, sizeof(struct state));

    // random live cells
    srand(time(NULL));
    int cells = rand() % columns*lines;
    for (int i = 0; i < cells; ++i) {
        int x = rand() % columns;
        int y = rand() % lines;
        board[x * lines + y].old = TRUE;
    }

    return board;
}

int neighbors(struct state board[], int x, int y, int columns, int lines)
{
    int live = 0;

    for (int i = -1; i <= +1; ++i) {
        for (int j = -1; j <= +1; ++j) {
            if ((i == 0) && (j == 0))
                continue;
            live += board[((x + i + columns) % columns) * lines + ((y + j + lines) % lines)].old;
        }
    }

    return live;
}

void evolve(struct state *board, int columns, int lines)
{
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < lines; ++j) {
            int n = neighbors(board, i, j, columns, lines);
            int new = FALSE;

            // live
            if (board[i * lines + j].old == TRUE) {
                // live cell < two live neighbors dies (underpopulation or exposure)
                if (n < 2)
                    new = FALSE;
                // live cell == two or three live neighbors lives
                else if ((n == 2 || n == 3))
                    new = TRUE;
                // live cell > three live neighbors dies (overpopulation or overcrowding)
                else if (n > 3)
                    new = FALSE;
            }
            // dead
            else if (board[i * lines + j].old == FALSE) {
                // dead cell == three live neighbors come to life
                if (n == 3)
                    new = TRUE;
            }

            board[i * lines + j].new = new;
        }
    }
}

void save(struct state *board, int columns, int lines)
{
    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < lines; ++j)
            board[i * lines + j].old = board[i * lines + j].new;
}

void display(struct state *board, int columns, int lines)
{
    wclear(stdscr);
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < lines/2; ++j) {
            wchar_t wstr[] = { 0, L'\0' };
            int top = board[i * lines + (j * 2)].new;
            int bottom = board[i * lines + (j * 2 + 1)].new;
            if ((top == TRUE) && (bottom == TRUE)) {
                wstr[0] = WHITE_1x1;
            } else if ((top == TRUE) && (bottom == FALSE))  {
                wstr[0] = WHITE_BLACK_1x1;
            } else if ((top == FALSE) && (bottom == TRUE))  {
                wstr[0] = BLACK_WHITE_1x1;
            } else {
                wstr[0] = BLACK_1x1;
            }
            mvaddwstr(j, i, wstr);
        }
    }
    mvprintw(LINES-1, 0, status);
    wrefresh(stdscr);
}

int main()
{
    signal(SIGINT, signal_handler);

    setlocale(LC_CTYPE, "");
    initscr();
    cbreak();
    timeout(100);
    keypad(stdscr, TRUE);

    int columns = COLS;
    int lines = LINES*2;

    status = realloc(status, columns);
    sprintf(status, "COLS %d LINES %d", columns, lines);

    struct state *board = board_init(columns, lines);

    while (signal_status != SIGINT) {
        int ch = wgetch(stdscr); // ERR on timeout

        if (ch == KEY_RESIZE) {
            free(board);
            columns = COLS;
            lines = LINES*2;
            board = board_init(columns, lines);
            status = realloc(status, columns);
            sprintf(status, "COLS %d LINES %d", columns, lines);
        }

        evolve(board, columns, lines);

        save(board, columns, lines);

        display(board, columns, lines);
    }

    endwin();

    free(board);

    return 0;
}
