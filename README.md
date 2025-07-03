## Simple Reflex Agent:
* Dirt is randomly placed
* Agent:
    - Cleans if there is dirt in adjacent cells
    - If no dirt nearby, moves randomly
## Utility Based Agent
### Utility Function:
We define utility of a cell as:</br>

    `utility = 10 if cell has dirt else -distance from nearest dirt`
    
* This means:
    - The agent prefers to clean nearby dirt first.
    - If no adjacent dirt is found, it moves toward the cell with the highest expected utility.
## Goal Based Agent
* The agent looks for nearest dirt (goal).
* Uses BFS to find shortest path (search/planning).
* Moves purposefully to reduce distance to dirt (goal-oriented).
* Stops when no dirt remains (goal achieved).
