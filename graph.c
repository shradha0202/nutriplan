// Graph (Adjacency List) for Food Substitution Network
// NutriPlan - Data Structures Project
// Finds alternative foods using graph traversal (BFS)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOODS 50
#define MAX_QUEUE 50

// Food vertex structure
typedef struct Food {
    char name[50];
    char hindiName[50];
    int calories;
    float protein;
    char dietType[20];  // veg/non-veg/egg
} Food;

// Adjacency list node
typedef struct AdjNode {
    int foodIndex;
    struct AdjNode *next;
} AdjNode;

// Graph structure
typedef struct {
    Food foods[MAX_FOODS];
    AdjNode *adjList[MAX_FOODS];
    int numFoods;
} FoodGraph;

// Initialize graph
// Time Complexity: O(V)
// Space Complexity: O(1)
void initGraph(FoodGraph *graph) {
    graph->numFoods = 0;
    for (int i = 0; i < MAX_FOODS; i++) {
        graph->adjList[i] = NULL;
    }
}

// Add food vertex to graph
// Time Complexity: O(1)
// Space Complexity: O(1)
int addFood(FoodGraph *graph, char *name, char *hindiName, int calories, 
            float protein, char *dietType) {
    if (graph->numFoods >= MAX_FOODS) {
        printf("❌ Graph is full!\n");
        return -1;
    }
    
    int index = graph->numFoods;
    strcpy(graph->foods[index].name, name);
    strcpy(graph->foods[index].hindiName, hindiName);
    graph->foods[index].calories = calories;
    graph->foods[index].protein = protein;
    strcpy(graph->foods[index].dietType, dietType);
    
    graph->numFoods++;
    printf("✅ Added: %s (%s) - %d kcal, %.1fg protein, %s\n", 
           name, hindiName, calories, protein, dietType);
    return index;
}

// Add edge (substitution link) between two foods
// Time Complexity: O(1)
// Space Complexity: O(1)
void addEdge(FoodGraph *graph, int food1, int food2) {
    // Add edge from food1 to food2
    AdjNode *newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->foodIndex = food2;
    newNode->next = graph->adjList[food1];
    graph->adjList[food1] = newNode;
    
    // Add edge from food2 to food1 (undirected graph)
    newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->foodIndex = food1;
    newNode->next = graph->adjList[food2];
    graph->adjList[food2] = newNode;
    
    printf("🔗 Linked: %s ↔ %s\n", 
           graph->foods[food1].name, graph->foods[food2].name);
}

// Find substitutes using BFS (Breadth-First Search)
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void findSubstitutes(FoodGraph *graph, int foodIndex) {
    if (foodIndex < 0 || foodIndex >= graph->numFoods) {
        printf("❌ Invalid food index\n");
        return;
    }
    
    int visited[MAX_FOODS] = {0};
    int queue[MAX_QUEUE];
    int front = 0, rear = 0;
    
    // Start BFS
    queue[rear++] = foodIndex;
    visited[foodIndex] = 1;
    
    printf("\n🔍 ========================================\n");
    printf("   FINDING SUBSTITUTES FOR:\n");
    printf("========================================\n");
    printf("Original: %s (%s)\n", 
           graph->foods[foodIndex].name,
           graph->foods[foodIndex].hindiName);
    printf("  • %d kcal | %.1fg protein | %s\n\n", 
           graph->foods[foodIndex].calories,
           graph->foods[foodIndex].protein,
           graph->foods[foodIndex].dietType);
    
    printf("AVAILABLE SWAPS:\n");
    printf("----------------------------------------\n");
    
    int swapCount = 0;
    
    while (front < rear) {
        int current = queue[front++];
        
        AdjNode *temp = graph->adjList[current];
        while (temp != NULL) {
            int adjFood = temp->foodIndex;
            
            if (!visited[adjFood]) {
                visited[adjFood] = 1;
                queue[rear++] = adjFood;
                
                swapCount++;
                printf("%d. %s (%s)\n", swapCount, 
                       graph->foods[adjFood].name,
                       graph->foods[adjFood].hindiName);
                printf("   • %d kcal | %.1fg protein | %s\n\n",
                       graph->foods[adjFood].calories,
                       graph->foods[adjFood].protein,
                       graph->foods[adjFood].dietType);
            }
            
            temp = temp->next;
        }
    }
    
    if (swapCount == 0) {
        printf("  ❌ No direct substitutes found\n");
    } else {
        printf("----------------------------------------\n");
        printf("Total substitutes found: %d\n", swapCount);
    }
    printf("========================================\n\n");
}

// Display entire graph (adjacency list)
// Time Complexity: O(V + E)
// Space Complexity: O(1)
void displayGraph(FoodGraph *graph) {
    printf("\n🕸️  ========================================\n");
    printf("   FOOD SUBSTITUTION NETWORK\n");
    printf("========================================\n\n");
    
    for (int i = 0; i < graph->numFoods; i++) {
        printf("%s → ", graph->foods[i].name);
        
        AdjNode *temp = graph->adjList[i];
        if (temp == NULL) {
            printf("(no substitutes)");
        }
        
        int count = 0;
        while (temp != NULL) {
            if (count > 0) printf(", ");
            printf("%s", graph->foods[temp->foodIndex].name);
            temp = temp->next;
            count++;
        }
        printf("\n");
    }
    printf("\n========================================\n\n");
}

