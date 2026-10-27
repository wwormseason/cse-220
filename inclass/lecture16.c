#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NAME_LEN 50
#define DATA_FILE "students.txt"

typedef struct
{
  int id;
  char name[NAME_LEN];
  float gpa;
  enum
  {
    Undergraduate = 1,
    Graduate = 2
  } Year;
  union
  {
    int year;            // only used for undergrads
    int researchCredits; // only used for grads
    // union instead of struct to save space, only one variable needed for any new student
  } Info;
} Student;

typedef struct
{
  Student data;      // data
  struct Node *next; // pointer
} Node;

int main()
{
  Node *head = NULL;
  int choice;

  for (;;)
  {
    printf("Student Records\n");
    printf("1. Add Student\n");
    printf("2. Display all Students\n");
    printf("3. Search by ID\n");
    printf("4. Delete by ID\n");
    printf("5\n");
    printf("6\n");
    printf("0");

    if (!read_int("Choose an option: ", &choice))
    {
      puts("\nInput ended.");
      break;
    }
  }
}