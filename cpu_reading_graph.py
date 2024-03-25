#!/home/uriel/work/coding/python/virenv/bin/python
import matplotlib.pyplot as plt
import numpy as np
import time

def main():

    temperature_readings = []
    number_of_readings = 0    
    
    with open("./cpu_temperature_readings.txt", "r") as file:
        lines = file.readlines()
        number_of_readings = len(lines)

        for line in lines:
            temperature_readings.append(int(line.strip()))

    def plot_graph(x_values, y_values):
        plt.plot(x_values, y_values)
        plt.xlabel('Time (seconds)')
        plt.ylabel('Temperatures')
        plt.title('Temperature Over Time')
        plt.grid(True)
        plt.savefig('temperature_readings.png')
        plt.show()

    seconds = list(range(1, number_of_readings + 1))

    plot_graph(seconds, temperature_readings)

main()
