# A* Pathfinding Visualization in Qt

This project is a visualization tool for demonstrating how the A* pathfinding algorithm works using a grid layout. Built with Qt framework, it offers a graphical interface to set start and end points, place obstacles, and visually follow the algorithm's process in finding the shortest path. The application is written in C++ and leverages the Qt library for the graphical user interface and painting mechanisms.

## Features

- **Interactive Grid**: Users can interact with the grid by setting start and end points, as well as creating obstacles by clicking on the grid cells.
- **A* Algorithm Visualization**: The application visually demonstrates how the A* algorithm searches for the shortest path, updating in real-time.
- **Customizable Grid**: Users can adjust the grid size, node size, and other parameters within the code to experiment with different configurations.

## Getting Started

### Prerequisites

Ensure you have the following installed:
- Qt 5.x Development Libraries
- C++ Compiler compatible with Qt
- Qt Creator (Optional, but recommended for ease of use)

### Installation

1. Clone the repository or download the source code.
2. Open the project in Qt Creator or compile using the Qt command line tools.
3. Run the application.

### Usage

- **Left Click**: Place or remove obstacles on the grid.
- **Right Click**: Set the start point.
- **Middle Click**: Set the end point.
- **'Run' Button**: Starts the A* algorithm visualization.

## Code Structure

- `main.cpp`: Initializes the application and sets up high DPI scaling.
- `widget.cpp` & `widget.h`: Contains the main widget class implementing the grid, pathfinding logic, and event handlers.
- `Node`: A struct within `Widget` class representing each cell in the grid with attributes like coordinates, obstacle flag, global and local goals, neighbors, and parent node pointer.

## Customization

You can customize the grid size, node size, and other parameters by modifying the respective variables in `widget.h`.

## Known Issues

- Performance may vary based on the grid size and the complexity of the path.
- The application currently does not support dynamic resizing of the grid during runtime.
- Position of mouse to gui might be inaccurate due to Qt issues with high resolution displays.

## Contributing

Contributions to improve the project are welcome. Please feel free to fork the repository, make changes, and submit pull requests.

