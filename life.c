#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

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

struct state *board_init()
{
    struct state *board = (struct state *)calloc(COLS * LINES, sizeof(struct state));

    // random live cells
    srand(time(NULL));
    int cells = rand() % COLS*LINES;
    for (int i = 0; i < cells; ++i) {
        int x = rand() % COLS;
        int y = rand() % LINES;
        board[x * LINES + y].old = TRUE;
    }

    return board;
}

int neighbors(struct state board[], int x, int y)
{
    int live = 0;

    for (int i = -1; i <= +1; ++i) {
        for (int j = -1; j <= +1; ++j) {
            if ((i == 0) && (j == 0))
                continue;
            live += board[((x + i + COLS) % COLS) * LINES + ((y + j + LINES) % LINES)].old;
        }
    }

    return live;
}

void evolve(struct state *board)
{
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < LINES; ++j) {
            int n = neighbors(board, i, j);
            int new = FALSE;

            // live
            if (board[i * LINES + j].old == TRUE) {
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
            else if (board[i * LINES + j].old == FALSE) {
                // dead cell == three live neighbors come to life
                if (n == 3)
                    new = TRUE;
            }

            board[i * LINES + j].new = new;
        }
    }
}

void save(struct state *board)
{
    for (int i = 0; i < COLS; ++i)
        for (int j = 0; j < LINES; ++j)
            board[i * LINES + j].old = board[i * LINES + j].new;
}

void display(struct state *board)
{
    wclear(stdscr);
    for (int i = 0; i < COLS; ++i)
        for (int j = 0; j < LINES; ++j)
            if (board[i * LINES + j].new == TRUE)
                mvwaddch(stdscr, j, i, ACS_DIAMOND); // ' '|A_REVERSE);
    mvprintw(LINES-1, 0, status);
    wrefresh(stdscr);
}

int main()
{
    signal(SIGINT, signal_handler);

    initscr();
    cbreak();
    timeout(100);
    keypad(stdscr, TRUE);

    status = realloc(status, COLS);
    sprintf(status, "COLS %d LINES %d", COLS, LINES);

    struct state *board = board_init(NULL);

    while (signal_status != SIGINT) {
        int ch = wgetch(stdscr); // ERR on timeout

        if (ch == KEY_RESIZE) {
            free(board);
            board = board_init();
            status = realloc(status, COLS);
            sprintf(status, "COLS %d LINES %d", COLS, LINES);
        }

        evolve(board);

        save(board);

        display(board);
    }

    endwin();

    free(board);

    return 0;
}
