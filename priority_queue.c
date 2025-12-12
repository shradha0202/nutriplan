// Priority Queue (Max Heap) for Optimal Meal Ranking
// NutriPlan - Data Structures Project
// Ranks meals based on nutrition score to show TOP 3 recommendations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Meal structure with nutrition score
typedef struct {
    char name[50];
    char hindiName[50];
    int calories;
    float protein;
    float carbs;
    float fats;
    int cost;
    int score;  // Calculated based on user goal
} Meal;

// Priority Queue structure (Max Heap)
typedef struct {
    Meal heap[MAX_SIZE];
    int size;
} PriorityQueue;

// Initialize priority queue
void initPQ(PriorityQueue *pq) {
    pq->size = 0;
}

// Swap two meals
void swap(Meal *a, Meal *b) {
    Meal temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up - maintain max heap property after insertion
// Time Complexity: O(log n)
// Space Complexity: O(1)
void heapifyUp(PriorityQueue *pq, int index) {
    if (index == 0) return;
    
    int parent = (index - 1) / 2;
    
    if (pq->heap[index].score > pq->heap[parent].score) {
        swap(&pq->heap[index], &pq->heap[parent]);
        heapifyUp(pq, parent);
    }
}

// Heapify down - maintain max heap property after extraction
// Time Complexity: O(log n)
// Space Complexity: O(1)
void heapifyDown(PriorityQueue *pq, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < pq->size && pq->heap[left].score > pq->heap[largest].score) {
        largest = left;
    }
    
    if (right < pq->size && pq->heap[right].score > pq->heap[largest].score) {
        largest = right;
    }
    
    if (largest != index) {
        swap(&pq->heap[index], &pq->heap[largest]);
        heapifyDown(pq, largest);
    }
}

// Insert meal into priority queue
// Time Complexity: O(log n)
// Space Complexity: O(1)
void insertMeal(PriorityQueue *pq, char *name, char *hindiName, int calories, 
                float protein, float carbs, float fats, int cost, int score) {
    if (pq->size >= MAX_SIZE) {
        printf("Queue is full!\n");
        return;
    }
    
    Meal newMeal;
    strcpy(newMeal.name, name);
    strcpy(newMeal.hindiName, hindiName);
    newMeal.calories = calories;
    newMeal.protein = protein;
    newMeal.carbs = carbs;
    newMeal.fats = fats;
    newMeal.cost = cost;
    newMeal.score = score;
    
    pq->heap[pq->size] = newMeal;
    heapifyUp(pq, pq->size);
    pq->size++;
}

// Extract maximum (best scored meal)
// Time Complexity: O(log n)
// Space Complexity: O(1)
Meal extractMax(PriorityQueue *pq) {
    Meal empty = {"", "", 0, 0, 0, 0, 0, 0};
    
    if (pq->size == 0) {
        printf("Queue is empty!\n");
        return empty;
    }
    
    Meal maxMeal = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    
    return maxMeal;
}

// Peek at top meal without removing
Meal peekMax(PriorityQueue *pq) {
    Meal empty = {"", "", 0, 0, 0, 0, 0, 0};
    
    if (pq->size == 0) {
        return empty;
    }
    
    return pq->heap[0];
}

// Calculate nutrition score based on goal
// Time Complexity: O(1)
// Space Complexity: O(1)
int calculateScore(char *goal, int calories, float protein, float carbs) {
    int score = 0;
    
    if (strcmp(goal, "weight-loss") == 0) {
        // High protein + low calories = higher score
        score = (int)(protein * 3) - (calories / 10);
    } else if (strcmp(goal, "muscle-gain") == 0) {
        // High protein + moderate calories = higher score
        score = (int)(protein * 4) + (calories / 20);
    } else if (strcmp(goal, "maintain") == 0) {
        // Balanced nutrition
        score = (int)(protein * 2.5);
    } else if (strcmp(goal, "pcod") == 0) {
        // Low carbs + moderate protein
        score = (int)(protein * 2) - (int)(carbs / 5);
    } else {
        // Default balanced score
        score = (int)(protein * 2);
    }
    
    return score;
}

