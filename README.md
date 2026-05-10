# Queue Simulation System
**Data Structures Project | First Year, Faculty of CSIT**

## Overview
This project is a comprehensive simulation of a service-based system (e.g., a bank or a clinic). It utilizes a **Linked List-based Queue** to manage customer flow, featuring a robust **VIP Priority** system where VIP customers are strategically inserted into the queue to receive faster service.

## Key Features
*   **Dynamic Queue Management:** Implemented from scratch using a Linked List to ensure efficient memory usage.
*   **VIP Priority System:** Intelligent logic to handle VIP customers, allowing them to skip ahead of regular customers while maintaining order among fellow VIPs.
*   **Real-time Simulation Engine:** Tracks arrival times, service durations, and server availability through a "Time Tick" system.
*   **Interactive GUI:** A modern interface built with **SFML** featuring:
    *   Live server status (Free/Busy/Remaining Time).
    *   Visual queue representation.
    *   Real-time statistics (Arrived vs. Served customers).
    *   A dynamic line graph showing queue history.

## Tech Stack
*   **Language:** C++
*   **Library:** SFML 3.0.2 (Graphics, Window, System)
*   **Compiler:** g++ (GCC 14.2.0 MinGW-w64)

## Project Structure
```text
Data-Structure-project/
├── src/                # Header files and Source files
│   ├── Controller.h
│   ├── Controller.cpp
│   ├── Customer.h
│   ├── Customer.cpp
│   ├── CustomerQueue.h
│   ├── CustomerQueue.cpp
│   ├── GUI.h
│   ├── GUI.cpp
│   ├── Server.h
│   ├── Server.cpp
│   ├── Simulation.h
│   ├── Simulation.cpp
│   └── main.cpp
├── assets/             
│   └── font.ttf        # UI font file
├── build/              # Executable and SFML DLLs
│   ├── sim_app.exe
│   └── sfml-xxx-3.dll  # Pre-included library dependencies
├── .gitignore          
├── README.md
└── Report.md           
```

## How to Compile & Run

### 1. Prerequisites
*   **SFML 3.0.2:** Download the required version (GCC 14.2.0 MinGW-w64 64-bit) from [this link](https://www.sfml-dev.org/files/SFML-3.0.2-windows-gcc-14.2.0-mingw-64-bit.zip).
    *   **Installation:** Extract the contents to `C:\SFML-3.0.2` to ensure the compilation paths match.
*   **C++ Compiler:** Ensure `g++` is installed and added to your system Environment Variables.

### 2. Compilation
Execute the following command from the **root directory** to allow the compiler to link all the source files inside the `src` folder.

**For Windows (PowerShell):**
```powershell
g++ (Get-ChildItem src\*.cpp).FullName -I"C:\SFML-3.0.2\include" -L"C:\SFML-3.0.2\lib" -o build/sim_app -lsfml-graphics -lsfml-window -lsfml-system
```

**For Linux / Git Bash / Command Prompt:**
```bash
g++ src/*.cpp -I"C:\SFML-3.0.2\include" -L"C:\SFML-3.0.2\lib" -o build/sim_app -lsfml-graphics -lsfml-window -lsfml-system
```

### 3. Execution
The necessary **DLL** files are already included in the `build` folder. Simply run:
```bash
cd build
./sim_app
```

## Simulation Tweaks (Scenario Testing)
You can modify the simulation behavior by adjusting constants directly within the Header files:

*   **VIP Probability:** To change how often VIP customers appear, modify the probability logic in `Simulation.h` or `Controller.h`.
*   **Service Time:** To adjust how long a server stays "Busy," update the `serviceTime` variables in `Server.h`.
*   **Visual Assets:** If you change the font, ensure the new file is named `font.ttf` and placed in the `assets/` directory.

## Contributors
*   **Khaled**
*   **Adham**
*   **Asser**
*   **Ahmed**