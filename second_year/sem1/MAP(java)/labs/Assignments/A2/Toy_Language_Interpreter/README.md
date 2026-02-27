# Toy Language Interpreter

A multi-threaded toy programming language interpreter with a JavaFX GUI, built as part of the Advanced Programming Methods course at UBB.

---

## What Can This Interpreter Do?

The interpreter executes programs written in a simple, imperative toy language that supports a surprisingly wide range of features.

### Types

| Type     | Description                                                                                |
| -------- | ------------------------------------------------------------------------------------------ |
| `int`    | Integer numbers                                                                            |
| `bool`   | Boolean values (`true` / `false`)                                                          |
| `string` | String values                                                                              |
| `Ref<T>` | Reference (pointer) to a heap-allocated value of type `T`; nestable (e.g. `Ref<Ref<int>>`) |

### Expressions

- **Arithmetic** — `+`, `-`, `*`, `/`
- **Relational** — `<`, `>`, `==`, `!=`, `<=`, `>=`
- **Logic** — `&&`, `||`
- **Not** — `!expr`
- **Variable read** — reads a variable from the symbol table
- **Heap read** — `rH(ref)` dereferences a heap pointer (chainable: `rH(rH(a))`)
- **Value literals** — integer, boolean, and string constants

### Statements

**Basic**

- Variable declaration: `int v;`, `bool a;`, `Ref int p;`
- Assignment: `v = expr`
- Conditional assignment: `v = (cond) ? expr1 : expr2`
- `if (cond) then s1 else s2`
- `switch (expr) case e1: s1; case e2: s2; default: s3`
- `print(expr)`
- `nop` — no operation
- `compound` — sequencing two statements

**Loops**

- `while (cond) stmt`
- `for (v = init; v < limit; v = step) stmt`
- `repeat stmt until cond`

**Heap / Memory**

- `new(ref, expr)` — allocates a value on the heap and stores the address in `ref`
- `wH(ref, expr)` — writes a new value to a heap address

**File I/O**

- `openRFile(filename)` — opens a file for reading
- `readFile(filename, var)` — reads the next integer from the file into a variable
- `closeRFile(filename)` — closes the file

**Concurrency**

- `fork(stmt)` — spawns a new concurrent thread that shares the heap and file table
- `newLock(x)` / `lock(x)` / `unlock(x)` — mutual exclusion locks
- `newSemaphore(cnt, capacity)` / `acquire(cnt)` / `release(cnt)` — counting semaphores
- `newBarrier(cnt, val)` / `barrierAwait(cnt)` — cyclic barriers
- `newLatch(cnt, val)` / `countDown(cnt)` / `latchAwait(cnt)` — countdown latches

### Runtime Features

- **Garbage collection** — unreachable heap objects are automatically collected after every execution step
- **Static type checking** — a full typecheck pass runs before any program is allowed to start
- **Concurrent execution** — forked threads run concurrently via a fixed-size `ExecutorService` thread pool
- **Execution logging** — every program step is written to a dedicated log file (`src/logs/logN.txt`)

---

## User Interface

The project ships with **two separate UIs**.

### JavaFX GUI (`MainFX`) — recommended

A two-window graphical interface built with JavaFX and FXML.

**Programs window** — lists all 20 pre-loaded example programs. Click one to load it into the main window.

**Main execution window** — displays the full interpreter state in real time:

| Panel            | Shows                                                   |
| ---------------- | ------------------------------------------------------- |
| Execution Stack  | Remaining statements for the selected thread            |
| Symbol Table     | Variable → value bindings for the selected thread       |
| Heap Table       | Address → value for all heap-allocated data             |
| File Table       | Open file descriptors and their read buffers            |
| Output List      | All values printed by `print()`                         |
| Program IDs list | IDs of all live threads; click one to inspect its state |
| Thread count     | Number of currently active program states               |
| Lock Table       | Index → owner for each mutex lock                       |
| Semaphore Table  | Index → (capacity, waiting list) for each semaphore     |
| Barrier Table    | Index → (count, waiting list) for each barrier          |
| Latch Table      | Index → remaining count for each latch                  |

Execution is driven by a **One Step** button (advances all live threads by one step concurrently) and a **Run All** button (runs the program to completion).

### CLI Text Menu (`Main`)

A simple terminal-based menu. Select a numbered program and run it step by step or to completion — useful for quick testing without a display.

---

## Built-in Example Programs

20 programs are pre-loaded, covering the full feature set:

| #   | What it demonstrates                               |
| --- | -------------------------------------------------- |
| 1   | Variable declaration and `print`                   |
| 2   | Arithmetic expressions (`2 + 3 * 5`)               |
| 3   | `if` statement with booleans                       |
| 4   | File I/O (`openRFile` / `readFile` / `closeRFile`) |
| 5   | Relational expressions and `if` with strings       |
| 6   | Heap allocation, nested `Ref` types                |
| 7   | Heap read (`rH`) with chaining                     |
| 8   | Heap write (`wH`)                                  |
| 9   | GC-observable aliasing through nested refs         |
| 10  | Garbage collection (unreachable heap node)         |
| 11  | `while` loop                                       |
| 12  | `fork` — basic concurrency with a shared heap      |
| 13  | `repeatUntil` + `fork` interleaving                |
| 14  | Barriers across forked threads                     |
| 15  | `for` loop + `fork`                                |
| 16  | Locks with nested forks                            |
| 17  | Conditional assignment (`? :`)                     |
| 18  | Countdown latches across nested forks              |
| 19  | `switch / case` statement                          |
| 20  | Semaphores with `acquire` / `release`              |

---

## Project Structure

```
src/
├── Main.java                       # CLI entry point
├── MainFX.java                     # JavaFX entry point (20 example programs)
├── controller/
│   ├── ProgramService.java         # Execution engine (one-step / full run, GC)
│   ├── GarbageCollector.java       # Mark-and-sweep heap GC
│   └── javafx_controller/
│       ├── MainController.java     # Main window controller
│       └── ProgramsController.java # Program list controller
├── model/
│   ├── expressions/                # Arithmetic, logic, relational, heap-read, etc.
│   ├── statements/
│   │   ├── basic_statements/       # Assign, if, switch, print, nop, …
│   │   ├── file_statements/        # open / read / close file
│   │   ├── heap_statements/        # new(), wH()
│   │   ├── loop_statements/        # while, for, repeatUntil
│   │   └── thread_statements/      # fork, lock, semaphore, barrier, latch
│   ├── states/                     # ProgramState, ExecutionStack, SymbolTable, HeapTable, …
│   ├── types/                      # IntType, BoolType, StringType, RefType
│   └── values/                     # IntValue, BoolValue, StringValue, RefValue
├── repo/                           # Repository (program state persistence + logging)
├── view/                           # CLI menu + JavaFX FXML views
├── exceptions/                     # Typed exception hierarchy
└── logs/                           # Execution logs (log1.txt … log20.txt)
```

---

## Getting Started

### Prerequisites

- **JDK 21+** (project uses instance `main()` without a surrounding class)
- **JavaFX SDK** — configure as a module-path dependency in your IDE (IntelliJ IDEA recommended)

_Created by Paul Fulop_
