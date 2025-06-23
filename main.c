#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *task;
  int completed; // 1 -> true, 0 -> false
} Task;

Task *tasks = NULL;
int length = 0;

void addTask(const char *task) {
  tasks = (Task *)realloc(tasks, (length + 1) * sizeof(Task));
  tasks[length].task = (char *)malloc(strlen(task) + 1);
  tasks[length].completed = 0;
  
  strcpy(tasks[length].task, task);

  length++;
  printf("task added\n");
}

void listTasks() {
  char status;

  for (int i = 0; i < length; i++) {
    if (tasks[i].completed == 1) {
      status = 'd';
    } else {
      status = 'n';
    }

    printf("%d. %s [%c]\n", i + 1, tasks[i].task, status);
  }
}

void markCompleted(int index) {
  if (index <= length && index > 0) {
    tasks[index - 1].completed = 1;
    printf("Task marked as completed\n");
  } else {
    printf("Invalid index\n");
  }
}

void deleteTask(int index) {
  if (index <= length && index > 0) {
    index = index - 1;

    free(tasks[index].task);

    for (int i = index; i < length - 1; i++) {
      tasks[i] = tasks[i + 1];
    }

    length--;

    tasks = (Task *)realloc(tasks, length * sizeof(Task));
  } else {
    printf("Invalid index\n");
  }
}

void editTask(int index, const char *task) {
  if (index <= length && index > 0) {
    index = index - 1;

    char *edittedTask = (char *)realloc(tasks[index].task, strlen(task) + 1);

    if (edittedTask != NULL) {
      /**
       * with this I copy memory of edittedTask into tasks[index].task as -
       * If realloc allocates a new block, the old memory is freed, and edittedTask will point
       * to the new memory. By assigning edittedTask back to tasks[index].task:
       * `tasks[index].task = edittedTask;`
       * You ensure that tasks[index].task points to the correct (new) memory location.
       * If you don't update the pointer, tasks[index].task would still point to the old,
       * now-freed memory, which would lead to undefined behavior if accessed.
       */
      tasks[index].task = edittedTask;
      strcpy(tasks[index].task, task); // and this one is for copying the value
      printf("Task updated successfully");
    } else {
      printf("Memory allocation failed");
    }
  } else {
    printf("Invalid index\n");
  }
}

int main() {
  int choice;
  int running = 1;

  int indexInput;
  char taskInput[100];

  printf("\nOptions\n");
  printf("1. Add a task\n");
  printf("2. List all tasks\n");
  printf("3. Mark as completed\n");
  printf("4. Edit task\n");
  printf("5. Delete Task\n");
  printf("6. Exit\n");

  while (running) {
    printf("Enter choice (1, 2, 3, 4, 5, 6): ");
    scanf("%d", &choice);

    switch(choice) {
      case 1:
        printf("Enter task: ");
        getchar();
        fgets(taskInput, sizeof(taskInput), stdin);
        taskInput[strcspn(taskInput, "\n")] = '\0';
        addTask(taskInput);

        break;
      case 2:
        listTasks();

        break;
      case 3:
        printf("Enter index: ");
        scanf("%d", &indexInput);
        markCompleted(indexInput);

        break;
      case 4:
        printf("Enter index: ");
        scanf("%d", &indexInput);

        printf("Enter editted task: ");
        getchar();
        fgets(taskInput, sizeof(taskInput), stdin);
        taskInput[strcspn(taskInput, "\n")] = '\0';

        editTask(indexInput, taskInput);

        break;
      case 5:
          printf("Enter index: ");
          scanf("%d", &indexInput);
          deleteTask(indexInput);

          break;
      case 6:
        printf("Bye");
        running = 0;

        break;
      default:
        printf("Invalid choice\n");
        break;
    }
  }

  free(tasks);

  return 0;
}
