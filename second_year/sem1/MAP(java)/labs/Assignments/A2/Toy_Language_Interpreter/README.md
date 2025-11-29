# Toy Language Interpreter

A simple interpreter implementation for a toy programming language, developed as part of the Advanced Programming Methods course.

## Overview

This project implements a basic interpreter for a toy programming language. It supports fundamental programming concepts including:

- Variable declarations and assignments
- Arithmetic expressions
- Logical operations
- Control flow statements (if statements)
- Program state management
- Basic I/O operations (print statements)

## Project Structure

The interpreter is organized into several main components:

- **Model**: Contains the core language elements

  - Expressions (arithmetic, logic, variables)
  - Statements (assignment, if, print, etc.)
  - Program state management
  - Types system (integers, booleans)
  - Values handling

- **Controller**: Manages the execution of programs
- **Repository**: Handles program state storage
- **View**: Provides the user interface for the interpreter

## Features

- Type checking and validation
- Expression evaluation
- Statement execution
- Program state tracking
- Symbol table management
- Execution stack implementation

## Getting Started

### Prerequisites

- Java Development Kit (JDK) 8 or higher
- Any Java IDE (IntelliJ IDEA recommended)

### Running the Interpreter

1. Clone this repository
2. Open the project in your preferred Java IDE
3. Run the `Main.java` file to start the interpreter

## Technical Implementation

The interpreter follows a modular design with clear separation of concerns:

- **Expression Evaluation**: Handles arithmetic and logical expressions
- **Statement Execution**: Processes various program statements
- **State Management**: Maintains program state including variables and execution stack
- **Type System**: Implements basic types (Integer, Boolean)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Created by Paul Fulop
