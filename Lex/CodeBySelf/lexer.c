#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lexical analysis function
int lexer();

int isddigit(char c);

int isletter(char c);

int iskeyword(char str[10]);

void mystrcat(char *token, char c);
typedef struct KeyWord {
  int num;
  char name[10];
} KeyWord;

KeyWord keyword[10] = {
    {3, "int"}, {4, "if"},   {5, "else"},  {6, "while"},
    {7, "for"}, {8, "read"}, {9, "write"},
};

int isddigit(char c) {
  if (c >= '0' && c <= '9')
    return 1;
  else
    return 0;
}

int isletter(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    return 1;
  else
    return 0;
}

int iskeyword(char str[10]) {
  for (int i = 0; i <= 6; i++) {
    if (strcmp(str, keyword[i].name) == 0) {
      return keyword[i].num;
    }
  }
  return 0;
}

void mystrcat(char *token, char c) {
  int len = strlen(token);
  token[len] = c;
  token[len + 1] = '\0';
}

int lexer() {
  char token[100] = "";
  char ch = '\0';

  // read one character and avoid reading useless character.
  ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') {
    ch = getchar();
  }

  // branch judgement
  switch (ch) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
    while (isddigit(ch) || isletter(ch)) {
      mystrcat(token, ch);
      ch = getchar();
    }
    ungetc(ch, stdin);
    // get token done

    int judge = iskeyword(token);
    if (judge >= 3 && judge <= 9)
      printf("( %d , - )\n", judge); // keyword
    else
      printf("( 1 , %s )\n", token); // identifier
    break;

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    while (isddigit(ch)) {
      mystrcat(token, ch);
      ch = getchar();
    }
    ungetc(ch, stdin);
    printf("( 2 , %s )\n", token); // constant
    break;

  case '+':
    printf("( 10 , - )\n"); // +
    break;

  case '-':
    printf("( 11 , - )\n"); // -
    break;

  case '*':
    printf("( 12 , - )\n"); // *
    break;

  case '/':
    printf("( 13 , - )\n"); // /
    break;

  case '<':
    mystrcat(token, ch);
    ch = getchar();
    if (ch == '=')

      printf("( 15 , - )\n"); // <=
    else {
      ungetc(ch, stdin);
      printf("( 14 , - )\n"); // <
    }
    break;

  case '>':
    mystrcat(token, ch);
    ch = getchar();
    if (ch == '=')

      printf("( 17 , - )\n"); // >=
    else {
      ungetc(ch, stdin);
      printf("( 16 , - )\n"); // >
    }
    break;

  case '!':
    mystrcat(token, ch);
    ch = getchar();
    if (ch == '=')
      printf("( 18 , - )\n"); // !
    else {
      ungetc(ch, stdin);
      printf("ERROR: expected '=' after '!' token.\n");
    }
    break;

  case '=':
    mystrcat(token, ch);
    ch = getchar();
    if (ch == '=')
      printf("( 19 , - )\n"); // ==
    else {
      ungetc(ch, stdin);
      printf("( 20 , - )\n"); // =
    }
    break;

  case '(':
    printf("( 21 , - )\n"); // (
    break;

  case ')':
    printf("( 22 , - )\n"); // )
    break;

  case ',':
    printf("( 23 , - )\n"); // ,
    break;

  case ';':
    printf("( 24 , - )\n"); // ;
    break;
  case '"':
    printf("( 25 , - )\n"); // "
    break;
  case '{':
    printf("( 26 , - )\n"); // {
    break;
  case '}':
    printf("( 27 , - )\n"); // }
    break;
  case EOF:
    return 0;
  default:
    printf("ERROR:\"%c\"\n", ch);
    break;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("ERROR: Please input 1 file. Usage: %s input_file.\n", argv[0]);
    exit(1);
  }

  if (freopen(argv[1], "r", stdin) == NULL) {
    printf("ERROR: Can't open file \"%s\".\n", argv[1]);
    exit(1);
  }

  while (1) {
    if (!lexer())
      break;
  }

  return 0;
}