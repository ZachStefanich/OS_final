import matplotlib.pyplot as plt 
import csv

x = []
y = []
z = []

with open('time_data.csv', 'r') as file:
    
    lines = csv.reader(file, delimiter=',') 
    for row in lines:
        x.append(row[0])
        y.append(row[1])
        z.append(row[2])
x.pop(0)
y.pop(0)
z.pop(0)
fig, ax = plt.subplots(2, 1, figsize=(10, 8))

# Multi-thread Time Graph
ax[0].plot(z, x, 'r*--')
ax[0].set_xlabel("Number of Threads")
ax[0].set_ylabel("Time (Multi-thread)")
ax[0].set_title("Multi-Thread Time Graph")

# Single-thread Time Graph
ax[1].plot(z, y, 'bo--')
ax[1].set_xlabel("Number of Threads")
ax[1].set_ylabel("Time (Single-thread)")
ax[1].set_title("Single-Thread Time Graph")

# Adjust layout
plt.tight_layout()
plt.show()