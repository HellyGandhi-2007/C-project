#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 16

int N;
int board[MAX][MAX];
int solution[MAX][MAX];
int SRN;

// Print board
void printBoard() {
    printf("\nBoard:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0)
                printf(". ");
            else
                printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Check validity
int isValid(int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num) return 0;
        if (board[x][col] == num) return 0;
    }

    int startRow = row - row % SRN;
    int startCol = col - col % SRN;

    for (int i = 0; i < SRN; i++)
        for (int j = 0; j < SRN; j++)
            if (board[startRow + i][startCol + j] == num)
                return 0;

    return 1;
}

// Shuffle numbers
void shuffle(int *arr) {
    for (int i = 0; i < N; i++) {
        int j = rand() % N;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Backtracking generator
int fillGrid(int row, int col) {
    if (row == N)
        return 1;

    if (col == N)
        return fillGrid(row + 1, 0);

    int nums[MAX];
    for (int i = 0; i < N; i++)
        nums[i] = i + 1;

    shuffle(nums);

    for (int i = 0; i < N; i++) {
        int num = nums[i];

        if (isValid(row, col, num)) {
            board[row][col] = num;

            if (fillGrid(row, col + 1))
                return 1;

            board[row][col] = 0;
        }
    }

    return 0;
}

// Remove digits
void removeDigits(int count) {
    while (count > 0) {
        int r = rand() % N;
        int c = rand() % N;

        if (board[r][c] != 0) {
            board[r][c] = 0;
            count--;
        }
    }
}

// Generate Sudoku
void generateSudoku() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    fillGrid(0, 0);

    // Save solution
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            solution[i][j] = board[i][j];

    removeDigits(N * N / 2);
}

// Check completion
int isComplete() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == 0)
                return 0;
    return 1;
}

int main() {
    int r, c, n;

    srand(time(0));

    printf("Enter size (4 or 9): ");
    scanf("%d", &N);

    SRN = sqrt(N);

    if (SRN * SRN != N) {
        printf("Invalid size! Must be perfect square.\n");
        return 0;
    }

    generateSudoku();

    while (1) {
        printBoard();

        // 🎉 Completion check
        if (isComplete()) {
            printf("\n🎉 Congratulations! You solved the Sudoku!\n");
            printf("Enter -1 for new game or 0 to exit.\n");
        }

        printf("\nEnter row col num (1-%d) or -1 new or -2 solution or 0 exit: ", N);
        scanf("%d", &r);

        // 🚪 Exit
        if (r == 0) {
            printf("\n👋 Thanks for playing Sudoku!\n");
            break;
        }

        // 🔁 New game
        if (r == -1) {
            generateSudoku();
            continue;
        }

        // 🧠 Show solution
        if (r == -2) {
            printf("\nSolution:\n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++)
                    printf("%d ", solution[i][j]);
                printf("\n");
            }
            continue;
        }

        scanf("%d %d", &c, &n);

        r--; 
        c--;

        if (r >= 0 && r < N && c >= 0 && c < N &&
            board[r][c] == 0 && n >= 1 && n <= N) {

            if (isValid(r, c, n))
                board[r][c] = n;
            else
                printf("❌ Invalid move! Violates Sudoku rules.\n");

        } else {
            printf("❌ Wrong input!\n");
        }
    }

    return 0;
}