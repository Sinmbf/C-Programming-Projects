#include <stdio.h>
#include <stdlib.h>

struct item {
    char name[20];
    float cost;
    float total;
    int date;
};

struct expenses {
    struct item *items;
    int count;
};

void menu();
struct expenses loaddata();
void clearExpenses(struct expenses *e);
void add(struct expenses *e);
void display(struct expenses e);
void saveExpenses(struct expenses e);

int main() {
    struct expenses e;
    int n;
    char ch;
    e = loaddata();
    do {
        menu();
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &n);
        switch (n) {
            case 1:
                add(&e);
                break;
            case 2:
                display(e);
                break;
            case 3:
                clearExpenses(&e);
                break;
            case 4:
                saveExpenses(e);
                exit(0);
            default:
                printf("\t\t\tWrong Choice!!!\n");
                printf("\t\t\tEnter 1 to 4 only:");
        }

        printf("\nDo you want to continue (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
    system("cls");
    return 0;
}

void menu() {
    system("cls");
    printf("\n\n");
    printf("\t\t\t_________________________________\n");
    printf("\t\t\t|   EXPENSE MANAGEMENT SYSTEM   |\n");
    printf("\t\t\t|_______________________________|\n\n\n\n\n");
    printf("\t\t\t_________________________________\n");
    printf("\t\t\t|   1. Add Expenses             |\n");
    printf("\t\t\t|   2. Display expenses         |\n");
    printf("\t\t\t|   3. Clear Expenses           |\n");
    printf("\t\t\t|   4. Save Expenses and Exit   |\n");
    printf("\t\t\t|_______________________________|\n");
}

struct expenses loaddata() {
    FILE *fp;
    struct expenses e;
    int i;

    fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!!!\n");
        e.count = 0;
        return e;
    }

    // Read the count of items
    fscanf(fp, "%d", &e.count);

    // Allocate memory for items
    e.items = (struct item *)malloc(e.count * sizeof(struct item));
    if (e.items == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        exit(0);
    }

    // Read each item separately
    for (i = 0; i < e.count; i++) {
        fscanf(fp, "%s %f", e.items[i].name, &e.items[i].cost);
    }

    fclose(fp);
    return e;
}

void add(struct expenses *e) {
    struct item newItem;
    printf("\n\t\t\tEnter expense: ");
    scanf("%s", newItem.name);
    printf("\n\t\t\tEnter cost: ");
    scanf("%f", &newItem.cost);
    
    e->items = (struct item *)realloc(e->items, (e->count + 1) * sizeof(struct item));
    if (e->items == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    e->items[e->count++] = newItem;
    printf("\n\t\t\tExpense Added\n");
}

void clearExpenses(struct expenses *e) {
    FILE *fp;
    fp = fopen("expenses.txt", "w");
    if (fp == NULL) {
        printf("Error clearing file!!!\n");
        exit(0);
    }
    fclose(fp);
    free(e->items);
    e->count = 0;
    printf("Expenses cleared successfully\n");
}

void saveExpenses(struct expenses e) {
    FILE *fp;
    int i;

    fp = fopen("expenses.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!!!\n");
        exit(0);
    }

    // Write the count of items
    fprintf(fp, "%d\n", e.count);

    // Write each item separately
    for (i = 0; i < e.count; i++) {
        fprintf(fp, "%s %.2f\n", e.items[i].name, e.items[i].cost);
    }

    fclose(fp);
}


void display(struct expenses e) {
    int i;
    float tcost = 0;
    if (e.count == 0) {
        printf("\n\t\t\t NO EXPENSES DONE !!!\n");
        return;
    }
    printf("\t\t\tExpenses\n");
    printf("\t\t\t--------------------------------\n");
    for (i = 0; i < e.count; i++) {
        printf("\t\t\t%-20s $%.2f\n", e.items[i].name, e.items[i].cost);
        tcost += e.items[i].cost;
    }
    printf("\t\t\t--------------------------------\n");
    printf("\t\t\tTotal Cost of %d expenses: $%.2f\n", e.count, tcost);
}