// Find foods by diet type
void findByDietType(FoodGraph *graph, char *dietType) {
    printf("\n📋 Foods with diet type '%s':\n", dietType);
    printf("----------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < graph->numFoods; i++) {
        if (strcmp(graph->foods[i].dietType, dietType) == 0) {
            printf("%d. %s (%s) - %d kcal\n", 
                   found + 1,
                   graph->foods[i].name,
                   graph->foods[i].hindiName,
                   graph->foods[i].calories);
            found++;
        }
    }
    
    if (found == 0) {
        printf("  No foods found\n");
    }
    printf("----------------------------------------\n\n");
}

// Check if two foods are connected (can substitute each other)
int areConnected(FoodGraph *graph, int food1, int food2) {
    AdjNode *temp = graph->adjList[food1];
    
    while (temp != NULL) {
        if (temp->foodIndex == food2) {
            return 1;  // Connected
        }
        temp = temp->next;
    }
    
    return 0;  // Not connected
}

// Get degree (number of substitutes) for a food
int getDegree(FoodGraph *graph, int foodIndex) {
    int degree = 0;
    AdjNode *temp = graph->adjList[foodIndex];
    
    while (temp != NULL) {
        degree++;
        temp = temp->next;
    }
    
    return degree;
}

// Main function demonstrating Graph operations
int main() {
    FoodGraph graph;
    initGraph(&graph);
    
    printf("\n=== NutriPlan Food Substitution Network (Graph) ===\n\n");
    
    // Add food vertices
    printf("--- ADDING FOODS TO GRAPH ---\n");
    int paneer = addFood(&graph, "Paneer Bhurji", "पनीर भुर्जी", 265, 18.5, "veg");
    int tofu = addFood(&graph, "Tofu Scramble", "टोफू", 180, 15.0, "veg");
    int chicken = addFood(&graph, "Chicken Curry", "चिकन करी", 380, 32.0, "non-veg");
    int fish = addFood(&graph, "Fish Curry", "मछली करी", 320, 28.0, "non-veg");
    int egg = addFood(&graph, "Egg Curry", "अंडा करी", 350, 20.0, "egg");
    int dal = addFood(&graph, "Dal Tadka", "दाल तड़का", 180, 12.0, "veg");
    int chole = addFood(&graph, "Chole", "छोले", 420, 16.0, "veg");
    int mushroom = addFood(&graph, "Mushroom Curry", "मशरूम करी", 150, 8.0, "veg");
    int soya = addFood(&graph, "Soya Chunks", "सोया", 200, 20.0, "veg");
    int rajma = addFood(&graph, "Rajma", "राजमा", 380, 16.0, "veg");
    
    printf("\n--- CREATING SUBSTITUTION LINKS ---\n");
    // Create substitution network based on nutritional similarity
    
    // High protein veg options
    addEdge(&graph, paneer, tofu);
    addEdge(&graph, paneer, mushroom);
    addEdge(&graph, paneer, soya);
    
    // Non-veg high protein
    addEdge(&graph, chicken, fish);
    addEdge(&graph, chicken, egg);
    
    // Lentil-based veg proteins
    addEdge(&graph, dal, chole);
    addEdge(&graph, dal, rajma);
    addEdge(&graph, dal, tofu);
    
    // Cross-category protein sources
    addEdge(&graph, tofu, soya);
    addEdge(&graph, egg, paneer);
    addEdge(&graph, chole, rajma);
    
    // Display network
    displayGraph(&graph);
    
    // Find substitutes for specific foods
    findSubstitutes(&graph, paneer);
    findSubstitutes(&graph, chicken);
    findSubstitutes(&graph, dal);
    
    // Filter by diet type
    findByDietType(&graph, "veg");
    findByDietType(&graph, "non-veg");
    
    // Check if specific foods can substitute
    printf("--- CHECKING SUBSTITUTION COMPATIBILITY ---\n");
    printf("Can Paneer substitute Tofu? %s\n", 
           areConnected(&graph, paneer, tofu) ? "✅ Yes" : "❌ No");
    printf("Can Chicken substitute Dal? %s\n", 
           areConnected(&graph, chicken, dal) ? "✅ Yes" : "❌ No");
    printf("Can Egg substitute Paneer? %s\n\n", 
           areConnected(&graph, egg, paneer) ? "✅ Yes" : "❌ No");
    
    // Show most versatile food (highest degree)
    printf("--- FINDING MOST VERSATILE FOODS ---\n");
    printf("(Foods with most substitution options)\n\n");
    
    for (int i = 0; i < graph.numFoods; i++) {
        int degree = getDegree(&graph, i);
        if (degree >= 3) {
            printf("🌟 %s: %d substitutes\n", graph.foods[i].name, degree);
        }
    }
    
    printf("\n=== Graph demonstration complete! ===\n");
    printf("Key features: BFS traversal finds all connected substitutes\n");
    printf("Use case: 'Swap Meal' button uses this graph to find alternatives\n\n");
    
    return 0;
}