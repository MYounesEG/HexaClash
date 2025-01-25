# HexaClash - Battle Simulation Project

## Overview

**HexaClash** is a battle simulation project that simulates a turn-based battle between two teams: the **Human Empire** (`insan_imparatorlugu`) and the **Orc Legion** (`ork_legi`). The project includes a graphical interface built with **SFML (Simple and Fast Multimedia Library)** and uses JSON files to define unit types, heroes, monsters, and research levels. The simulation calculates damage, critical hits, and other battle mechanics, and logs the results to a file.

---

## Features

- **Turn-Based Battle Simulation**: Simulates battles between two teams with attack, defense, and critical hit mechanics.
- **Graphical Interface**: Renders a hexagonal grid with unit images, health bars, and main characters (heroes and monsters).
- **Dynamic Unit Placement**: Units are randomly placed on the grid based on their team.
- **Health Bars and Stats**: Displays health percentages and unit stats in real-time.
- **Interactive UI**: Click on units to enlarge or shrink their images.
- **Sound Effects**: Plays background music during the welcome screen.
- **Logging**: Logs battle results to a file (`savas_sim.txt`).

---

## Prerequisites

Before running the project, ensure you have the following installed:

1. **C/C++ Compiler**: 
   - GCC (Linux/Mac) or MinGW (Windows).
2. **SFML Library**:
   - Download and install SFML from [SFML's official website](https://www.sfml-dev.org/).
   - Make sure SFML is properly linked to your project.
3. **CURL** (for downloading scenario files):
   - Ensure `curl` is installed on your system.
4. **Windows API** (for sound and system commands):
   - Required for `PlaySound` and `system` commands.

---

## Installation

### Step 1: Clone the Repository

```bash
git clone https://github.com/your-username/HexaClash.git
cd HexaClash
```

### Step 2: Install Dependencies

#### On Windows:
<ol start="1">
  <li>
    <p>
      Download and install
      <a
        href="https://www.sfml-dev.org/download.php"
        target="_blank"
        rel="noreferrer"
        >SFML</a
      >.
    </p>
  </li>
  <li>
    <p>
      Add SFML's <code>include</code> and <code>lib</code> directories to your
      compiler's search paths.
    </p>
  </li>
  <li>
    <p>
      Ensure <code>sfml-audio-2.dll</code>, <code>sfml-graphics-2.dll</code>,
      and other SFML DLLs are in the <code>bin/Debug</code> or
      <code>bin/Release</code> folder.
    </p>
  </li>
</ol>

#### On Linux/Mac:
Install SFML using your package manager:
```bash
sudo apt-get install libsfml-dev  # For Ubuntu/Debian
brew install sfml                # For Mac
```
### Step 3: Compile the Project

#### Using GCC:
```bash
g++ -std=c++11 main.c gameInterface.cpp -o HexaClash -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

#### Using Code::Blocks
1. open `HexaClash.cbp` using Code::Blocks
2. click "Build and run" or press F9

## Usage

<ol start="1">
  <li>
    <p><strong>Run the Program</strong></p>

  </li>
  <li>
    <p><strong>Enter a Scenario Number</strong>:</p>
    <ul>
      <li>
        <p>The program will prompt you to enter a scenario number (1-10).</p>
      </li>
      <li>
        <p>
          The scenario file will be downloaded automatically if it doesn't exist
          locally.
        </p>
      </li>
    </ul>
  </li>
  <li>
    <p><strong>View the Battle</strong>:</p>
    <ul>
      <li>
        <p>
          The graphical interface will display the battle grid, units, and
          health bars.
        </p>
      </li>
      <li><p>Click on units to enlarge or shrink their images.</p></li>
    </ul>
  </li>
  <li>
    <p><strong>Battle Simulation</strong>:</p>
    <ul>
      <li>
        <p>
          The battle is simulated automatically, and the results are logged to
          <code>savas_sim.txt</code>.
        </p>
      </li>
    </ul>
  </li>
  <li>
    <p><strong>Replay or Exit</strong>:</p>
    <ul>
      <li>
        <p>
          After the battle, you can choose to replay the simulation or exit the
          program.
        </p>
      </li>
    </ul>
  </li>
</ol>

## Project Structure
```mathematica
Prolab1/
├── bin/                # Compiled binaries and SFML DLLs
├── fonts/              # Font files (e.g., Arial.ttf)
├── images/             # Unit, hero, monster, and background images
├── json/               # JSON files for unit types, heroes, monsters, and research
├── music/              # Background music (music.wav)
├── obj/                # Object files (generated during compilation)
├── src/                # Source code files
│   ├── classes.h       # Data structures for units, heroes, monsters, and teams
│   ├── fightFunction.h # Battle simulation logic
│   ├── functions.h     # Utility functions for file handling and user interaction
│   ├── gameInterface.cpp # Graphical interface implementation
│   ├── main.c          # Entry point of the program
├── README.md           # Project documentation
```

## JSON File Format
The project uses JSON files to define scenarios. Here's an example structure:
```json
{
  "insan_imparatorlugu": {
    "birimler": [
      {"isim": "piyade", "sayi": 100},
      {"isim": "okcu", "sayi": 50}
    ],
    "kahramanlar": [
      {"isim": "Alparslan", "bonus_turu": "saldiri", "bonus_degeri": 10, "etkilenen": "piyade"}
    ],
    "canavarlar": [
      {"isim": "Ejderha", "etki_turu": "savunma", "etki_degeri": 5, "etkilenen": "okcu"}
    ],
    "arastirma_seviyesi": {
      "isim": "savunma_ustaligi",
      "seviye": 1,
      "oran": 10
    }
  },
  "ork_legi": {
    "birimler": [
      {"isim": "ork_dovuscu", "sayi": 120},
      {"isim": "trol", "sayi": 30}
    ],
    "kahramanlar": [
      {"isim": "Goruk_Vahsi", "bonus_turu": "kritik", "bonus_degeri": 15, "etkilenen": "ork_dovuscu"}
    ],
    "canavarlar": [
      {"isim": "Tepegoz", "etki_turu": "saldiri", "etki_degeri": 8, "etkilenen": "trol"}
    ],
    "arastirma_seviyesi": {
      "isim": "elit_egitim",
      "seviye": 2,
      "oran": 20
    }
  }
}
```



<hr>

![ww](images/Screenshots(1).bmp)

![ww](images/Screenshots(2).bmp)

<hr>

## Collaborators

<ul>
  <li>
    <p>
      <strong
        ><a
          href="https://github.com/MYounesEG"
          target="_blank"
          rel="noreferrer"
          >MYounes</a
        ></strong
      >: JSON file parsing and unit data management.
    </p>
  </li>
  <li>
    <p>
      <strong
        ><a
          href="https://github.com/MerveSevim44"
          target="_blank"
          rel="noreferrer"
          >Merve Sevim</a
        ></strong
      >: SFML integration and UI design.
    </p>
  </li>
</ul>


# Enjoy the HexaClash simulation! 🎮