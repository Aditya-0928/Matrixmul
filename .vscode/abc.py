import matplotlib.pyplot as plt
import matplotlib.animation as animation


def knapsack_greedy(weights, values, capacity):
    # Calculate the value-to-weight ratio for each item
    ratios = [(value / weight) for value, weight in zip(values, weights)]

    # Sort the items based on the ratio in descending order
    items = sorted(zip(weights, values, ratios), key=lambda x: x[2], reverse=True)

    # Initialize the knapsack and total weight and value
    knapsack = []
    total_weight = 0
    total_value = 0

    for weight, value, ratio in items:
        if total_weight + weight <= capacity:
            # Add the item to the knapsack
            knapsack.append((weight, value))
            total_weight += weight
            total_value += value

    return knapsack, total_value


def animate(i):
    plt.cla()  # Clear the current axes

    # Display the current state of the knapsack
    if i < len(items):
        weight, value, ratio = items[i]
        selected = False

        if weight + current_weight <= capacity:
            current_weight += weight
            current_value += value
            selected = True

        plt.barh(y=0, width=weight, height=0.3, color='blue', alpha=0.5)
        plt.text(weight / 2, 0.15, f'Value: {value}', ha='center', va='center')
        plt.text(weight / 2, -0.15, f'Weight: {weight}', ha='center', va='center')
        plt.text(weight / 2, -0.45, f'Ratio: {ratio:.2f}', ha='center', va='center')
        plt.text(weight / 2, -0.75, f'Selected: {selected}', ha='center', va='center')

    # Display the final result
    if i == len(items):
        plt.text(0, 0, 'Final Result:', ha='left', va='center')
        plt.text(0, -0.3, f'Total Value: {current_value}', ha='left', va='center')
        plt.text(0, -0.6, f'Total Weight: {current_weight}', ha='left', va='center')

    plt.axis('off')


# Example inputs
weights = [2, 3, 5, 7, 9]
values = [10, 5, 15, 7, 6]
capacity = 20

# Solve the knapsack problem using the greedy method
knapsack, total_value = knapsack_greedy(weights, values, capacity)

# Prepare the items for animation
items = sorted(zip(weights, values, [v/w for v, w in zip(values, weights)]), key=lambda x: x[2], reverse=True)

# Initialize variables for animation
current_weight = 0
current_value = 0

# Create the figure and animation
fig = plt.figure()
ani = animation.FuncAnimation(fig, animate, frames=len(items)+1, interval=1000, repeat=False)

# Display the animation
plt.show()
