# Task Tracker CLI

**Description**  
Task Tracker is a command-line interface (CLI) application designed to help users manage their tasks efficiently. It provides a simple and lightweight way to add, track, and organize daily tasks directly from the terminal.

This project provides the solution proposed as part of the [Task Tracker challenge on roadmap.sh](https://roadmap.sh/projects/task-tracker).

---

## Features
- Add new tasks
- List all tasks
- Update task status
- Delete tasks
- Persistent storage using a JSON file

---

## Commands & Usage

Below is the list of supported commands and their usage.

### Add a task
```bash
> add Buy groceries
Task added (ID 1)

> add Finish roadmap.sh challenge
Task added (ID 2)

> list
[1] Buy groceries | todo
[2] Finish roadmap.sh challenge | todo

> update 2 done
Task updated.

> delete 1
Task deleted.

