#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct Segment {
  int x;
  int y;
};

void spawn_apple(struct Segment *snake, int snake_len,
                 int *apple_x, int *apple_y,
                 int width, int height) {
    int occupied;

    do {
        occupied = 0;

        *apple_y = 1 + rand() % (height - 2);
        *apple_x = 1 + rand() % (width - 2);

        for (int g = 0; g < snake_len; g++) {
            if (snake[g].x == *apple_x &&
                snake[g].y == *apple_y) {
                occupied = 1;
                break;
            }
        }
    } while (occupied);
}

void move_right(struct Segment *snake, int snake_len) {
    for (int i = snake_len - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0].x++;
}

void move_left(struct Segment *snake, int snake_len) {
    for (int i = snake_len - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0].x--;
}

void move_up(struct Segment *snake, int snake_len) {
    for (int i = snake_len - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0].y--;
}

void move_down(struct Segment *snake, int snake_len) {
    for (int i = snake_len - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0].y++;
}

int main() {
  struct Segment tail;
  char direction = 'a';
  char input;
  int snake_len = 1;
  int apple_y, apple_x;
  srand(time(0));
  struct Segment *snake = malloc(snake_len*sizeof(struct Segment));
  snake[0].y = 3;
  snake[0].x = 7;
  char pole[7][15];
  int height = 7;
  int width = 15;
  int p = 0;
  int h;
  spawn_apple(snake, snake_len, &apple_x, &apple_y, width, height);
  while (1) {
    tail = snake[snake_len - 1];
    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        if ( y == 0 || y == height - 1|| x == 0 || x == width - 1) {
        pole[y][x] = '#';
        }
        else {
            pole[y][x] = ' ';
        }
      }
    }
    for(int i = 0; i < snake_len; i++) {
      pole[snake[i].y][snake[i].x] = '@';
    }
    pole[apple_y][apple_x] = '0';
    for(int y = 0; y < height; y++) {
     for(int x = 0; x < width; x++) {
       printf("%c", pole[y][x]);
      }
      printf("\n");
    }
    scanf(" %c", &input);;
    if (input == 'w') {
      direction = 'w';
    }
    else if(input == 'a') {
      direction = 'a';
    }
    else if(input == 's') {
      direction = 's';
    }
    else if(input == 'd') {
      direction = 'd';
    }
    if (direction == 'w') {
      move_up(snake, snake_len);
    }
    else if(direction == 'a') {
      move_left(snake, snake_len);;
    }
    else if(direction == 's') {
      move_down(snake, snake_len);
    }
    else if(direction == 'd') {
      move_right(snake, snake_len);;
    }
    if (snake[0].x == apple_x && snake[0].y == apple_y) {
        snake_len++;
        struct Segment* tmp = realloc(snake, snake_len * sizeof(struct Segment));
        snake = tmp;
        snake[snake_len - 1] = tail;
        spawn_apple(snake, snake_len, &apple_x, &apple_y, width, height);
     }
    for (int n = 1; n < snake_len; n++) {
        if (snake[0].y == snake[n].y && snake[0].x == snake[n].x) {
            snake[0].y = 0;
        }
    }
    if ( snake[0].x <= 0 || snake[0].y <= 0 || snake[0].x >= width - 1 || snake[0].y >= height - 1) {
        printf("Game over!\n");
        break;
    }
    system("clear");
  }
  free(snake);
  return 0;
 }
