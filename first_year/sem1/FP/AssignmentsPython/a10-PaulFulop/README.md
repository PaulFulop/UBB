# Board Game Application

A Python-based board game implementation featuring both console and graphical user interfaces, AI player support, and score tracking capabilities.

## Features

- 6x6 game board implementation
- Dual interface support:
  - Console-based UI
  - PyGame-based graphical interface
- AI player with adjustable difficulty levels
- Score tracking and persistence
- Configurable game settings through properties file

## Project Structure

```
src/
├── domain/          # Core game entities
├── interface/       # UI implementations (Console & PyGame)
├── repository/      # Data persistence layer
├── services/        # Game logic and AI implementation
└── test/           # Unit tests
```

## Getting Started

### Prerequisites

- Python 3.x
- PyGame library
- Texttable library

### Installation

1. Clone the repository:

```bash
git clone https://github.com/cs-ubbcluj-ro/a10-PaulFulop.git
```

2. Install required dependencies:

```bash
pip install pygame texttable
```

### Configuration

Game settings can be configured in `src/settings.properties`:

- `mode`: Interface mode (`console` or `pygame`)
- `firstPlayer`: Who starts first (`human` or `computer`)
- `difficulty`: AI difficulty level (1-3)

### Running the Game

```bash
python src/start.py
```

## Testing

The project includes a comprehensive test suite covering:

- Board mechanics
- Repository operations
- Game services

Run tests using:

```bash
python -m unittest discover src/test
```

## License

This project is licensed under the terms provided in the LICENSE file.

## Author

Paul Fulop - cs-ubbcluj-ro