// Display meal details
void displayMeal(Meal meal, int rank) {
    printf("\n#%d: %s (%s)\n", rank, meal.name, meal.hindiName);
    printf("    Calories: %d kcal | Protein: %.1fg | Carbs: %.1fg | Fats: %.1fg\n", 
           meal.calories, meal.protein, meal.carbs, meal.fats);
    printf("    Cost: Rs.%d | Nutrition Score: %d\n", meal.cost, meal.score);
}

// Main function demonstrating Priority Queue
int main() {
    PriorityQueue pq;
    initPQ(&pq);
    
    printf("=== NutriPlan Meal Ranking System (Priority Queue) ===\n\n");
    
    // Test Case 1: Weight Loss Goal
    char goal1[] = "weight-loss";
    printf("GOAL: %s\n", goal1);
    printf("Strategy: High protein, low calories get best scores\n");
    printf("---------------------------------------------------\n");
    
    // Insert meals with calculated scores
    insertMeal(&pq, "Moong Dal Cheela", "मूंग दाल चीला", 180, 12.0, 25.0, 4.0, 20,
               calculateScore(goal1, 180, 12.0, 25.0));
    insertMeal(&pq, "Paneer Bhurji", "पनीर भुर्जी", 265, 18.5, 8.0, 14.0, 65,
               calculateScore(goal1, 265, 18.5, 8.0));
    insertMeal(&pq, "Chicken Curry", "चिकन करी", 380, 32.0, 12.0, 15.0, 80,
               calculateScore(goal1, 380, 32.0, 12.0));
    insertMeal(&pq, "Poha", "पोहा", 250, 6.0, 40.0, 7.0, 15,
               calculateScore(goal1, 250, 6.0, 40.0));
    insertMeal(&pq, "Egg Curry", "अंडा करी", 350, 20.0, 18.0, 16.0, 45,
               calculateScore(goal1, 350, 20.0, 18.0));
    insertMeal(&pq, "Dal Tadka", "दाल तड़का", 320, 14.0, 48.0, 8.0, 30,
               calculateScore(goal1, 320, 14.0, 48.0));
    
    printf("\nTOP 3 Meals for Weight Loss:\n");
    for (int i = 1; i <= 3 && pq.size > 0; i++) {
        Meal best = extractMax(&pq);
        displayMeal(best, i);
    }
    
    // Reset for next test
    initPQ(&pq);
    
    // Test Case 2: Muscle Gain Goal
    printf("\n\n==========================================================\n");
    char goal2[] = "muscle-gain";
    printf("GOAL: %s\n", goal2);
    printf("Strategy: High protein + moderate calories get best scores\n");
    printf("---------------------------------------------------\n");
    
    insertMeal(&pq, "Moong Dal Cheela", "मूंग दाल चीला", 180, 12.0, 25.0, 4.0, 20,
               calculateScore(goal2, 180, 12.0, 25.0));
    insertMeal(&pq, "Paneer Bhurji", "पनीर भुर्जी", 265, 18.5, 8.0, 14.0, 65,
               calculateScore(goal2, 265, 18.5, 8.0));
    insertMeal(&pq, "Chicken Curry", "चिकन करी", 380, 32.0, 12.0, 15.0, 80,
               calculateScore(goal2, 380, 32.0, 12.0));
    insertMeal(&pq, "Poha", "पोहा", 250, 6.0, 40.0, 7.0, 15,
               calculateScore(goal2, 250, 6.0, 40.0));
    insertMeal(&pq, "Egg Curry", "अंडा करी", 350, 20.0, 18.0, 16.0, 45,
               calculateScore(goal2, 350, 20.0, 18.0));
    insertMeal(&pq, "Chole", "छोले", 420, 18.0, 65.0, 10.0, 45,
               calculateScore(goal2, 420, 18.0, 65.0));
    
    printf("\nTOP 3 Meals for Muscle Gain:\n");
    for (int i = 1; i <= 3 && pq.size > 0; i++) {
        Meal best = extractMax(&pq);
        displayMeal(best, i);
    }
    
    printf("\n\n=== Priority Queue successfully ranks meals by goal! ===\n");
    
    return 0;
}