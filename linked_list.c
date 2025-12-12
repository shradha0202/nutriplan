// Linked List for Recipe Step Management
// NutriPlan - Data Structures Project
// Dynamically manages cooking instructions with easy insertion/deletion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recipe step node
typedef struct StepNode {
    int stepNumber;
    char instruction[200];
    char timeEstimate[20];
    struct StepNode *next;
} StepNode;

// Create new step node
// Time Complexity: O(1)
// Space Complexity: O(1)
StepNode* createStep(int number, char *instruction, char *time) {
    StepNode newStep = (StepNode)malloc(sizeof(StepNode));
    newStep->stepNumber = number;
    strcpy(newStep->instruction, instruction);
    strcpy(newStep->timeEstimate, time);
    newStep->next = NULL;
    return newStep;
}

// Insert step at beginning (for prep steps)
// Time Complexity: O(1)
// Space Complexity: O(1)
void insertAtBeginning(StepNode **head, int number, char *instruction, char *time) {
    StepNode *newStep = createStep(number, instruction, time);
    newStep->next = *head;
    *head = newStep;
    printf("✅ Inserted at beginning: %s\n", instruction);
}

// Insert step at end (most common - adding final steps)
// Time Complexity: O(n)
// Space Complexity: O(1)
void insertAtEnd(StepNode **head, int number, char *instruction, char *time) {
    StepNode *newStep = createStep(number, instruction, time);
    
    if (*head == NULL) {
        *head = newStep;
        return;
    }
    
    StepNode *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newStep;
}

// Insert step after specific position
// Time Complexity: O(n)
// Space Complexity: O(1)
void insertAfter(StepNode *prevStep, int number, char *instruction, char *time) {
    if (prevStep == NULL) {
        printf("❌ Previous step cannot be NULL\n");
        return;
    }
    
    StepNode *newStep = createStep(number, instruction, time);
    newStep->next = prevStep->next;
    prevStep->next = newStep;
    printf("✅ Inserted after step: %s\n", instruction);
}

// Delete step at specific position
// Time Complexity: O(n)
// Space Complexity: O(1)
void deleteStep(StepNode **head, int position) {
    if (*head == NULL) {
        printf("❌ Recipe is empty!\n");
        return;
    }
    
    StepNode *temp = *head;
    
    // Delete head
    if (position == 0) {
        *head = temp->next;
        printf("🗑  Deleted: %s\n", temp->instruction);
        free(temp);
        return;
    }
    
    // Find previous node
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL || temp->next == NULL) {
        printf("❌ Position out of range\n");
        return;
    }
    
    StepNode *toDelete = temp->next;
    temp->next = toDelete->next;
    printf("🗑  Deleted: %s\n", toDelete->instruction);
    free(toDelete);
}

// Display all recipe steps
// Time Complexity: O(n)
// Space Complexity: O(1)
void displayRecipe(StepNode *head, char *recipeName) {
    if (head == NULL) {
        printf("❌ No recipe steps available.\n");
        return;
    }
    
    printf("\n👨‍🍳 ========================================\n");
    printf("   RECIPE: %s\n", recipeName);
    printf("========================================\n\n");
    
    StepNode *temp = head;
    int stepCount = 1;
    int totalTime = 0;
    
    while (temp != NULL) {
        printf("Step %d: %s\n", stepCount, temp->instruction);
        printf("  ⏱  Time: %s\n\n", temp->timeEstimate);
        
        // Calculate total time (extract number from time string)
        int mins;
        if (sscanf(temp->timeEstimate, "%d", &mins) == 1) {
            totalTime += mins;
        }
        
        temp = temp->next;
        stepCount++;
    }
    
    printf("========================================\n");
    printf("Total Steps: %d | Total Time: ~%d mins\n", stepCount - 1, totalTime);
    printf("========================================\n\n");
}

