// Stack (LIFO) for Cheat Meal Sin Tracking
// NutriPlan - Data Structures Project
// Tracks junk food consumption with Last-In-First-Out behavior

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STACK 50

// Cheat meal structure
typedef struct {
    char name[50];
    char icon[10];
    int calories;
    char timestamp[30];
    char consequence[100];
} CheatMeal;

// Stack structure
typedef struct {
    CheatMeal items[MAX_STACK];
    int top;
} CheatStack;

// Initialize stack
// Time Complexity: O(1)
// Space Complexity: O(1)
void initStack(CheatStack *stack) {
    stack->top = -1;
}

// Check if stack is empty
// Time Complexity: O(1)
int isEmpty(CheatStack *stack) {
    return stack->top == -1;
}

// Check if stack is full
// Time Complexity: O(1)
int isFull(CheatStack *stack) {
    return stack->top == MAX_STACK - 1;
}

// Push cheat meal onto stack
// Time Complexity: O(1)
// Space Complexity: O(1)
void push(CheatStack *stack, char *name, char *icon, int calories) {
    if (isFull(stack)) {
        printf("❌ Stack overflow! Too many sins (max 50)\n");
        return;
    }
    
    stack->top++;
    CheatMeal *cheat = &stack->items[stack->top];
    
    strcpy(cheat->name, name);
    strcpy(cheat->icon, icon);
    cheat->calories = calories;
    
    // Add timestamp
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(cheat->timestamp, sizeof(cheat->timestamp), "%Y-%m-%d %H:%M:%S", t);
    
    // Generate consequence message
    int daysDelayed = calories / 500;  // Rough estimate: 500 kcal = 1 day delay
    sprintf(cheat->consequence, 
            "🔥 %d kcal = Goal delayed by ~%d day(s)", 
            calories, daysDelayed);
    
    printf("❌ PUSH: %s %s (%d kcal) added to sin stack\n", icon, name, calories);
}

// Pop (undo) last cheat meal from stack
// Time Complexity: O(1)
// Space Complexity: O(1)
CheatMeal pop(CheatStack *stack) {
    CheatMeal empty = {"", "", 0, "", ""};
    
    if (isEmpty(stack)) {
        printf("✅ Stack is empty! No sins to undo.\n");
        return empty;
    }
    
    CheatMeal removed = stack->items[stack->top];
    stack->top--;
    
    printf("✅ POP: %s %s (%d kcal) removed from stack\n", 
           removed.icon, removed.name, removed.calories);
    return removed;
}

// Peek at top cheat meal without removing
// Time Complexity: O(1)
CheatMeal peek(CheatStack *stack) {
    CheatMeal empty = {"", "", 0, "", ""};
    
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return empty;
    }
    
    return stack->items[stack->top];
}

// Display entire stack (from top to bottom)
// Time Complexity: O(n)
// Space Complexity: O(1)
void displayStack(CheatStack *stack) {
    if (isEmpty(stack)) {
        printf("\n🎉 ==========================================\n");
        printf("   No sins! You're on track! Keep going!\n");
        printf("==========================================\n\n");
        return;
    }
    
    printf("\n📚 ========== YOUR SIN STACK (LIFO) ==========\n");
    printf("   Total Sins: %d\n", stack->top + 1);
    printf("==============================================\n\n");
    
    int totalCalories = 0;
    
    for (int i = stack->top; i >= 0; i--) {
        CheatMeal *cheat = &stack->items[i];
        
        if (i == stack->top) {
            printf("🔝 TOP → ");
        } else {
            printf("       ");
        }
        
        printf("[%s %s - %d kcal]\n", cheat->icon, cheat->name, cheat->calories);
        printf("         📅 %s\n", cheat->timestamp);
        printf("         %s\n\n", cheat->consequence);
        
        totalCalories += cheat->calories;
    }
    
    printf("⬇ BOTTOM (Oldest sin)\n\n");
    printf("💀 TOTAL SIN CALORIES: %d kcal\n", totalCalories);
    printf("⚠  Goal delayed by ~%d days!\n", totalCalories / 500);
    printf("==============================================\n\n");
}

// Get total sin calories
// Time Complexity: O(n)
int getTotalSinCalories(CheatStack *stack) {
    int total = 0;
    for (int i = 0; i <= stack->top; i++) {
        total += stack->items[i].calories;
    }
    return total;
}

// Get stack size
// Time Complexity: O(1)
int getSize(CheatStack *stack) {
    return stack->top + 1;
}

// Clear all sins from stack
// Time Complexity: O(1)
void clearStack(CheatStack *stack) {
    stack->top = -1;
    printf("🗑  All sins cleared! Fresh start!\n");
}

// Main function demonstrating Stack operations
int main() {
    CheatStack sinStack;
    initStack(&sinStack);
    
    printf("\n=== NutriPlan Cheat Meal Tracker (Stack - LIFO) ===\n\n");
    
    // Simulate user eating junk food (PUSH operations)
    printf("--- USER STARTS EATING JUNK ---\n\n");
    push(&sinStack, "Pizza", "🍕", 700);
    push(&sinStack, "Burger with Fries", "🍔", 550);
    push(&sinStack, "Maggi", "🍜", 400);
    push(&sinStack, "Cola", "🥤", 150);
    
    // Display current stack
    displayStack(&sinStack);
    
    // Peek at top sin
    printf("--- PEEKING AT TOP SIN (WITHOUT REMOVING) ---\n");
    CheatMeal topSin = peek(&sinStack);
    printf("Top sin: %s %s (%d kcal)\n\n", topSin.icon, topSin.name, topSin.calories);
    
    // User regrets and undos last 2 sins (POP operations)
    printf("--- USER REGRETS AND UNDOS LAST 2 SINS ---\n\n");
    pop(&sinStack);
    pop(&sinStack);
    
    // Display updated stack
    displayStack(&sinStack);
    
    // Add more sins
    printf("--- USER EATS MORE JUNK ---\n\n");
    push(&sinStack, "Samosa", "🥟", 250);
    push(&sinStack, "Ice Cream", "🍦", 280);
    
    displayStack(&sinStack);
    
    // Test stack properties
    printf("--- STACK STATISTICS ---\n");
    printf("Current stack size: %d\n", getSize(&sinStack));
    printf("Total damage: %d kcal\n", getTotalSinCalories(&sinStack));
    printf("Is empty? %s\n", isEmpty(&sinStack) ? "Yes" : "No");
    printf("Is full? %s\n\n", isFull(&sinStack) ? "Yes" : "No");
    
    // Undo all remaining sins
    printf("--- UNDOING ALL REMAINING SINS ---\n\n");
    while (!isEmpty(&sinStack)) {
        pop(&sinStack);
    }
    
    // Try to pop from empty stack
    printf("\n--- TRYING TO POP FROM EMPTY STACK ---\n");
    pop(&sinStack);
    
    displayStack(&sinStack);
    
    printf("\n=== Stack demonstration complete! ===\n");
    printf("Key takeaway: LIFO - Last In, First Out\n");
    printf("Most recent cheat is always at TOP and removed first\n\n");
    
    return 0;
}