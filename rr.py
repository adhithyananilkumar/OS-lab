import matplotlib.pyplot as plt

# Process class to hold data
class Process:
    def __init__(self, pid, burst_time):
        self.pid = pid
        self.burst_time = burst_time
        self.remaining_time = burst_time

def round_robin(processes, time_quantum):
    timeline = []
    time = 0
    queue = processes.copy()

    while queue:
        process = queue.pop(0)
        exec_time = min(time_quantum, process.remaining_time)

        timeline.append((process.pid, time, time + exec_time))
        time += exec_time
        process.remaining_time -= exec_time

        if process.remaining_time > 0:
            queue.append(process)

    return timeline

def plot_gantt_chart(timeline):
    fig, ax = plt.subplots()
    for pid, start, end in timeline:
        ax.barh(0, end - start, left=start, edgecolor='black', label=f'P{pid}')
        ax.text((start + end) / 2, 0, f'P{pid}', ha='center', va='center', color='white')

    ax.set_xlabel("Time")
    ax.set_yticks([])
    ax.set_title("Round Robin Scheduling - Gantt Chart")
    plt.tight_layout()
    plt.show()

# Example usage
if __name__ == "__main__":
    # Define processes: (pid, burst_time)
    processes = [Process(1, 5), Process(2, 3), Process(3, 8), Process(4, 6)]
    time_quantum = 2

    timeline = round_robin(processes, time_quantum)
    plot_gantt_chart(timeline)
