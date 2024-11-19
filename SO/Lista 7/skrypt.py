import os

def sum_memory_values(field_name):
    total = 0
    for pid in os.listdir('/proc'):
        if pid.isdigit():  # Tylko katalogi z numerami PID
            try:
                with open(f'/proc/{pid}/status', 'r') as f:
                    for line in f:
                        if line.startswith(field_name):
                            total += int(line.split()[1])  # Wartość w kB
                            break
            except FileNotFoundError:
                # Proces mógł zakończyć się w międzyczasie
                continue
    return total

vm_size_sum = sum_memory_values('VmSize:')
vm_rss_sum = sum_memory_values('VmRSS:')

print(f"Suma VmSize: {vm_size_sum // 1024} MB")
print(f"Suma VmRSS: {vm_rss_sum // 1024} MB")