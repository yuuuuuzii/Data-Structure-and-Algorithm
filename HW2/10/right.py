class PrinterQueue:
    def __init__(self):
        self.jobs = []

    def add_job(self, job_id, priority):
        self.jobs.append((job_id, priority))
        self.jobs.sort(key=lambda x: x[1], reverse=True)

    def print_job(self):
        if self.jobs:
            job_id, _ = self.jobs.pop(0)
            print(f"{job_id} printed")
        else:
            print("no documents in queue")

    def move_jobs(self, other_queue):
        other_queue.jobs.extend(self.jobs)
        other_queue.jobs.sort(key=lambda x: x[1], reverse=True)
        self.jobs.clear()


def main():
    n, m = map(int, input().split())
    printers = {i: PrinterQueue() for i in range(1, n + 1)}

    for _ in range(m):
        operation = input().split()
        if operation[0] == '1':
            # Add operation
            _, job_id, priority, printer_id = map(int, operation)
            printers[printer_id].add_job(job_id, priority)
            print(f"{len(printers[printer_id].jobs)} jobs waiting on printer {printer_id}")
        
        elif operation[0] == '2':
            # Print operation
            _, printer_id = map(int, operation)
            printers[printer_id].print_job()

        elif operation[0] == '3':
            # Move operation
            _, printer_id1, printer_id2 = map(int, operation)
            printers[printer_id1].move_jobs(printers[printer_id2])
            print(f"{len(printers[printer_id2].jobs)} jobs waiting on printer {printer_id2} after moving")


if __name__ == "__main__":
    main()
    
