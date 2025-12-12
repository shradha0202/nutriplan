// Binary Search Tree for Food Database Organization
// NutriPlan - Data Structures Project
// Organizes 100+ Indian foods by calorie content for fast searching

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Food node structure
typedef struct FoodNode {
    char name[50];
    char hindiName[50];
    int calories;
    float protein;
    float carbs;
    float fats;
    int cost;  // in rupees
    char dietType[20];  // veg/non-veg/egg
    struct FoodNode *left;
    struct FoodNode *right;
} FoodNode;

// Create new food node
FoodNode* createNode(char *name, char *hindiName, int calories, float protein, 
                     float carbs, float fats, int cost, char *dietType) {
    FoodNode *newNode = (FoodNode*)malloc(sizeof(FoodNode));
    strcpy(newNode->name, name);
    strcpy(newNode->hindiName, hindiName);
    newNode->calories = calories;
    newNode->protein = protein;
    newNode->carbs = carbs;
    newNode->fats = fats;
    newNode->cost = cost;
    strcpy(newNode->dietType, dietType);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert food into BST (ordered by calories)
// Time Complexity: O(log n) average, O(n) worst case
// Space Complexity: O(1)
FoodNode* insertFood(FoodNode *root, char *name, char *hindiName, int calories, 
                     float protein, float carbs, float fats, int cost, char *dietType) {
    if (root == NULL) {
        return createNode(name, hindiName, calories, protein, carbs, fats, cost, dietType);
    }
    
    if (calories < root->calories) {
        root->left = insertFood(root->left, name, hindiName, calories, protein, 
                               carbs, fats, cost, dietType);
    } else {
        root->right = insertFood(root->right, name, hindiName, calories, protein, 
                                carbs, fats, cost, dietType);
    }
    
    return root;
}

// Search foods within calorie range (for goal-based filtering)
// Time Complexity: O(n) worst case, O(log n) average
// Space Complexity: O(h) for recursion stack, where h is height
void searchInRange(FoodNode *root, int minCal, int maxCal, char *dietType) {
    if (root == NULL) return;
    
    // Check left subtree if min is less than current
    if (minCal < root->calories) {
        searchInRange(root->left, minCal, maxCal, dietType);
    }
    
    // Print if in range and matches diet type
    if (root->calories >= minCal && root->calories <= maxCal) {
        if (strcmp(dietType, "all") == 0 || strcmp(root->dietType, dietType) == 0) {
            printf("%-25s %-20s %4d kcal | P:%.1fg C:%.1fg F:%.1fg | Rs.%d | %s\n", 
                   root->name, root->hindiName, root->calories, 
                   root->protein, root->carbs, root->fats, 
                   root->cost, root->dietType);
        }
    }
    
    // Check right subtree if max is greater than current
    if (maxCal > root->calories) {
        searchInRange(root->right, minCal, maxCal, dietType);
    }
}

// Inorder traversal (prints foods in ascending calorie order)
// Time Complexity: O(n)
// Space Complexity: O(h) for recursion
void inorderTraversal(FoodNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s (%d kcal) ", root->name, root->calories);
        inorderTraversal(root->right);
    }
}

// Find minimum calorie food (leftmost node)
FoodNode* findMin(FoodNode *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Find maximum calorie food (rightmost node)
FoodNode* findMax(FoodNode *root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Count total foods in database
int countNodes(FoodNode *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Main function demonstrating BST operations
int main() {
    FoodNode *root = NULL;
    
    printf("=== NutriPlan Food Database (Binary Search Tree) ===\n\n");
    
    // Insert Indian foods - organized by calories
    root = insertFood(root, "Moong Dal Cheela", "मूंग दाल चीला", 180, 12.0, 25.0, 4.0, 20, "veg");
    root = insertFood(root, "Oats Upma", "ओट्स उपमा", 210, 8.0, 32.0, 6.0, 25, "veg");
    root = insertFood(root, "Egg Bhurji", "अंडा भुर्जी", 220, 18.0, 8.0, 14.0, 30, "egg");
    root = insertFood(root, "Boiled Eggs", "उबले अंडे", 240, 16.0, 22.0, 11.0, 25, "egg");
    root = insertFood(root, "Poha", "पोहा", 250, 6.0, 40.0, 7.0, 15, "veg");
    root = insertFood(root, "Paneer Bhurji", "पनीर भुर्जी", 265, 18.5, 8.0, 14.0, 65, "veg");
    root = insertFood(root, "Idli Sambar", "इडली सांभर", 280, 10.0, 48.0, 6.0, 40, "veg");
    root = insertFood(root, "Dal Tadka", "दाल तड़का", 320, 14.0, 48.0, 8.0, 30, "veg");
    root = insertFood(root, "Fish Curry", "मछली करी", 320, 28.0, 22.0, 14.0, 90, "non-veg");
    root = insertFood(root, "Paneer Paratha", "पनीर पराठा", 320, 15.0, 40.0, 12.0, 50, "veg");
    root = insertFood(root, "Rajma Chawal", "राजमा चावल", 380, 16.0, 58.0, 9.0, 35, "veg");
    root = insertFood(root, "Chicken Curry", "चिकन करी", 380, 32.0, 35.0, 12.0, 80, "non-veg");
    root = insertFood(root, "Egg Curry", "अंडा करी", 350, 20.0, 48.0, 10.0, 45, "egg");
    root = insertFood(root, "Chole", "छोले", 420, 18.0, 65.0, 10.0, 45, "veg");
    
    printf("Total foods in database: %d\n\n", countNodes(root));
    
    printf("=== All Foods (Sorted by Calories - Inorder Traversal) ===\n");
    inorderTraversal(root);
    printf("\n\n");
    
    // Find extremes
    FoodNode *minFood = findMin(root);
    FoodNode *maxFood = findMax(root);
    printf("Lowest Calorie: %s (%d kcal)\n", minFood->name, minFood->calories);
    printf("Highest Calorie: %s (%d kcal)\n\n", maxFood->name, maxFood->calories);
    
    // Search by goal
    printf("=== WEIGHT LOSS Foods (150-300 kcal, Veg) ===\n");
    searchInRange(root, 150, 300, "veg");
    
    printf("\n=== MUSCLE GAIN Foods (300-450 kcal, Non-Veg) ===\n");
    searchInRange(root, 300, 450, "non-veg");
    
    printf("\n=== ALL Foods in Moderate Range (250-350 kcal) ===\n");
    searchInRange(root, 250, 350, "all");
    
    return 0;
}