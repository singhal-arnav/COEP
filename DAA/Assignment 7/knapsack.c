#include <stdio.h>

struct Item {
    float weight;
    float value;
    float ratio;
    int index;
};

int main() {
    int n;
    float W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item items[n];
    float fraction[n];
    float result[n];

    for(int i = 0; i < n; i++) {
        fraction[i] = 0;
        result[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        printf("Enter weight of item %d: ", i + 1);
        scanf("%f", &items[i].weight);
        printf("Enter value of item %d: ", i + 1);
        scanf("%f", &items[i].value);
        items[i].ratio = items[i].value / items[i].weight;
        items[i].index = i;
    }

    printf("Enter knapsack capacity: ");
    scanf("%f", &W);

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(items[j].ratio < items[j + 1].ratio) {
                struct Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    float totalValue = 0;

    for(int i = 0; i < n; i++) {
        if(W >= items[i].weight) {
            W -= items[i].weight;
            totalValue += items[i].value;
            fraction[i] = 1;
        }
        else {
            fraction[i] = W / items[i].weight;
            totalValue += items[i].ratio * W;
            break;
        }
    }

    for(int i = 0; i < n; i++) {
        result[items[i].index] = fraction[i];
    }

    printf("Maximum value in knapsack: %.2f\n", totalValue);
    printf("Fractions of items selected: ");
    for(int i = 0; i < n; i++) {
        printf("%.2f ", result[i]);
    }
    printf("\n");

    return 0;
}

