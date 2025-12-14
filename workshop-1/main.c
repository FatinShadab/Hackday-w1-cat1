#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define DAILY_LIMIT 5
#define LAZINESS_THRESHOLD 2

typedef struct {
    int priority;
    char tag[50];
    char name[100];
    char category[20];  // "Ready", "25%", "50%", "75%", "100%"
    char startTime[20];
    char endTime[20];
    int hourlyUpdateCount;
    char history[5][20]; // Track category updates for progress flow
    int historyCount;
} Task;

Task tasks[MAX_TASKS];
int taskCount = 0;
int todayTaskCount = 0;

// Utility to display all tasks
void listTasks() {
    printf("\n--- Current Tasks ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s | Priority: %d | Category: %s\n", 
            i + 1, tasks[i].name, tasks[i].priority, tasks[i].category);
    }
    if(taskCount == 0) printf("No tasks available.\n");
}

// Add a new task
void addTask() {
    if (todayTaskCount >= DAILY_LIMIT) {
        printf("Warning: Daily task limit reached!\n");
        return;
    }

    Task t;
    printf("Enter task name: ");
    scanf(" %[^\n]", t.name);
    printf("Enter priority (integer): ");
    scanf("%d", &t.priority);
    printf("Enter tag: ");
    scanf(" %[^\n]", t.tag);
    strcpy(t.category, "Ready");
    printf("Enter start time (string or timestamp): ");
    scanf(" %[^\n]", t.startTime);
    printf("Enter end time (string or timestamp): ");
    scanf(" %[^\n]", t.endTime);
    printf("Enter hourly update count: ");
    scanf("%d", &t.hourlyUpdateCount);

    // Initialize history
    strcpy(t.history[0], t.category);
    t.historyCount = 1;

    tasks[taskCount++] = t;
    todayTaskCount++;

    printf("Task added successfully!\n");
}

// Update task progress
void updateProgress() {
    listTasks();
    if(taskCount == 0) return;

    int idx;
    printf("Enter task number to update progress: ");
    scanf("%d", &idx);
    idx--; // array index

    if(idx < 0 || idx >= taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    Task *t = &tasks[idx];
    if(strcmp(t->category, "Ready") == 0) strcpy(t->category, "25%");
    else if(strcmp(t->category, "25%") == 0) strcpy(t->category, "50%");
    else if(strcmp(t->category, "50%") == 0) strcpy(t->category, "75%");
    else if(strcmp(t->category, "75%") == 0) strcpy(t->category, "100%");
    else {
        printf("Task is already 100%% complete.\n");
        return;
    }

    strcpy(t->history[t->historyCount++], t->category);
    printf("Task progress updated to %s\n", t->category);
}

// View progress flow for a completed task
void viewProgressFlow() {
    listTasks();
    if(taskCount == 0) return;

    int idx;
    printf("Enter task number to view progress flow: ");
    scanf("%d", &idx);
    idx--;

    if(idx < 0 || idx >= taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    Task *t = &tasks[idx];
    if(strcmp(t->category, "100%") != 0) {
        printf("Task is not yet 100%% complete.\n");
        return;
    }

    printf("Progress flow for task '%s': ", t->name);
    for(int i = 0; i < t->historyCount; i++) {
        printf("%s", t->history[i]);
        if(i != t->historyCount - 1) printf(" -> ");
    }
    printf("\n");
}

// Check distraction/laziness indicator
void checkDistraction() {
    listTasks();
    if(taskCount == 0) return;

    int idx;
    printf("Enter task number to check distraction: ");
    scanf("%d", &idx);
    idx--;

    if(idx < 0 || idx >= taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    Task *t = &tasks[idx];
    if(t->hourlyUpdateCount < LAZINESS_THRESHOLD) {
        printf("Distraction Alert: Hourly updates are low. Are you being lazy?\n");
    } else {
        printf("Task is on track.\n");
    }
}

// Main menu
void menu() {
    while(1) {
        printf("\n--- Todo List Menu ---\n");
        printf("1. Add Task\n");
        printf("2. Update Progress\n");
        printf("3. View Progress Flow\n");
        printf("4. Check Distraction Indicator\n");
        printf("5. List All Tasks\n");
        printf("6. Exit\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);

        switch(choice) {
            case 1: addTask(); break;
            case 2: updateProgress(); break;
            case 3: viewProgressFlow(); break;
            case 4: checkDistraction(); break;
            case 5: listTasks(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

int main() {
    printf("Welcome to the Terminal-based Todo List!\n");
    menu();
    return 0;
}