// Count total steps
// Time Complexity: O(n)
// Space Complexity: O(1)
int countSteps(StepNode *head) {
    int count = 0;
    StepNode *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Search for specific keyword in steps
// Time Complexity: O(n)
// Space Complexity: O(1)
StepNode* searchStep(StepNode *head, char *keyword) {
    StepNode *temp = head;
    int position = 1;
    
    while (temp != NULL) {
        if (strstr(temp->instruction, keyword) != NULL) {
            printf("🔍 Found '%s' in Step %d: %s\n", keyword, position, temp->instruction);
            return temp;
        }
        temp = temp->next;
        position++;
    }
    
    printf("❌ Keyword '%s' not found in recipe\n", keyword);
    return NULL;
}

// Reverse recipe (useful for showing steps in reverse order)
// Time Complexity: O(n)
// Space Complexity: O(1)
void reverseRecipe(StepNode **head) {
    StepNode *prev = NULL;
    StepNode *current = *head;
    StepNode *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    *head = prev;
    printf("🔄 Recipe steps reversed!\n");
}

// Free all nodes (cleanup)
void freeRecipe(StepNode **head) {
    StepNode *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Main function demonstrating Linked List operations
int main() {
    StepNode *paneerRecipe = NULL;
    
    printf("\n=== NutriPlan Recipe Management System (Linked List) ===\n\n");
    
    // Build Paneer Bhurji recipe step by step
    printf("--- BUILDING PANEER BHURJI RECIPE ---\n\n");
    
    insertAtEnd(&paneerRecipe, 1, "Crumble paneer into small pieces", "2 mins");
    insertAtEnd(&paneerRecipe, 2, "Heat oil in pan on medium flame", "1 min");
    insertAtEnd(&paneerRecipe, 3, "Add cumin seeds and let them splutter", "30 secs");
    insertAtEnd(&paneerRecipe, 4, "Add chopped onions and green chili", "3 mins");
    insertAtEnd(&paneerRecipe, 5, "Add chopped tomatoes and cook until soft", "4 mins");
    insertAtEnd(&paneerRecipe, 6, "Add turmeric, red chili powder, coriander powder", "30 secs");
    insertAtEnd(&paneerRecipe, 7, "Add crumbled paneer and mix well", "2 mins");
    insertAtEnd(&paneerRecipe, 8, "Cook for 3-4 minutes stirring occasionally", "4 mins");
    insertAtEnd(&paneerRecipe, 9, "Garnish with coriander leaves", "30 secs");
    insertAtEnd(&paneerRecipe, 10, "Serve hot with roti or bread", "0 mins");
    
    // Display complete recipe
    displayRecipe(paneerRecipe, "Paneer Bhurji");
    
    // Count steps
    printf("Total steps in recipe: %d\n\n", countSteps(paneerRecipe));
    
    // Search for a step
    printf("--- SEARCHING FOR STEPS ---\n");
    searchStep(paneerRecipe, "tomatoes");
    searchStep(paneerRecipe, "salt");  // Not found
    printf("\n");
    
    // Modify recipe - add a forgotten step at beginning
    printf("--- ADDING PREP STEP AT BEGINNING ---\n");
    insertAtBeginning(&paneerRecipe, 0, "Gather all ingredients and keep ready", "2 mins");
    displayRecipe(paneerRecipe, "Paneer Bhurji (Updated)");
    
    // Delete a step (remove cumin for simpler version)
    printf("--- CREATING SIMPLIFIED VERSION ---\n");
    printf("Removing cumin step for quick recipe...\n");
    deleteStep(&paneerRecipe, 3);  // Index 3 = 4th step (after adding prep)
    displayRecipe(paneerRecipe, "Paneer Bhurji (Quick Version)");
    
    // Create another recipe - Dal Tadka
    printf("\n--- CREATING DAL TADKA RECIPE ---\n\n");
    StepNode *dalRecipe = NULL;
    
    insertAtEnd(&dalRecipe, 1, "Pressure cook toor dal with turmeric for 3 whistles", "15 mins");
    insertAtEnd(&dalRecipe, 2, "Mash the dal until smooth", "2 mins");
    insertAtEnd(&dalRecipe, 3, "Heat ghee in a pan", "1 min");
    insertAtEnd(&dalRecipe, 4, "Add cumin seeds, garlic, and dried red chili", "1 min");
    insertAtEnd(&dalRecipe, 5, "Add chopped tomatoes and cook", "3 mins");
    insertAtEnd(&dalRecipe, 6, "Pour tadka over dal and mix", "1 min");
    insertAtEnd(&dalRecipe, 7, "Garnish with coriander and serve hot", "0 mins");
    
    displayRecipe(dalRecipe, "Dal Tadka");
    
    // Demonstrate insertion after specific step
    printf("--- INSERTING STEP AFTER 'Add tomatoes' ---\n");
    StepNode *tomatoStep = searchStep(dalRecipe, "tomatoes");
    if (tomatoStep != NULL) {
        insertAfter(tomatoStep, 6, "Add garam masala and salt to taste", "30 secs");
    }
    displayRecipe(dalRecipe, "Dal Tadka (Enhanced)");
    
    // Cleanup
    printf("--- CLEANING UP MEMORY ---\n");
    freeRecipe(&paneerRecipe);
    freeRecipe(&dalRecipe);
    printf("✅ All recipes freed from memory\n\n");
    
    printf("=== Linked List demonstration complete! ===\n");
    printf("Key advantages: Dynamic size, easy insertion/deletion anywhere\n\n");
    
    return 0;
}