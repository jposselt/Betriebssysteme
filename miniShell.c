// Compile gcc -o minishell miniShell.c

// Includes
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Zeile einlesen
char *readLine(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // getline alloziert Buffer
  getline(&line, &bufsize, stdin);
  return line;
}

// Parsen der Argumente
/*
char **parseLine(char *line)
{
  
}
*/

// Kommando ausführen
/*
int runCommand(char **args)
{
  
}
*/

// Prompt anzeigen
void printPrompt(void)
{
  printf("%s:%s$ ", getlogin(), getcwd(0,0));
}

// Hauptschleif zur Kommandoausführung
void shellLoop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printPrompt();
    line = readLine();

    // ...

    free(line);
    free(args);  
  } while (status);
}

// Main
int main( int argc, const char* argv[] )
{

  // Hauptschleife
  shellLoop();
  
  return EXIT_SUCCESS;
}
